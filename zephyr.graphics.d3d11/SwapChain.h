#pragma once

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace d3d11
        {
            class SwapChain : public Interface<IDXGISwapChain>
            {
            };
        }
    }
}
