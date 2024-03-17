#include <dxgidebug.h>

#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"

#define this (*this)

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            GraphicsDevice GraphicsDevice::Instance;

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
                D3D_FEATURE_LEVEL actuallyFeatureLevel;
                UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);

                // デバイスとスワップチェインの作成
                UINT flags = 0;
#ifdef _DEBUG
                flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
                HRESULT hr = S_OK;
                IDXGISwapChain* createdSwapChain = nullptr;
                ID3D11DeviceContext* createdDeviceContext = nullptr;
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
                        &createdSwapChain,
                        &this,
                        &actuallyFeatureLevel,
                        &createdDeviceContext);
                    if (SUCCEEDED(hr))
                        break;
                }
                runtime_assert(SUCCEEDED(hr), "Failed to create d3d11 device.");

                GraphicsDeviceContext::Instance.Create(createdSwapChain, createdDeviceContext, window, fullscreen);
            }

            void GraphicsDevice::Release()
            {
#ifdef _DEBUG
                if (this.available())
                {
                    HMODULE hDll = GetModuleHandleA("dxgidebug.dll");
                    auto DXGIGetDebugInterface = (HRESULT(*)(const IID&, void**))GetProcAddress(hDll, "DXGIGetDebugInterface");
                    runtime_assert(DXGIGetDebugInterface != nullptr);

                    com_ptr<IDXGIDebug> pDxgiDebug;
                    runtime_assert(SUCCEEDED(DXGIGetDebugInterface(__uuidof(IDXGIDebug), reinterpret_cast<void**>(&pDxgiDebug))));
                    runtime_assert(SUCCEEDED(pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL)));
                }
#endif
            }
        }
    }
}
