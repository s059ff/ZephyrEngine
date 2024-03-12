#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class Texture2D;

            class RenderTargetView : public Interface<ID3D11RenderTargetView>
            {
            public:

                void Create(Texture2D& texture);

                void Release();
            };
        }
    }
}
