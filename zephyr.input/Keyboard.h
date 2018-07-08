#pragma once

#include "zephyr\array.h"
#include "zephyr\property.h"

#include "Interface.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        enum class ButtonState;
        enum class KeyCode;

        /// <summary>
        /// �L�[�{�[�h�f�o�C�X��\���܂��B
        /// </summary>
        class Keyboard : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// ���̃N���X�̐V�����C���X�^���X�����������܂��B
            /// </summary>
            Keyboard() = default;

            /// <summary>
            /// �C���X�^���X��j�����܂��B
            /// </summary>
            ~Keyboard();

            /// <summary>
            /// �f�o�C�X�̏�Ԃ��X�V���܂��B���̃��\�b�h�͖��t���[���Ăяo���K�v������܂��B
            /// </summary>
            void Update();

            /// <summary>
            /// �L�[�̏�Ԃ��擾���܂��B
            /// </summary>
            /// <param name="key">�L�[�R�[�h�B</param>
            /// <returns>�L�[�̏�ԁB</returns>
            ButtonState GetKeyState(KeyCode key);

            /// <summary>
            /// �L�[�̏�Ԃ��擾���܂��B
            /// </summary>
            ButtonState operator [](KeyCode key)
            {
                return this->GetKeyState(key);
            }

            /// <summary>
            /// �R���g���[�����ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            READONLY_PROPERTY(bool, IsConnected, { return true; });

        private:

            // ����������
            void Create();

            // ���Z�b�g����
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // �L�[�̐�
            enum { KeyCount = 256 };

            // �O��̃L�[�{�[�h�̏��
            array<byte, KeyCount> prevKeyState;

            // �L�[�{�[�h�̏��
            array<byte, KeyCount> keyState;
        };
    }
}
