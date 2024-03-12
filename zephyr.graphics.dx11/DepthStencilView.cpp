#include "GraphicsDevice.h"
#include "enums.h"
#include "Texture2D.h"
#include "DepthStencilView.h"

#define this (*this)
#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void DepthStencilView::Create(Texture2D& depthStencil)
            {
                D3D11_DEPTH_STENCIL_VIEW_DESC desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.Format = DXGI_FORMAT_UNKNOWN;
                desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

                device->CreateDepthStencilView(depthStencil.ptr, &desc, &this);
            }

            void DepthStencilView::CreateDepthMapView(Texture2D& texture)
            {
                CD3D11_DEPTH_STENCIL_VIEW_DESC desc(D3D11_DSV_DIMENSION_TEXTURE2D, DXGI_FORMAT_D24_UNORM_S8_UINT, 0, 0, 1, 0);

                HRESULT hr = device->CreateDepthStencilView(texture.ptr, &desc, &this);
                assert(SUCCEEDED(hr));
            }

            void DepthStencilView::Release()
            {
                this.reset();
            }
        }
    }
}
