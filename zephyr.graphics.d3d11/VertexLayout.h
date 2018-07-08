#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class VertexElement;
            class VertexShader;

            class VertexLayout : public Interface<ID3D11InputLayout>
            {
            public:

                void Create(const VertexElement elements[], int elementsCount, VertexShader& shader);

                template <size_t N>
                void Create(const VertexElement(&elements)[N], VertexShader& shader)
                {
                    this->Create(elements, N, shader);
                }

                void Release();
            };
        }
    }
}
