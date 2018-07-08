#include <d3d11.h>

#include "zephyr\runtime_assert.h"
#include "zephyr.graphics.dx11\GraphicsDevice.h"
#include "zephyr.graphics.dx11\VertexElement.h"
#include "zephyr.graphics.dx11\VertexShader.h"

#include "zephyr.graphics.dx11\GraphicsDevice.h"

#include "VertexLayout.h"

#define this (*this)
#define device GraphicsDevice::Instance.Device

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void VertexLayout::Create(const VertexElement elements[], int elementsCount, VertexShader& shader)
            {
                this.Release();

                static_assert(sizeof(D3D11_INPUT_ELEMENT_DESC) == sizeof(VertexElement), "");

                HRESULT hr = device->CreateInputLayout(
                    reinterpret_cast<const D3D11_INPUT_ELEMENT_DESC*>(elements),
                    elementsCount,
                    shader.bytecode.data(),
                    shader.bytecode.size(),
                   &this);
                runtime_assert(SUCCEEDED(hr));
            }

            void VertexLayout::Release()
            {
                this.reset();
            }
        }
    }
}
