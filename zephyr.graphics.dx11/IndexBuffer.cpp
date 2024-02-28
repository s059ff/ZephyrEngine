#include "enums.h"
#include "IndexBuffer.h"

#define this (*this)

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void IndexBuffer::Create(int stride, int count, Accessibility access)
            {
                base::Create(stride, count, access, BufferBindFlags::IndexBuffer);
            }

            void IndexBuffer::Create(const void* source, int stride, int count, Accessibility access)
            {
                base::Create(source, stride, count, access, BufferBindFlags::IndexBuffer);
            }
        }
    }
}
