#include "zephyr\runtime_assert.h"

#include "GraphicsDevice.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "RenderTargetView.h"

#define this (*this)

#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
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