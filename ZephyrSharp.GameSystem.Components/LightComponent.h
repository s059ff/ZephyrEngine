#pragma once

using namespace System::Collections::Generic;
using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// ���C�g��\���܂��B
            /// </summary>
            public ref class LightComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ���C�g�̐ݒ��\���܂��B
                /// </summary>
                enum class LightMode
                {
                    /// <summary>
                    /// ���C�g�͐Î~���Ă���B
                    /// </summary>
                    Stationary,

                    /// <summary>
                    /// �^�[�Q�b�g��ǐՂ���B
                    /// </summary>
                    Tracking
                };

                /// <summary>
                /// ���C�g�̌�����ݒ肵�܂��B
                /// </summary>
                /// <param name="eye">���C�g�̍��W�B</param> 
                /// <param name="at">������̍��W�B</param> 
                void LookAt(Vector3 eye, Vector3 at);

                /// <summary>
                /// �g���b�L���O�̑ΏۂƂȂ�G���e�B�e�B�B
                /// </summary>
                property Entity^ TrackingTarget;

                /// <summary>
                /// �g���b�L���O�ΏۃG���e�B�e�B�Ƃ��̃G���e�B�e�B�̑��Έʒu�B
                /// </summary>
                property Vector3 Offset;

                /// <summary>
                /// ���C�g�̓���ݒ��\���܂��B
                /// </summary>
                property LightMode Mode;

            protected public:

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

            private:

                void Update();
            };
        }
    }
}
