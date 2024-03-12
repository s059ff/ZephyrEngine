#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// スワップチェインを表します。
        /// </summary>
        public ref class SwapChain
            : public INativeWrapper<zephyr::graphics::dx11::SwapChain>
        {
        };
    }
}
