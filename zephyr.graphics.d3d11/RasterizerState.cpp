#include "GraphicsDevice.h"
#include "enums.h"
#include "RasterizerState.h"

#define this (*this)
#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            void RasterizerState::Create(CullMode cullMode, FillMode fillMode)
            {
                D3D11_RASTERIZER_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.FillMode = (D3D11_FILL_MODE)fillMode;
                desc.CullMode = (D3D11_CULL_MODE)cullMode;
                desc.DepthClipEnable = false;
                desc.DepthBiasClamp = 0;
                desc.SlopeScaledDepthBias = 0;
                desc.ScissorEnable = false;
                desc.FrontCounterClockwise = false;     // "Front face" is clock wise.
                desc.MultisampleEnable = false;         // Multi sampling.
                desc.AntialiasedLineEnable = false;     // Line antialius.
                device->CreateRasterizerState(&desc,&this);
            }

            void RasterizerState::Release()
            {
                this.reset();
            }
        }
    }
}
