#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// ������Ԃɂ����� 2D �G���e�B�e�B��\���܂��B
            /// </summary>
            public ref class Physics2DComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// �I�u�W�F�N�g�ɂ�����́B
                /// </summary>
                Vector2 Force;

                /// <summary>
                /// �I�u�W�F�N�g�ɂ������]�̗́B
                /// </summary>
                float Torque;

                /// <summary>
                /// �I�u�W�F�N�g�̑��x�B
                /// </summary>
                Vector2 Velocity;

                /// <summary>
                /// �I�u�W�F�N�g�̊p���x�B
                /// </summary>
                float AngularVelocity;

                /// <summary>
                /// �I�u�W�F�N�g�̉����x�B
                /// </summary>
                Vector2 Acceleration;

                /// <summary>
                /// �I�u�W�F�N�g�̊p�����x�B
                /// </summary>
                float AngularAcceleration;

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
