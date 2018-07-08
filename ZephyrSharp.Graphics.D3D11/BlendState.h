#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ブレンディング ステートを表します。
        /// </summary>
        public ref class BlendState 
            : public INativeWrapper<zephyr::graphics::d3d11::BlendState>
        {
        public:

            /// <summary>
            /// ブレンドをしないブレンディング ステートを作成します。
            /// </summary>
            /// <param name="operation">( BlendOperation::None にすること )</param> 
            void Create(BlendOperation operation)
            {
                Native->Create((zephyr::graphics::d3d11::BlendOperation)operation);
            }

            /// <summary>
            /// 新しいブレンディング ステートを作成します。
            /// </summary>
            /// <param name="operation">演算方法。</param> 
            /// <param name="srcFactor">ピクセル シェーダが出力した色情報に対する係数。</param> 
            /// <param name="destFactor">レンダリング ターゲットから読み取った色情報に対する係数。</param> 
            void Create(BlendOperation operation, BlendFactor srcFactor, BlendFactor destFactor)
            {
                Native->Create(
                    (zephyr::graphics::d3d11::BlendOperation)operation,
                    (zephyr::graphics::d3d11::BlendFactor)srcFactor,
                    (zephyr::graphics::d3d11::BlendFactor)destFactor);
            }
        };
    }
}
