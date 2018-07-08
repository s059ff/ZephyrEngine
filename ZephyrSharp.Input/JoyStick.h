#pragma once

#include "common.h"
#include "ButtonState.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// �W���C�X�e�B�b�N�R���g���[����\���܂��B
        /// </summary>
        public ref class JoyStick
            : public INativeWrapper<zephyr::input::JoyStick>
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
            /// �{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            /// <param name="id">�{�^���� ID �B</param>
            ButtonState GetButtonState(int id)
            {
                return (ButtonState)Native->GetButtonState(id);
            }

            /// <summary>
            /// �{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState default[int]
            {
                ButtonState get(int id) { return this->GetButtonState(id); }
            }

        public:

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 1 ���� X ���̒l���擾���܂��B
            /// </summary>
            property double AxisX { double get() { return Native->AxisX; } }

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 1 ���� Y ���̒l���擾���܂��B
            /// </summary>
            property double AxisY { double get() { return Native->AxisY; } }

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 2 ���� X ���̒l���擾���܂��B
            /// </summary>
            property double SubAxisX { double get() { return Native->SubAxisX; } }

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 2 ���� Y ���̒l���擾���܂��B
            /// </summary>
            property double SubAxisY { double get() { return Native->SubAxisY; } }

            /// <summary>
            /// POV �X�C�b�`�̍������̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState Left { ButtonState get() { return (ButtonState)Native->Left; } }

            /// <summary>
            /// POV �X�C�b�`�̉E�����̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState Right { ButtonState get() { return (ButtonState)Native->Right; } }

            /// <summary>
            /// POV �X�C�b�`�̏�����̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState Up { ButtonState get() { return (ButtonState)Native->Up; } }

            /// <summary>
            /// POV �X�C�b�`�̉������̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState Down { ButtonState get() { return (ButtonState)Native->Down; } }

            /// <summary>
            /// �R���g���[�����ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            property bool IsConnected { bool get() { return Native->IsConnected; } }

            /// <summary>
            /// �A�i���O�X�e�B�b�N�̃f�b�h�]�[���̑傫���� 0 ���� 1 �͈̔͂Ŏw�肵�܂��B
            /// </summary>
            property double DeadZone
            {
                double get() { return Native->DeadZone; }
                void set(double value) { Native->DeadZone = value; }
            }
        };
    }
}
