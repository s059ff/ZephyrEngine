#pragma once

#include "zephyr\property.h"
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
            /// ������Ԃɂ�����G���e�B�e�B��\���܂��B
            /// </summary>
            class PhysicsComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// �I�u�W�F�N�g�ɂ�����́B
                /// </summary>
                linalg::Vector3 Force;

                /// <summary>
                /// �I�u�W�F�N�g�ɂ������]�̗́B
                /// </summary>
                linalg::Vector3 Torque;

                /// <summary>
                /// �I�u�W�F�N�g�̑��x�B
                /// </summary>
                linalg::Vector3 Velocity;

                /// <summary>
                /// �I�u�W�F�N�g�̊p���x�B
                /// </summary>
                linalg::Vector3 AngularVelocity;

                /// <summary>
                /// �I�u�W�F�N�g�̉����x�B
                /// </summary>
                linalg::Vector3 Acceleration;

                /// <summary>
                /// �I�u�W�F�N�g�̊p�����x�B
                /// </summary>
                linalg::Vector3 AngularAcceleration;

                /// <summary>
                /// �I�u�W�F�N�g�̎��ʁB
                /// </summary>
                float Mass = 1.0f;

                /// <summary>
                /// �I�u�W�F�N�g�̊������[�����g�B
                /// </summary>
                float InertiaMoment = 1.0f;

            public:

                virtual void ReceiveMessage(const string& message, void* params[]) override;

            private:

                void Update();
            };
        }
    }
}
