#pragma once

#include "common.h"
#include "SoundDevice.h"

namespace ZephyrSharp
{
    namespace Sound
    {
        /// <summary>
        /// �Đ��Ɠǂݏo���𓯎��ɍs���T�E���h ���\�[�X�ł��B
        /// </summary>
        public ref class StreamingSoundBuffer
            : public INativeWrapper<zephyr::sound::StreamingSoundBuffer>
        {
        public:

            /// <summary>
            /// �T�E���h�t�@�C�����J���āA�T�E���h���Đ��\�ȏ�Ԃɂ��܂��B
            /// </summary>
            /// <param name="path">�T�E���h�t�@�C���̃p�X�B</param>
            void Create(String^ path)
            {
                Native->Create(SoundDevice::Instance->NativeRef, to_string(path).c_str());
            }

            /// <summary>
            /// �T�E���h�f�[�^��j�����A�T�E���h�t�@�C������܂��B
            /// </summary>
            void Close()
            {
                Native->Close();
            }

            /// <summary>
            /// �b�P�ʂōĐ��ʒu��ύX���܂��B
            /// </summary>
            /// <param name="time">�Đ��ʒu�B</param>
            void Seek(int time)
            {
                Native->Seek(time);
            }

            /// <summary>
            /// �T�E���h��擪����Đ����܂��B
            /// </summary>
            void Play()
            {
                Native->Play();
            }

            /// <summary>
            /// �T�E���h��擪���烋�[�v�Đ����܂��B
            /// </summary>
            void LoopPlay()
            {
                Native->LoopPlay();
            }

            /// <summary>
            /// �T�E���h���~���A�Đ��ʒu��擪�ɖ߂��܂��B
            /// </summary>
            void Stop()
            {
                Native->Stop();
            }

            /// <summary>
            /// �T�E���h���ꎞ��~�������͍ĊJ���܂��B
            /// </summary>
            void Pause()
            {
                Native->Pause();
            }

            /// <summary>
            /// �Đ��󋵂ɉ����āA�T�E���h���������ɓǂݍ��݂܂��B���̃��\�b�h�͖��t���[���Ăяo���K�v������܂��B
            /// </summary>
            void Update()
            {
                Native->Update();
            }
        };
    }
}
