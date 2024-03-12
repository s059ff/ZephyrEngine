#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            enum class Accessibility;
            enum class BufferBindFlags;
            enum class CpuAccessibility;
            enum class Usage;

            class Buffer : public Interface<ID3D11Buffer>
            {
            public:

                void Create(int size, Accessibility access, BufferBindFlags flags)
                {
                    this->Create(nullptr, size, access, flags);
                }

                void Create(const void* source, int size, Accessibility access, BufferBindFlags flags);

                void Create(const void* source, int size, CpuAccessibility cpuAccess, BufferBindFlags flags, Usage usage);

                void Release();

                void Lock(Accessibility access);

                void Unlock();

                void* Begin() { return m_locked_ptr; }

                const void* Begin() const { return m_locked_ptr; }

                void* End() { return (byte*)m_locked_ptr + m_size; }

                const void* End() const { return (byte*)m_locked_ptr + m_size; }

            public:

                READONLY_PROPERTY(int, size, const{ return m_size; });

                READONLY_PROPERTY(void*, locked_ptr, { return m_locked_ptr; });

                READONLY_PROPERTY(const void*, const_locked_ptr, const{ return m_locked_ptr; });

            private:

                // バッファサイズ
                int m_size;

                // ロックした領域
                void* m_locked_ptr = nullptr;
            };
        }
    }
}
