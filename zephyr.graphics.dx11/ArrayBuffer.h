#pragma once

#include "common.h"
#include "Buffer.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class ArrayBuffer : public Buffer
            {
                using base = Buffer;

            public:

                void Create(int stride, int count, Accessibility access, BufferBindFlags flags)
                {
                    this->Create(nullptr, stride, count, access, flags);
                }

                void Create(const void* source, int stride, int count, Accessibility access, BufferBindFlags flags)
                {
                    base::Create(source, stride * count, access, flags);

                    m_stride = stride;
                    m_count = count;
                }

                void Release()
                {
                    base::Release();

                    m_count = 0;
                    m_stride = 0;
                }

                inline void* Access(int index)
                {
                    assert(locked_ptr != nullptr);
                    assert(count > index);
                    return (byte*)locked_ptr + stride * index;
                }

                inline const void* Access(int index) const
                {
                    assert(const_locked_ptr != nullptr);
                    assert(count > index);
                    return (byte*)const_locked_ptr + stride * index;
                }

            public:

                READONLY_PROPERTY(int, stride, const{ return m_stride; });

                READONLY_PROPERTY(int, count, const{ return m_count; });

            private:

                int m_stride;

                int m_count;
            };
        }
    }
}
