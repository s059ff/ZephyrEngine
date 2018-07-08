#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// ������Ԃɂ�����G���e�B�e�B��\���܂��B
            /// </summary>
            public ref class PhysicsComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// �I�u�W�F�N�g�ɂ�����́B
                /// </summary>
                Vector3 Force;

                /// <summary>
                /// �I�u�W�F�N�g�ɂ������]�̗́B
                /// </summary>
                Vector3 Torque;

                /// <summary>
                /// �I�u�W�F�N�g�̑��x�B
                /// </summary>
                Vector3 Velocity;

                /// <summary>
                /// �I�u�W�F�N�g�̊p���x�B
                /// </summary>
                Vector3 AngularVelocity;

                /// <summary>
                /// �I�u�W�F�N�g�̉����x�B
                /// </summary>
                Vector3 Acceleration;

                /// <summary>
                /// �I�u�W�F�N�g�̊p�����x�B
                /// </summary>
                Vector3 AngularAcceleration;

                /// <summary>
                /// �I�u�W�F�N�g�̎��ʁB
                /// </summary>
                float Mass = 1.0f;

                /// <summary>
                /// �I�u�W�F�N�g�̊������[�����g�B
                /// </summary>
                float InertiaMoment = 1.0f;

            protected public:

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

            private:

                void Update();
            };
        }
    }
}
