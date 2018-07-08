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
            /// 3D ��Ԃɂ�����G���e�B�e�B�̈ʒu��\���܂��B
            /// </summary>
            class TransformComponent : public EntityComponent
            {
            public:

                TransformComponent()
                {
                    this->Matrix.identity();
                }
                
                /// <summary>
                /// �G���e�B�e�B�̎p���s���\���܂��B
                /// </summary>
                linalg::Matrix4x3 Matrix;

            public:

                /// <summary>
                /// �G���e�B�e�B�� +X �����̃x�N�g�����擾���܂��B
                /// </summary>
                READONLY_PROPERTY(linalg::Vector3, Rightward, const{ return linalg::Vector3(Matrix.m11, Matrix.m12, Matrix.m13); });

                /// <summary>
                /// �G���e�B�e�B�� +Y �����̃x�N�g�����擾���܂��B
                /// </summary>
                READONLY_PROPERTY(linalg::Vector3, Upward, const{ return linalg::Vector3(Matrix.m21, Matrix.m22, Matrix.m23); });

                /// <summary>
                /// �G���e�B�e�B�� +Z �����̃x�N�g�����擾���܂��B
                /// </summary>
                READONLY_PROPERTY(linalg::Vector3, Forward, const{ return linalg::Vector3(Matrix.m31, Matrix.m32, Matrix.m33); });

                /// <summary>
                /// �G���e�B�e�B�̈ʒu��\���܂��B
                /// </summary>
                READWRITE_PROPERTY(linalg::Vector3, Position, const{ return Matrix.position; }, { Matrix.position = value; });
            };
        }
    }
}
