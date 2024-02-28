#include "GraphicsDevice.h"
#include "enums.h"
#include "SamplerState.h"

#define this (*this)
#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void SamplerState::Create(TextureAddressMode addressU, TextureAddressMode addressV, TextureAddressMode addressW)
            {
                D3D11_SAMPLER_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                
                // Set default parameters.
                desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
                desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
                desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
                desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
                desc.MinLOD = -FLT_MAX;
                desc.MaxLOD = FLT_MAX;
                desc.MipLODBias = 0.0f;
                desc.MaxAnisotropy = 1;
                desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
                desc.BorderColor[0] = 1;
                desc.BorderColor[1] = 1;
                desc.BorderColor[2] = 1;
                desc.BorderColor[3] = 1;

                // Set specified parameters.
                desc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)addressU;
                desc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)addressV;
                desc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)addressW;

                HRESULT hr = device->CreateSamplerState(&desc,&this);
                runtime_assert(SUCCEEDED(hr));
            }

            void SamplerState::CreateComparator()
            {
                D3D11_SAMPLER_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
                desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
                desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
                desc.BorderColor[0] = 1.0f;
                desc.BorderColor[1] = 1.0f;
                desc.BorderColor[2] = 1.0f;
                desc.BorderColor[3] = 1.0f;
                desc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
                desc.Filter = D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR;
                desc.MaxAnisotropy = 1;
                desc.MipLODBias = 0;
                desc.MinLOD = -FLT_MAX;
                desc.MaxLOD = +FLT_MAX;

                HRESULT hr = device->CreateSamplerState(&desc, &this);
                runtime_assert(SUCCEEDED(hr));
            }
        }
    }
}
