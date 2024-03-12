#pragma once

#include "common.h"
#include "ArrayBuffer.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class IndexBuffer : public ArrayBuffer
            {
                using base = ArrayBuffer;

            public:

                void Create(int stride, int count, Accessibility access);

                void Create(const void* source, int stride, int count, Accessibility access);

                template <typename I>
                inline void Create(int count, Accessibility access)
                {
                    this->Create(sizeof(I), count, access);
                }

                template <typename I>
                inline void Create(const I source[], int count, Accessibility access)
                {
                    this->Create(source, sizeof(I), count, access);
                }

                template <typename I, size_t N>
                inline void Create(const I(&source)[N], Accessibility access)
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

                template <typename I>
                inline I& Access(int index)
                {
                    assert(sizeof(I) == stride);
                    return *(I*)(Access(index));
                }

                template <typename I>
                inline const I& Access(int index) const
                {
                    assert(sizeof(I) == stride);
                    return *(const I*)(Access(index));
                }

                template <typename I>
                inline void Write(int index, const I& value)
                {
                    this->Access<I>(index) = value;
                }

                template <typename I>
                inline const I& Read(int index) const
                {
                    return this->Access<I>(index);
                }

                template <typename I>
                inline I* Begin()
                {
                    return (I*)base::Begin();
                }

                template <typename I>
                inline const I* Begin() const
                {
                    return (const I*)base::Begin();
                }

                template <typename I>
                inline I* End()
                {
                    return (I*)base::End();
                }

                template <typename I>
                inline const I* End() const
                {
                    return (const I*)base::End();
                }
            };
        }
    }
}
