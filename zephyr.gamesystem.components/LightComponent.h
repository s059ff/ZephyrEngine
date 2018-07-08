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
            /// ���C�g��\���܂��B
            /// </summary>
            class LightComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ���C�g�̌�����ݒ肵�܂��B
                /// </summary>
                /// <param name="eye">���C�g�̍��W�B</param> 
                /// <param name="at">������̍��W�B</param> 
                void LookAt(linalg::Vector3 eye, linalg::Vector3 at);
            };
        }
    }
}
