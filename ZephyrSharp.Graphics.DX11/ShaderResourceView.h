#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        ref class ShaderResourceView : public INativeWrapper<zephyr::graphics::dx11::ShaderResourceView>
        {
        };
    }
}
