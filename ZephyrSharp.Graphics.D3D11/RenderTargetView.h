#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        ref class RenderTargetView : public INativeWrapper<zephyr::graphics::d3d11::RenderTargetView>
        {
        };
    }
}
