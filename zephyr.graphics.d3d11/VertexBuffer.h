#pragma once

#include "common.h"
#include "ArrayBuffer.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class VertexBuffer : public ArrayBuffer
            {
                using base = ArrayBuffer;

            public:

                void Create(int stride, int count, Accessibility access);

                void Create(const void* source, int stride, int count, Accessibility access);

                template <typename V>
                inline void Create(int count, Accessibility access)
                {
                    this->Create(sizeof(V), count, access);
                }

                template <typename V>
                inline void Create(const V source[], int count, Accessibility access)
                {
                    this->Create(source, sizeof(V), count, access);
                }

                template <typename V, size_t N>
                inline void Create(const V(&source)[N], Accessibility access)
                {
                    this->Create(source, N, access);
                }

                void* Access(int index)
                {
                    return base::Access(index);
                }

                const void* Access(int index) const
                {
                    return base::Access(index);
                }

                template <typename V>
                inline V& Access(int index)
                {
                    assert(sizeof(V) == stride);
                    return *(V*)(Access(index));
                }

                template <typename V>
                inline const V& Access(int index) const
                {
                    assert(sizeof(V) == stride);
                    return *(const V*)(Access(index));
                }

                template <typename V>
                inline void Write(int index, const V& value)
                {
                    this->Access<V>(index) = value;
                }

                template <typename V>
                inline const V& Read(int index) const
                {
                    return this->Access<V>(index);
                }

                template <typename V>
                inline V* Begin()
                {
                    return (V*)base::Begin();
                }

                template <typename V>
                inline const V* Begin() const
                {
                    return (const V*)base::Begin();
                }

                template <typename V>
                inline V* End()
                {
                    return (V*)base::End();
                }

                template <typename V>
                inline const V* End() const
                {
                    return (const V*)base::End();
                }
            };
        }
    }
}
