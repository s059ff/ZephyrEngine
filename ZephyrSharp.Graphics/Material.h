#pragma once

#include "common.h"
#include "Color.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// 物体のマテリアル情報を表します。
        /// </summary>
        public value struct Material
        {
            /// <summary>
            /// アンビエント カラーを取得または設定します。
            /// </summary>
            Color Ambient;

            /// <summary>
            /// ディフューズ カラーを取得または設定します。
            /// </summary>
            Color Diffuse;

            /// <summary>
            /// スペキュラー カラーを取得または設定します。
            /// </summary>
            Color Specular;

            /// <summary>
            /// スペキュラー パワーを取得または設定します。
            /// </summary>
            float Power;
        };
    }
}
