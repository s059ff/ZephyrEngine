#pragma once

#include "zephyr\property.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.gamesystem\EntityComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// カメラを表します。
            /// </summary>
            class CameraComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ある地点から別のある地点を注視するようにカメラの向きを設定します。
                /// </summary>
                /// <param name="eye">カメラの座標。</param> 
                /// <param name="at">注視先の座標。</param> 
                void LookAt(linalg::Vector3 eye, linalg::Vector3 at);

                /// <summary>
                /// ビューイング行列を取得します。
                /// </summary>
                READONLY_PROPERTY(linalg::Matrix4x3, ViewingMatrix, const;);
            };
        }
    }
}
