#pragma once

#include "zephyr\string.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.gamesystem\EntityComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// ライトを表します。
            /// </summary>
            class LightComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ライトの向きを設定します。
                /// </summary>
                /// <param name="eye">ライトの座標。</param> 
                /// <param name="at">注視先の座標。</param> 
                void LookAt(linalg::Vector3 eye, linalg::Vector3 at);
            };
        }
    }
}
