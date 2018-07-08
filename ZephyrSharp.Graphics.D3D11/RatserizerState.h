#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ラスタライザー ステートを表します。
        /// </summary>
        public ref class RasterizerState
            : public INativeWrapper<zephyr::graphics::d3d11::RasterizerState>
        {
        public:

            /// <summary>
            /// ラスタライザー ステートを作成します。
            /// </summary>
            /// <param name="cullMode">カリングの設定。</param> 
            /// <param name="fillMode">塗りつぶし領域の設定。</param> 
            void Create(CullMode cullMode, FillMode fillMode)
            {
                Native->Create((zephyr::graphics::d3d11::CullMode)cullMode, (zephyr::graphics::d3d11::FillMode)fillMode);
            }
        };
    }
}
