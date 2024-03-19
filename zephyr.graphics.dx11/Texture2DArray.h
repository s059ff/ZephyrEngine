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
            enum class Format;

            class Texture2DArray : public Interface<ID3D11Texture2D>
            {
            public:

                void Create(int width, int height, int count, Format format, Accessibility access, BufferBindFlags flags);

                void Create(const void* source, int width, int height, int count, Format format, Accessibility access, BufferBindFlags flags);

                void Create(const string& path, Accessibility access);

                void Create(const string& path, int width, int height, Accessibility access);

                void Create(string paths[], int count, Accessibility access);

                void CreateCubeMap(const void* source, int width, int height, Format format, Accessibility access, BufferBindFlags flags);

                void CreateCubeMap(const string& path, Accessibility access, BufferBindFlags flags);

                void Release();

                void Lock(Accessibility access, int index);

                void Unlock();

                inline void* Access(int x, int y)
                {
                    assert(m_locked_ptr != nullptr);
                    assert(x >= 0&& x < m_width);
                    assert(y >= 0&& y < m_height);
                    return (byte*)m_locked_ptr + m_row_pitch * y + x * m_stride;
                }

                inline const void* Access(int x, int y) const
                {
                    assert(m_locked_ptr != nullptr);
                    assert(x >= 0&& x < m_width);
                    assert(y >= 0&& y < m_height);
                    return (byte*)m_locked_ptr + m_row_pitch * y + x * m_stride;
                }

                template <typename T>
                inline T& Access(int x, int y)
                {
                    assert(sizeof(T) == m_stride);
                    return *(T*)(Access(x, y));
                }

                template <typename T>
                inline const T& Access(int x, int y) const
                {
                    assert(sizeof(T) == m_stride);
                    return *(const T*)(Access(x, y));
                }

                template <typename T>
                inline T Read(int x, int y) const
                {
                    return this->Access<T>(x, y);
                }

                template <typename T>
                inline void Write(int x, int y, T value)
                {
                    this->Access<T>(x, y) = value;
                }

            public:

                READONLY_PROPERTY(int, width, { return m_width; });

                READONLY_PROPERTY(int, height, { return m_height; });

                READONLY_PROPERTY(int, length, { return m_length; });

                READONLY_PROPERTY(int, stride, { return m_stride; });

                READONLY_PROPERTY(void*, locked_ptr, { return m_locked_ptr; });

            private:

                int m_width = 0, m_height = 0, m_length = 0;

                int m_stride = 0;

                void* m_locked_ptr = nullptr;

                int m_locked_index = 0;

                int m_row_pitch = 0;
            };
        }
    }
}
