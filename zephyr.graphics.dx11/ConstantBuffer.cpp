#include "GraphicsDevice.h"
#include "GraphicsDeviceContext.h"
#include "enums.h"
#include "ConstantBuffer.h"

#define this (*this)
#define device GraphicsDevice::Instance
#define context GraphicsDeviceContext::Instance

#define UpdateWithSubresource FALSE

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            void ConstantBuffer::Create(const void* source, int size)
            {
#if UpdateWithSubresource
                base::Create(source, size, CpuAccessibility::None, BufferBindFlags::ConstantBuffer, Usage::Default);
#else
                base::Create(source, size, CpuAccessibility::Write, BufferBindFlags::ConstantBuffer, Usage::Dynamic);
#endif 
            }

            void ConstantBuffer::Update(const void* source)
            {
#if UpdateWithSubresource
                context->UpdateSubresource(this.ptr, 0, nullptr, source, 0, 0);
#else
                this.Lock(Accessibility::DynamicWriteOnly);
                assert(this.locked_ptr != nullptr);
                {
                    memcpy(this.locked_ptr, source, this.size);
                }
                this.Unlock();
#endif 
            }
        }
    }
}
