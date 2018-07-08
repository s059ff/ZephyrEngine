#pragma once

#include "zephyr\type.h"

#include "Interface.h"

struct IDirectSound;

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// �T�E���h�V�X�e���𓝊����܂��B
        /// </summary>
        class SoundDevice : public Interface<IDirectSound>
        {
        public:

            /// <summary>
            /// �f�o�C�X���쐬���A�T�E���h�V�X�e�����N���ɂ��܂��B
            /// </summary>
            void Create(handle hWindow);

            /// <summary>
            /// �f�o�C�X������A�T�E���h�V�X�e�����I�����܂��B
            /// </summary>
            void Release();
        };
    }
}
