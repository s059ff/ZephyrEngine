#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Sound
    {
        /// <summary>
        /// �T�E���h�V�X�e���𓝊����܂��B
        /// </summary>
        public ref class SoundDevice
            : public INativeWrapper<zephyr::sound::SoundDevice>
        {
        public:

            /// <summary>
            /// �f�o�C�X���쐬���A�T�E���h�V�X�e�����N���ɂ��܂��B
            /// </summary>
            /// <param name="hWindow">�A�v���P�[�V�����̃E�B���h�E�n���h���B</param>
            void Create(handle hWindow)
            {
                Native->Create(hWindow);
            }

            /// <summary>
            /// �f�o�C�X���쐬���A�T�E���h�V�X�e�����N���ɂ��܂��B
            /// </summary>
            /// <param name="hWindow">�A�v���P�[�V�����̃E�B���h�E�n���h���B</param>
            void Create(unsigned long long hWindow)
            {
                Native->Create((handle)hWindow);
            }

            /// <summary>
            /// �f�o�C�X������A�T�E���h�V�X�e�����I�����܂��B
            /// </summary>
            void Release()
            {
                Native->Release();
            }

        public:

            static SoundDevice^ Instance = gcnew SoundDevice();
        };
    }
}
