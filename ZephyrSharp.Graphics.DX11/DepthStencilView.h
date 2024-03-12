#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        ref class DepthStencilView : public INativeWrapper<zephyr::graphics::dx11::DepthStencilView>
        {
        };
    }
}
