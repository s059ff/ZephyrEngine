#pragma once

#include "zephyr\property.h"
#include "zephyr.sound\SoundBuffer.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// 3D �T�E���h��炵�܂��B
            /// </summary>
            class SoundComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// �R���|�[�l���g�����������܂��B
                /// </summary>
                /// <param name="device">�T�E���h�f�o�C�X�B</param> 
                /// <param name="buffer">�T�E���h�o�b�t�@�B</param> 
                SoundComponent(sound::SoundDevice& device, sound::SoundBuffer& buffer)
                {
                    this->Sound.Create(device, buffer);
                    this->VolumeFactor = 1;
                }

                /// <summary>
                /// �R���|�[�l���g�����������܂��B
                /// </summary>
                /// <param name="device">�T�E���h�f�o�C�X�B</param> 
                /// <param name="buffer">�T�E���h�o�b�t�@�B</param> 
                /// <param name="play">true �̏ꍇ�A�����ɍĐ�����B</param> 
                SoundComponent(sound::SoundDevice& device, sound::SoundBuffer& buffer, bool play)
                    : SoundComponent(device, buffer)
                {
                    if (play)
                        this->Sound.Play();
                }

                /// <summary>
                /// �T�E���h���Đ����܂��B
                /// </summary>
                void Play()
                {
                    this->Sound.Play();
                }

                /// <summary>
                /// �T�E���h�����[�v�Đ����܂��B
                /// </summary>
                void LoopPlay()
                {
                    this->Sound.LoopPlay();
                }

                /// <summary>
                /// �T�E���h���擾�܂��͐ݒ肵�܂��B
                /// </summary>
                sound::SoundBuffer Sound;

                /// <summary>
                /// ���ʂ𒲐����܂��B
                /// </summary>
                double VolumeFactor;

                /// <summary>
                /// ���g�����擾���܂��B
                /// </summary>
                READONLY_PROPERTY(unsigned long, Frequency, const{ return Sound.Frequency; });

                    /// <summary>
                    /// ���ʂ��擾���܂��B
                    /// </summary>
                READONLY_PROPERTY(double, Volume, const{ return Sound.Volume; });

                /// <summary>
                /// �p�����擾���܂��B
                /// </summary>
                READONLY_PROPERTY(double, Pan, const{ return Sound.Pan; });

            public:

                virtual void ReceiveMessage(const string& message, void* params[]) override;

                virtual void OnDestroy() override;

            private:

                void Update();
            };
        }
    }
}
