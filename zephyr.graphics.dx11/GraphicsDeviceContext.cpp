#include "zephyr\runtime_assert.h"
#include "zephyr.graphics\Window.h"
#include "zephyr.graphics\Color.h"

#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"
#include "Texture2D.h"
#include "RenderTargetView.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexLayout.h"
#include "InstanceBuffer.h"
#include "BlendState.h"
#include "RasterizerState.h"
#include "enums.h"
#include "DepthStencilState.h"

#define this (*this)

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            GraphicsDeviceContext GraphicsDeviceContext::Instance;

            void GraphicsDeviceContext::Create(IDXGISwapChain* swapChain, ID3D11DeviceContext* deviceContext, const Window& window, bool fullScreen)
            {
                this.reset(deviceContext);
                m_swapChain.reset(swapChain);

                // バックバッファ取得
                Texture2D backBuffer;
                auto hr = GraphicsDeviceContext::Instance.m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBuffer);
                runtime_assert(SUCCEEDED(hr));

                // レンダーターゲットビューを生成
                hr = GraphicsDevice::Instance->CreateRenderTargetView(backBuffer.ptr, NULL, &GraphicsDeviceContext::Instance.m_renderTargetView);
                runtime_assert(SUCCEEDED(hr));

                // 深度バッファを作成
                GraphicsDeviceContext::Instance.m_depthStencil.CreateDepthStencil(window.width, window.height);
                GraphicsDeviceContext::Instance.m_depthStencilView.Create(GraphicsDeviceContext::Instance.m_depthStencil);

                // 出力マネージャにレンダーターゲットビューを設定
                ID3D11RenderTargetView* renderTargetViews[] = { GraphicsDeviceContext::Instance.m_renderTargetView.ptr };
                GraphicsDeviceContext::Instance->OMSetRenderTargets(1, renderTargetViews, GraphicsDeviceContext::Instance.m_depthStencilView.ptr);

                // 深度ステートの設定
                GraphicsDeviceContext::Instance.m_depthStencilState.Create(true, false, true);
                GraphicsDeviceContext::Instance->OMSetDepthStencilState(GraphicsDeviceContext::Instance.m_depthStencilState.ptr, 0);

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
                GraphicsDeviceContext::Instance->RSSetViewports(1, &vp);

                // 
                m_swapChain->SetFullscreenState(fullScreen, NULL);
            }

            void GraphicsDeviceContext::Release()
            {
                // すべてのリソースとパイプラインとのバインドを解除する
                if (this.available())
                    this->ClearState();

                m_renderTargetView.reset();
                m_swapChain.reset();
                m_renderTargetView.reset();
                m_depthStencil.reset();
                m_depthStencilView.reset();
                m_depthStencilState.reset();

                base::reset();
            }

            void GraphicsDeviceContext::UnbindAllResources()
            {
                // すべてのリソースとパイプラインとのバインドを解除する
                this->ClearState();
            }

            void GraphicsDeviceContext::Clear(const Color& clearColor)
            {
                float r = clearColor.r;
                float g = clearColor.g;
                float b = clearColor.b;
                float a = clearColor.a;
                float rgba[] = { r,g,b,a };

                RenderTargetView targetView;
                DepthStencilView depthView;
                this->OMGetRenderTargets(1, &targetView, &depthView);
                if (targetView.available())
                    this->ClearRenderTargetView(targetView.ptr, rgba);
                if (depthView.available())
                    this->ClearDepthStencilView(depthView.ptr, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
            }
            
            void GraphicsDeviceContext::SetVertexShader(VertexShader& shader)
            {
                this->VSSetShader(shader.ptr, NULL, 0);
            }

            void GraphicsDeviceContext::SetGeometryShader(GeometryShader& shader)
            {
                this->GSSetShader(shader.ptr, NULL, 0);
            }

            void GraphicsDeviceContext::SetPixelShader(PixelShader& shader)
            {
                this->PSSetShader(shader.ptr, NULL, 0);
            }

            void GraphicsDeviceContext::SetVertexBuffer(VertexBuffer& buffer, int slot)
            {
                ID3D11Buffer* _buffers[] = { buffer.ptr };
                UINT _strides[] = { (UINT)buffer.stride };
                UINT _offsets[] = { (UINT)0 };

                this->IASetVertexBuffers(slot, 1, _buffers, _strides, _offsets);
            }

            void GraphicsDeviceContext::SetVertexBuffers(VertexBuffer buffers[], int bufferCount, int startSlot)
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

                this->IASetVertexBuffers(startSlot, bufferCount, _buffers, _strides, _offsets);
            }

            void GraphicsDeviceContext::SetIndexBuffer(IndexBuffer& buffer)
            {
                this->IASetIndexBuffer(buffer.ptr, DXGI_FORMAT_R32_UINT, 0);
            }

            void GraphicsDeviceContext::SetInstanceBuffer(InstanceBuffer& buffer, int slot)
            {
                this.SetVertexBuffer(buffer, slot);
            }

            void GraphicsDeviceContext::SetInstanceBuffers(InstanceBuffer buffers[], int bufferCount, int startSlot)
            {
                this.SetVertexBuffers(buffers, bufferCount, startSlot);
            }

            void GraphicsDeviceContext::SetVertexLayout(VertexLayout& layout)
            {
                this->IASetInputLayout(layout.ptr);
            }

            void GraphicsDeviceContext::SetPrimitiveTopology(PrimitiveTopology topology)
            {
                this->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)topology);
            }

            void GraphicsDeviceContext::SetBlendState(BlendState& state)
            {
                float factor[] = { 0,0,0,0 };
                this->OMSetBlendState(state.ptr, factor, 0xffffffff);
            }

            void GraphicsDeviceContext::SetRasterizerState(RasterizerState& state)
            {
                this->RSSetState(state.ptr);
            }

            void GraphicsDeviceContext::SetDepthStencilState(DepthStencilState& state)
            {
                this->OMSetDepthStencilState(state.ptr, 0);
            }

            void GraphicsDeviceContext::SetRenderTargetAndDepthStencil(RenderTargetView& view1, DepthStencilView& view2)
            {
                ID3D11RenderTargetView* renderTargetViews[] = { view1.ptr };
                this->OMSetRenderTargets(1, renderTargetViews, view2.ptr);
            }

            void GraphicsDeviceContext::SetRenderTargetAndDepthStencil(nullptr_t, DepthStencilView& view2)
            {
                ID3D11RenderTargetView* renderTargetViews[] = { nullptr };
                this->OMSetRenderTargets(1, renderTargetViews, view2.ptr);
            }

            void GraphicsDeviceContext::SetRenderTargetAndDepthStencil(RenderTargetView& view1, nullptr_t)
            {
                ID3D11RenderTargetView* renderTargetViews[] = { view1.ptr };
                this->OMSetRenderTargets(1, renderTargetViews, nullptr);
            }

            void GraphicsDeviceContext::ResetRenderTargetAndDepthStencil()
            {
                ID3D11RenderTargetView* renderTargetViews[] = { m_renderTargetView.ptr };
                this->OMSetRenderTargets(1, renderTargetViews, m_depthStencilView.ptr);
            }

            void GraphicsDeviceContext::SetViewport(int width, int height)
            {
                CD3D11_VIEWPORT	viewport(0.0f, 0.0f, (float)width, (float)height);
                this->RSSetViewports(1, &viewport);
            }

            void GraphicsDeviceContext::Draw(int vertexCount, int startVertexLocation)
            {
                this->Draw(vertexCount, startVertexLocation);
            }

            void GraphicsDeviceContext::DrawIndexed(int indexCount, int startIndexLocation, int baseVertexLocation)
            {
                this->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
            }

            void GraphicsDeviceContext::DrawInstanced(int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation)
            {
                this->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
            }

            void GraphicsDeviceContext::DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation)
            {
                this->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startIndexLocation);
            }

            void GraphicsDeviceContext::Present(int syncInterval)
            {
                m_swapChain->Present(syncInterval, 0);
            }
        }
    }
}
