#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        ref class DepthStencilView : public INativeWrapper<zephyr::graphics::d3d11::DepthStencilView>
        {
        };
    }
}
