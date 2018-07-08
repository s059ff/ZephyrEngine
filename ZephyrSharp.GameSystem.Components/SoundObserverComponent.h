#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 3D �T�E���h�̊ϑ��҂�\���܂��B
            /// </summary>
            public ref class SoundObserverComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// �T�E���h�̌��ʔ͈͂��擾�܂��͐ݒ肵�܂��B
                /// </summary>
                property double EffectRange;

                /// <summary>
                /// �������擾�܂��͐ݒ肵�܂��B
                /// </summary>
                property double SonicSpeed;

            internal:

                static SoundObserverComponent^ Observer;

                Vector3 Position;

                Vector3 Velocity;

                Matrix4x3 Matrix;

            protected public:

                virtual void OnAttach() override;

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

            private:

                void Update();
            };
        }
    }
}
