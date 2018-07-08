#include <d3d11.h>
#include <d3dcommon.h>

#include "zephyr\runtime_assert.h"
#include "zephyr.graphics\Window.h"
#include "zephyr.graphics\Color.h"
#include "zephyr.graphics.dx11\Texture2D.h"
#include "zephyr.graphics.dx11\RenderTargetView.h"
#include "zephyr.graphics.dx11\VertexShader.h"
#include "zephyr.graphics.dx11\GeometryShader.h"
#include "zephyr.graphics.dx11\PixelShader.h"
#include "zephyr.graphics.dx11\VertexBuffer.h"
#include "zephyr.graphics.dx11\IndexBuffer.h"
#include "zephyr.graphics.dx11\VertexLayout.h"
#include "zephyr.graphics.dx11\InstanceBuffer.h"
#include "zephyr.graphics.dx11\BlendState.h"
#include "zephyr.graphics.dx11\RasterizerState.h"
#include "zephyr.graphics.dx11\enums.h"
#include "zephyr.graphics.dx11\DepthStencilState.h"

#include "GraphicsDevice.h"

#define this (*this)
#define device GraphicsDevice::Instance.Device
#define context GraphicsDevice::Instance.DeviceContext

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            GraphicsDevice::~GraphicsDevice()
            {
                this.Release();

                context.reset();

#ifdef _DEBUG
                if (device.available())
                {
                    com_ptr<ID3D11Debug> pD3dDebug;

                    HRESULT hr = device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&pD3dDebug));
                    runtime_assert(SUCCEEDED(hr));

                    pD3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
                }
#endif

                device.reset();
            }

            void GraphicsDevice::UnbindAllResources()
            {
                // すべてのリソースとパイプラインとのバインドを解除する
                context->ClearState();
            }

            void GraphicsDevice::Create(const Window& window)
            {
                this.Create(window, false);
            }

            void GraphicsDevice::Create(const Window& window, bool fullscreen)
            {
                // スワップチェインの設定
                DXGI_SWAP_CHAIN_DESC swapChainDesc;
                ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
                swapChainDesc.BufferCount = 1;
                swapChainDesc.BufferDesc.Width = window.width;
                swapChainDesc.BufferDesc.Height = window.height;
                swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
                swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
                swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                swapChainDesc.OutputWindow = (HWND)window.handle;
                swapChainDesc.SampleDesc.Count = 1;
                swapChainDesc.SampleDesc.Quality = 0;
                swapChainDesc.Windowed = !fullscreen;
                swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

                // 機能レベル
                D3D_FEATURE_LEVEL featureLevels[] = {
                    D3D_FEATURE_LEVEL_11_0,
                    //D3D_FEATURE_LEVEL_10_1,
                    //D3D_FEATURE_LEVEL_10_0,
                };
                UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);

                // デバイスとスワップチェインの作成
                UINT flags = 0;
#ifdef _DEBUG
                flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
                HRESULT hr = S_OK;
                for (auto& driver : {
                    D3D_DRIVER_TYPE_HARDWARE,
                    D3D_DRIVER_TYPE_WARP,
                    D3D_DRIVER_TYPE_REFERENCE
                })
                {
                    hr = D3D11CreateDeviceAndSwapChain(
                        NULL,
                        driver,
                        NULL,
                        flags,
                        featureLevels,
                        numFeatureLevels,
                        D3D11_SDK_VERSION,
                        &swapChainDesc,
                        &m_swapChain,
                        &device,
                        &m_featureLevel,
                        &context);
                    if (SUCCEEDED(hr))
                        break;
                }
                runtime_assert(SUCCEEDED(hr), "Failed to create d3d11 device.");

                // バックバッファ取得
                Texture2D backBuffer;
                hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
                runtime_assert(SUCCEEDED(hr));

                // レンダーターゲットビューを生成
                hr = device->CreateRenderTargetView(backBuffer.ptr, NULL, &m_renderTargetView);
                runtime_assert(SUCCEEDED(hr));

                // 深度バッファを作成
                m_depthStencil.CreateDepthStencil(window.width, window.height);
                m_depthStencilView.Create(m_depthStencil);

                // 出力マネージャにレンダーターゲットビューを設定
                ID3D11RenderTargetView* renderTargetViews[] = { m_renderTargetView.ptr };
                context->OMSetRenderTargets(1, renderTargetViews, m_depthStencilView.ptr);

                // 深度ステートの設定
                m_depthStencilState.Create(true, false, true);
                context->OMSetDepthStencilState(m_depthStencilState.ptr, 0);

                // ビューポートの設定
                D3D11_VIEWPORT vp;
                {
                    vp.Width = (float)window.width;
                    vp.Height = (float)window.height;
                    vp.MinDepth = 0.0f;
                    vp.MaxDepth = 1.0f;
                    vp.TopLeftX = 0;
                    vp.TopLeftY = 0;
                }
                context->RSSetViewports(1, &vp);

                // 
                m_swapChain->SetFullscreenState(fullscreen, NULL);
            }

            void GraphicsDevice::Clear(const Color& clearColor)
            {
                float r = clearColor.r;
                float g = clearColor.g;
                float b = clearColor.b;
                float a = clearColor.a;
                float rgba[] = { r,g,b,a };

                RenderTargetView targetView;
                DepthStencilView depthView;
                context->OMGetRenderTargets(1, &targetView, &depthView);
                if (targetView.available())
                    context->ClearRenderTargetView(targetView.ptr, rgba);
                if (depthView.available())
                    context->ClearDepthStencilView(depthView.ptr, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            }

            void GraphicsDevice::Release()
            {
                // すべてのリソースとパイプラインとのバインドを解除する
                if (context.available())
                    context->ClearState();

                m_featureLevel = (D3D_FEATURE_LEVEL)0;
                m_renderTargetView.reset();
                m_swapChain.reset();
                m_renderTargetView.reset();
                m_depthStencil.reset();
                m_depthStencilView.reset();
                m_depthStencilState.reset();
            }

            void GraphicsDevice::SetVertexShader(VertexShader& shader)
            {
                context->VSSetShader(shader.ptr, NULL, 0);
            }

            void GraphicsDevice::SetGeometryShader(GeometryShader& shader)
            {
                context->GSSetShader(shader.ptr, NULL, 0);
            }

            void GraphicsDevice::SetPixelShader(PixelShader& shader)
            {
                context->PSSetShader(shader.ptr, NULL, 0);
            }

            void GraphicsDevice::SetVertexBuffer(VertexBuffer& buffer, int slot)
            {
                ID3D11Buffer* _buffers[] = { buffer.ptr };
                UINT _strides[] = { (UINT)buffer.stride };
                UINT _offsets[] = { (UINT)0 };

                context->IASetVertexBuffers(slot, 1, _buffers, _strides, _offsets);
            }

            void GraphicsDevice::SetVertexBuffers(VertexBuffer buffers[], int bufferCount, int startSlot)
            {
                enum { MAX_SLOT_COUNT = D3D11_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT };

                ID3D11Buffer* _buffers[MAX_SLOT_COUNT];
                UINT _strides[MAX_SLOT_COUNT];
                UINT _offsets[MAX_SLOT_COUNT] = { 0 };

                for (int i = 0; i < bufferCount; i++)
                {
                    _buffers[i] = buffers[i].ptr;
                    _strides[i] = buffers[i].stride;
                }

                context->IASetVertexBuffers(startSlot, bufferCount, _buffers, _strides, _offsets);
            }

            void GraphicsDevice::SetIndexBuffer(IndexBuffer& buffer)
            {
                context->IASetIndexBuffer(buffer.ptr, DXGI_FORMAT_R32_UINT, 0);
            }

            void GraphicsDevice::SetInstanceBuffer(InstanceBuffer& buffer, int slot)
            {
                this.SetVertexBuffer(buffer, slot);
            }

            void GraphicsDevice::SetInstanceBuffers(InstanceBuffer buffers[], int bufferCount, int startSlot)
            {
                this.SetVertexBuffers(buffers, bufferCount, startSlot);
            }

            void GraphicsDevice::SetVertexLayout(VertexLayout& layout)
            {
                context->IASetInputLayout(layout.ptr);
            }

            void GraphicsDevice::SetPrimitiveTopology(PrimitiveTopology topology)
            {
                context->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)topology);
            }

            void GraphicsDevice::SetBlendState(BlendState& state)
            {
                float factor[] = { 0,0,0,0 };
                context->OMSetBlendState(state.ptr, factor, 0xffffffff);
            }

            void GraphicsDevice::SetRasterizerState(RasterizerState& state)
            {
                context->RSSetState(state.ptr);
            }

            void GraphicsDevice::SetDepthStencilState(DepthStencilState& state)
            {
                context->OMSetDepthStencilState(state.ptr, 0);
            }

            void GraphicsDevice::SetRenderTargetAndDepthStencil(RenderTargetView& view1, DepthStencilView& view2)
            {
                ID3D11RenderTargetView* renderTargetViews[] = { view1.ptr };
                context->OMSetRenderTargets(1, renderTargetViews, view2.ptr);
            }

            void GraphicsDevice::SetRenderTargetAndDepthStencil(nullptr_t, DepthStencilView& view2)
            {
                ID3D11RenderTargetView* renderTargetViews[] = { nullptr };
                context->OMSetRenderTargets(1, renderTargetViews, view2.ptr);
            }

            void GraphicsDevice::SetRenderTargetAndDepthStencil(RenderTargetView& view1, nullptr_t)
            {
                ID3D11RenderTargetView* renderTargetViews[] = { view1.ptr };
                context->OMSetRenderTargets(1, renderTargetViews, nullptr);
            }

            void GraphicsDevice::ResetRenderTargetAndDepthStencil()
            {
                ID3D11RenderTargetView* renderTargetViews[] = { m_renderTargetView.ptr };
                context->OMSetRenderTargets(1, renderTargetViews, m_depthStencilView.ptr);
            }

            void GraphicsDevice::SetViewport(int width, int height)
            {
                CD3D11_VIEWPORT	viewport(0.0f, 0.0f, (float)width, (float)height);
                context->RSSetViewports(1, &viewport);
            }

            void GraphicsDevice::Draw(int vertexCount, int startVertexLocation)
            {
                context->Draw(vertexCount, startVertexLocation);
            }

            void GraphicsDevice::DrawIndexed(int indexCount, int startIndexLocation, int baseVertexLocation)
            {
                context->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
            }

            void GraphicsDevice::DrawInstanced(int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation)
            {
                context->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
            }

            void GraphicsDevice::DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation)
            {
                context->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startIndexLocation);
            }

            void GraphicsDevice::Present()
            {
                m_swapChain->Present(1, 0);
            }

            GraphicsDevice GraphicsDevice::Instance;
        }
    }
}
