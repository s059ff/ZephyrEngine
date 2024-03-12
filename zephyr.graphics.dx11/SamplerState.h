#pragma once

#include "common.h"
#include "enums.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class SamplerState : public Interface<ID3D11SamplerState>
            {
            public:

                void Create(TextureAddressMode addressU, TextureAddressMode addressV, TextureAddressMode addressW);

                void CreateComparator();
            };
        }
    }
}
