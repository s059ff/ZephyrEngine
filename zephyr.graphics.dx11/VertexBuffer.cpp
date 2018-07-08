#include "zephyr.graphics.dx11\GraphicsDevice.h"
#include "zephyr.graphics.dx11\enums.h"
#include "zephyr.graphics.dx11\ConstantBuffer.h"

#include "VertexBuffer.h"

#define this (*this)

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void VertexBuffer::Create(int stride, int count, Accessibility access)
            {
                base::Create(stride, count, access, BufferBindFlags::VertexBuffer);
            }

            void VertexBuffer::Create(const void* source, int stride, int count, Accessibility access)
            {
                base::Create(source, stride, count, access, BufferBindFlags::VertexBuffer);
            }
        }
    }
}
