#include "GraphicsDevice.h"
#include "enums.h"
#include "Texture2D.h"
#include "DepthStencilState.h"

#define this (*this)

#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            void DepthStencilState::Create(bool depthEnable, bool stencilEnable, bool depthWriteEnable)
            {
                this.Release();

                D3D11_DEPTH_STENCIL_DESC desc;
                ZeroMemory(&desc, sizeof(desc));

                // Set default parameters.
                desc.DepthEnable = TRUE;
                desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
                desc.DepthFunc = D3D11_COMPARISON_LESS;
                desc.StencilEnable = FALSE;
                desc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
                desc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

                desc.DepthEnable = depthEnable;
                desc.DepthWriteMask = depthWriteEnable ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
                desc.DepthFunc = depthEnable ? D3D11_COMPARISON_LESS : D3D11_COMPARISON_ALWAYS;
                desc.StencilEnable = stencilEnable;
                device->CreateDepthStencilState(&desc,&this);
            }

            void DepthStencilState::Release()
            {
                this.reset();
            }
        }
    }
}
