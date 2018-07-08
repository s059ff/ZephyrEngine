#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            enum class CullMode;
            enum class FillMode;

            class RasterizerState : public Interface<ID3D11RasterizerState>
            {
            public:

                void Create(CullMode cullMode, FillMode fillMode);

                void Release();
            };
        }
    }
}
