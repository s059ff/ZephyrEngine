#pragma once

#include "zephyr\array.h"
#include "zephyr\property.h"

#include "Interface.h"
#include "ButtonCode.h"
#include "ButtonState.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        enum class ButtonState;

        /// <summary>
        /// �W���C�X�e�B�b�N�R���g���[����\���܂��B
        /// </summary>
        class JoyStick : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// ���̃N���X�̐V�����C���X�^���X�����������܂��B
            /// </summary>
            JoyStick() = default;

            /// <summary>
            /// �C���X�^���X��j�����܂��B
            /// </summary>
            ~JoyStick();

            /// <summary>
            /// �f�o�C�X�̏�Ԃ��X�V���܂��B���̃��\�b�h�͖��t���[���Ăяo���K�v������܂��B
            /// </summary>
            void Update();

            /// <summary>
            /// �{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            /// <param name="code">�{�^���R�[�h�B</param>
            ButtonState GetButtonState(ButtonCode code) const;

			/// <summary>
			/// �{�^���̒��������Ԃ��擾���܂��B
			/// </summary>
			/// <param name="code">�{�^���R�[�h�B</param>
			/// <returns>�{�^����������đ����Ă���t���[�����B</returns>
			int GetPressTimeLength(ButtonCode code) const;

            /// <summary>
            /// �{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            ButtonState operator [](ButtonCode code) const
            {
                return this->GetButtonState(code);
            }

        public:

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 1 ���� X ���̒l���擾���܂��B
            /// </summary>
            const double& AxisX = this->axisX;

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 1 ���� Y ���̒l���擾���܂��B
            /// </summary>
            const double& AxisY = this->axisY;

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 2 ���� X ���̒l���擾���܂��B
            /// </summary>
            const double& SubAxisX = this->subAxisX;

            /// <summary>
            /// �A�i���O�X�e�B�b�N�� 2 ���� Y ���̒l���擾���܂��B
            /// </summary>
            const double& SubAxisY = this->subAxisY;

            /// <summary>
            /// POV �X�C�b�`�̍������̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(ButtonState, Left, { return getButtonState(this->povLeft, this->prevPovLeft); });

            /// <summary>
            /// POV �X�C�b�`�̉E�����̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(ButtonState, Right, { return getButtonState(this->povRight, this->prevPovRight); });

            /// <summary>
            /// POV �X�C�b�`�̏�����̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(ButtonState, Up, { return getButtonState(this->povUp, this->prevPovUp); });

            /// <summary>
            /// POV �X�C�b�`�̉������̃{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(ButtonState, Down, { return getButtonState(this->povDown, this->prevPovDown); });

            /// <summary>
            /// �R���g���[�����ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            __declspec(property(get = isConnected)) bool IsConnected;

            /// <summary>
            /// �R���g���[�����ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            bool isConnected() const;

            /// <summary>
            /// �A�i���O�X�e�B�b�N�̃f�b�h�]�[���̑傫���� 0 ���� 1 �͈̔͂Ŏw�肵�܂��B
            /// </summary>
            double DeadZone;

        private:

            // �쐬����
            void Create();

            // ���Z�b�g����
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // �{�^����
            enum { ButtonCount = 32 };

            // ���݂̃{�^���̏��
            array<byte, ButtonCount> buttonState;

            // ���O�̃{�^���̏��
            array<byte, ButtonCount> prevButtonState;

			// �{�^����������Ă��鍇�v����
			array<int, ButtonCount> pressTimeLength;

            // ���݂�POV�X�C�b�`�̏��
            bool povLeft, povRight, povUp, povDown;

            // ���O��POV�X�C�b�`�̏��
            bool prevPovLeft, prevPovRight, prevPovUp, prevPovDown;

            // �A�i���O�X�e�B�b�N
            double axisX, axisY;

            // �T�u�A�i���O�X�e�B�b�N
            double subAxisX, subAxisY;
        };
    }
}
