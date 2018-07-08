#include <d3d11.h>

#include "zephyr\runtime_assert.h"
#include "zephyr.graphics.dx11\GraphicsDevice.h"
#include "zephyr.graphics.dx11\Texture2D.h"
#include "zephyr.graphics.dx11\Texture2DArray.h"

#include "RenderTargetView.h"

#define this (*this)

#define device GraphicsDevice::Instance.Device
#define context GraphicsDevice::Instance.DeviceContext

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void RenderTargetView::Create(Texture2D& texture)
            {
                this.Release();

                HRESULT hr = device->CreateRenderTargetView(texture.ptr, nullptr, &this);
                assert(SUCCEEDED(hr));
            }

            void RenderTargetView::Release()
            {
                this.reset();
            }
        }
    }
}