#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �X���b�v�`�F�C����\���܂��B
        /// </summary>
        public ref class SwapChain
            : public INativeWrapper<zephyr::graphics::d3d11::SwapChain>
        {
        };
    }
}
