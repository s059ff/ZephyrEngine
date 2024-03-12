#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// サンプラー ステートを表します。
        /// </summary>
        public ref class SamplerState
            : public INativeWrapper<zephyr::graphics::dx11::SamplerState>
        {
        public:

            /// <summary>
            /// サンプラー ステートを作成します。
            /// </summary>
            /// <param name="addressU">U 座標のアドレッシングモード。</param> 
            /// <param name="addressV">V 座標のアドレッシングモード。</param> 
            /// <param name="addressW">W 座標のアドレッシングモード。</param> 
            void Create(TextureAddressMode addressU, TextureAddressMode addressV, TextureAddressMode addressW)
            {
                Native->Create(
                    (zephyr::graphics::dx11::TextureAddressMode)addressU, 
                    (zephyr::graphics::dx11::TextureAddressMode)addressV, 
                    (zephyr::graphics::dx11::TextureAddressMode)addressW);
            }

            /// <summary>
            /// 比較サンプラー ステートを作成します。
            /// </summary>
            void CreateComparator()
            {
                Native->CreateComparator();
            }
        };
    }
}
