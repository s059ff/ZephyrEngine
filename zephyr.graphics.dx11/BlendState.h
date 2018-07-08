#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            enum class BlendOperation;
            enum class BlendFactor;

            class BlendState : public Interface<ID3D11BlendState>
            {
            public:

                void Create(BlendOperation operation);

                void Create(BlendOperation operation, BlendFactor srcFactor, BlendFactor destFactor);

                void Release();
            };
        }
    }
}
