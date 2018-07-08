#pragma once

#include "common.h"
#include "Buffer.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class ConstantBuffer : public Buffer
            {
                using base = Buffer;

            public:

                void Create(const void* source, int size);

                void Create(int size) { this->Create(nullptr, size); };

                void Update(const void* source);

                template <typename T>
                void Update(const T& source) { this->Update((const void*)&source); }
            };
        }
    }
}
