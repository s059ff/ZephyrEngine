#include "GraphicsDevice.h"
#include "enums.h"
#include "BlendState.h"

#define this (*this)
#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
#if 0
            void BlendState::Create(BlendStateTemplate temp)
            {
                D3D11_BLEND_DESC desc = { 0 };
                desc.AlphaToCoverageEnable = false;
                desc.IndependentBlendEnable = false;
                desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
                desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
                desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
                desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

                desc.RenderTarget[0].BlendEnable = false;
                desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
                desc.RenderTarget[0].DestBlend = D3D11_BLEND_DEST_COLOR;
                desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

                switch (temp)
                {
                case BlendStateTemplate::NoBlend:
                    desc.RenderTarget[0].BlendEnable = false;
                    break;

                case BlendStateTemplate::Addition:
                    desc.RenderTarget[0].BlendEnable = true;
                    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
                    desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
                    break;

                case BlendStateTemplate::Subtraction:
                    desc.RenderTarget[0].BlendEnable = true;
                    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
                    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
                    desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
                    break;

                case BlendStateTemplate::Multiplication:
                    desc.RenderTarget[0].BlendEnable = true;
                    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ZERO;
                    desc.RenderTarget[0].DestBlend = D3D11_BLEND_SRC_COLOR;
                    break;

                case BlendStateTemplate::HalfAddition:
                    desc.RenderTarget[0].BlendEnable = true;
                    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
                    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                    break;

                case BlendStateTemplate::Reverse:
                    desc.RenderTarget[0].BlendEnable = true;
                    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_DEST_COLOR;
                    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;
                    break;

                case BlendStateTemplate::AlphaBlend:
                    desc.RenderTarget[0].BlendEnable = true;
                    desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
                    desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
                    desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                    break;
                default:
                    break;
                }
            }
#endif // 0

            void BlendState::Create(BlendOperation operation)
            {
                D3D11_BLEND_DESC desc = { 0 };
                desc.AlphaToCoverageEnable = false;
                desc.IndependentBlendEnable = false;
                desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
                desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
                desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
                desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

                desc.RenderTarget[0].BlendEnable = (operation != BlendOperation::None);
                desc.RenderTarget[0].SrcBlend = (D3D11_BLEND)BlendFactor::One;
                desc.RenderTarget[0].DestBlend = (D3D11_BLEND)BlendFactor::Zero;
                desc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)operation;

                device->CreateBlendState(&desc,&this);
            }

            void BlendState::Create(BlendOperation operation, BlendFactor srcFactor, BlendFactor destFactor)
            {
                D3D11_BLEND_DESC desc = { 0 };
                desc.AlphaToCoverageEnable = false;
                desc.IndependentBlendEnable = false;
                desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
                desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
                desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
                desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

                desc.RenderTarget[0].BlendEnable = (operation != BlendOperation::None);
                desc.RenderTarget[0].SrcBlend = (D3D11_BLEND)srcFactor;
                desc.RenderTarget[0].DestBlend = (D3D11_BLEND)destFactor;
                desc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)operation;

                device->CreateBlendState(&desc,&this);
            }

            void BlendState::Release()
            {
                this.reset();
            }
        }
    }
}
