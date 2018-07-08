#include "GraphicsDevice.h"
#include "enums.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"

#define this (*this)

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
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
