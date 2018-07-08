#pragma once

#include "common.h"
#include "Texture2D.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class DepthStencilState : public Interface<ID3D11DepthStencilState>
            {
            public:

                void Create(bool depthEnable, bool stencilEnable, bool depthWriteEnable);

                void Release();
            };
        }
    }
}
