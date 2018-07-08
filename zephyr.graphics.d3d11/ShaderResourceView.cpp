#include "zephyr\runtime_assert.h"

#include "GraphicsDevice.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "ShaderResourceView.h"

#define this (*this)

#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            void ShaderResourceView::Create(Texture2D& texture)
            {
                this.Release();

                HRESULT hr = device->CreateShaderResourceView(texture.ptr, nullptr, &this);
                assert(SUCCEEDED(hr));
            }

            void ShaderResourceView::Create(Texture2DArray& textureArray)
            {
                this.Release();

                HRESULT hr = device->CreateShaderResourceView(textureArray.ptr, nullptr, &this);
                assert(SUCCEEDED(hr));
            }

            void ShaderResourceView::CreateDepthMapView(Texture2D& texture)
            {
                this.Release();

                CD3D11_SHADER_RESOURCE_VIEW_DESC desc(D3D11_SRV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R24_UNORM_X8_TYPELESS, 0, 1, 0, 1);

                HRESULT hr = device->CreateShaderResourceView(texture.ptr, &desc, &this);
                assert(SUCCEEDED(hr));
            }

            void ShaderResourceView::Release()
            {
                this.reset();
            }
        }
    }
}
