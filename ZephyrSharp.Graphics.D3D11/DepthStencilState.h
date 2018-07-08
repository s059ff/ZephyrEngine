#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// 深度・ステンシルバッファ ステートを表します。
        /// </summary>
        public ref class DepthStencilState
            : public INativeWrapper<zephyr::graphics::d3d11::DepthStencilState>
        {
        public:

            /// <summary>
            /// 新しいブレンディング ステートを作成します。
            /// </summary>
            /// <param name="depthEnable">深度バッファを使用する場合は true。</param> 
            /// <param name="stencilEnable">ステンシルバッファを使用する場合は true。</param> 
            /// <param name="depthWriteEnable">深度バッファへの書き込みを許可する場合は true。</param> 
            void Create(bool depthEnable, bool stencilEnable, bool depthWriteEnable)
            {
                Native->Create(depthEnable, stencilEnable, depthWriteEnable);
            }
        };
    }
}
