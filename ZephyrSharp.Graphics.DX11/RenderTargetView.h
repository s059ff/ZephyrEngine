#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        ref class RenderTargetView : public INativeWrapper<zephyr::graphics::dx11::RenderTargetView>
        {
        };
    }
}
