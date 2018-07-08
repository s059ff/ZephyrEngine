#pragma once

using namespace ZephyrSharp::Linalg;
using namespace ZephyrSharp::Sound;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 3D �T�E���h��炵�܂��B
            /// </summary>
            public ref class SoundComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// �R���|�[�l���g�����������܂��B
                /// </summary>
                /// <param name="buffer">�T�E���h�o�b�t�@�B</param> 
                SoundComponent(SoundBuffer^ buffer)
                {
                    Sound = gcnew SoundBuffer();
                    Sound->Create(buffer);
                    this->VolumeFactor = 1;
                }

                /// <summary>
                /// �R���|�[�l���g�����������܂��B
                /// </summary>
                /// <param name="buffer">�T�E���h�o�b�t�@�B</param> 
                /// <param name="play">true �̏ꍇ�A�����ɍĐ�����B</param> 
                SoundComponent(SoundBuffer^ buffer, bool play)
                    : SoundComponent(buffer)
                {
                    if (play)
                        this->Sound->Play();
                }

                /// <summary>
                /// �T�E���h���Đ����܂��B
                /// </summary>
                void Play()
                {
                    Sound->Play();
                }

                /// <summary>
                /// �T�E���h�����[�v�Đ����܂��B
                /// </summary>
                void LoopPlay()
                {
                    Sound->LoopPlay();
                }

                /// <summary>
                /// �T�E���h���擾�܂��͐ݒ肵�܂��B
                /// </summary>
                property SoundBuffer^ Sound;

                /// <summary>
                /// ���ʂ𒲐����܂��B
                /// </summary>
                property double VolumeFactor;

                /// <summary>
                /// ���g�����擾���܂��B
                /// </summary>
                property unsigned long Frequency { unsigned long get() { return Sound->Frequency; } }

                /// <summary>
                /// ���ʂ��擾���܂��B
                /// </summary>
                property double Volume { double get() { return Sound->Volume; } }

                /// <summary>
                /// �p�����擾���܂��B
                /// </summary>
                property double Pan { double get() { return Sound->Pan; } }

            protected public:

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

                virtual void OnDestroy() override;

            private:

                void Update();
            };
        }
    }
}
