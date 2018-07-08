#include <d3d11.h>

#include "zephyr\runtime_assert.h"
#include "zephyr.graphics.dx11\GraphicsDevice.h"
#include "zephyr.graphics.dx11\Texture2D.h"
#include "zephyr.graphics.dx11\Texture2DArray.h"

#include "ShaderResourceView.h"

#define this (*this)

#define device GraphicsDevice::Instance.Device
#define context GraphicsDevice::Instance.DeviceContext

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
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
