#pragma once

#include "common.h"
#include "enums.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class GraphicsDevice : public Interface<ID3D11Device>
            {
            public:

                void Create(const Window& window, bool fullscreen);

                void Release();

            public:

                static GraphicsDevice Instance;
            };
        }
    }
}
