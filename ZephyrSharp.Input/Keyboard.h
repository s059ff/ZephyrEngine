#pragma once

#include "common.h"
#include "ButtonState.h"
#include "KeyCode.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// �L�[�{�[�h�f�o�C�X��\���܂��B
        /// </summary>
        public ref class Keyboard : public INativeWrapper<zephyr::input::Keyboard>
        {
        public:

            /// <summary>
            /// �f�o�C�X�̏�Ԃ��X�V���܂��B���̃��\�b�h�͖��t���[���Ăяo���K�v������܂��B
            /// </summary>
            void Update()
            {
                Native->Update();
            }

            /// <summary>
            /// �L�[�̏�Ԃ��擾���܂��B
            /// </summary>
            /// <param name="key">�L�[�R�[�h�B</param>
            /// <returns>�L�[�̏�ԁB</returns>
            ButtonState GetKeyState(KeyCode key)
            {
                return (ButtonState)Native->GetKeyState((zephyr::input::KeyCode)key);
            }

            /// <summary>
            /// �L�[�̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState default [KeyCode]
            {
                ButtonState get(KeyCode key) { return this->GetKeyState(key); }
            }

            /// <summary>
            /// �R���g���[�����ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            property bool IsConnected { bool get() { return Native->IsConnected; } };
        };
    }
}
