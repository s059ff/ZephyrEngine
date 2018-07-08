#pragma once

#include "Color.h"

namespace zephyr
{
    namespace graphics
    {
        /// <summary>
        /// グラフィックスモデルの材質を表します。
        /// </summary>
        struct Material
        {
            /// <summary>
            /// このクラスの新しいインスタンスを初期化します。
            /// </summary>
            Material() :
                ambient(0, 0, 0, 1),
                diffuse(1, 1, 1, 1),
                specular(0, 0, 0, 1),
                power(0)
            {
            }

            /// <summary>
            /// アンビエント カラーを取得または設定します。
            /// </summary>
            Color ambient;

            /// <summary>
            /// ディフューズ カラーを取得または設定します。
            /// </summary>
            Color diffuse;

            /// <summary>
            /// スペキュラー カラーを取得または設定します。
            /// </summary>
            Color specular;

            /// <summary>
            /// スペキュラー パワーを取得または設定します。
            /// </summary>
            float power;
        };
    }
}
