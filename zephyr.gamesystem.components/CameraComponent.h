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
            /// �J������\���܂��B
            /// </summary>
            class CameraComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ����n�_����ʂ̂���n�_�𒍎�����悤�ɃJ�����̌�����ݒ肵�܂��B
                /// </summary>
                /// <param name="eye">�J�����̍��W�B</param> 
                /// <param name="at">������̍��W�B</param> 
                void LookAt(linalg::Vector3 eye, linalg::Vector3 at);

                /// <summary>
                /// �r���[�C���O�s����擾���܂��B
                /// </summary>
                READONLY_PROPERTY(linalg::Matrix4x3, ViewingMatrix, const;);
            };
        }
    }
}
