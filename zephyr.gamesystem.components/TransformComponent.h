#pragma once

#include "zephyr\property.h"
#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.gamesystem\EntityComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// 3D 空間におけるエンティティの位置を表します。
            /// </summary>
            class TransformComponent : public EntityComponent
            {
            public:

                TransformComponent()
                {
                    this->Matrix.identity();
                }
                
                /// <summary>
                /// エンティティの姿勢行列を表します。
                /// </summary>
                linalg::Matrix4x3 Matrix;

            public:

                /// <summary>
                /// エンティティの +X 方向のベクトルを取得します。
                /// </summary>
                READONLY_PROPERTY(linalg::Vector3, Rightward, const{ return linalg::Vector3(Matrix.m11, Matrix.m12, Matrix.m13); });

                /// <summary>
                /// エンティティの +Y 方向のベクトルを取得します。
                /// </summary>
                READONLY_PROPERTY(linalg::Vector3, Upward, const{ return linalg::Vector3(Matrix.m21, Matrix.m22, Matrix.m23); });

                /// <summary>
                /// エンティティの +Z 方向のベクトルを取得します。
                /// </summary>
                READONLY_PROPERTY(linalg::Vector3, Forward, const{ return linalg::Vector3(Matrix.m31, Matrix.m32, Matrix.m33); });

                /// <summary>
                /// エンティティの位置を表します。
                /// </summary>
                READWRITE_PROPERTY(linalg::Vector3, Position, const{ return Matrix.position; }, { Matrix.position = value; });
            };
        }
    }
}
