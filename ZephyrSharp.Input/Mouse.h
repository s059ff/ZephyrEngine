#pragma once

#include "common.h"
#include "ButtonState.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// �}�E�X�f�o�C�X��\���܂��B
        /// </summary>
        public ref class Mouse
            : public INativeWrapper<zephyr::input::Mouse>
        {
        public:

            /// <summary>
            /// �f�o�C�X�̏�Ԃ��X�V���܂��B���̃��\�b�h�͖��t���[���Ăяo���K�v������܂��B
            /// </summary>
            void Update()
            {
                Native->Update();
            }

        public:

            /// <summary>
            /// �}�E�X�̃N���C�A���g���W�n�ł� X ���W���擾���܂��B
            /// </summary>
            property int X { int get() { return Native->X; } };

            /// <summary>
            /// �}�E�X�̃N���C�A���g���W�n�ł� Y ���W���擾���܂��B
            /// </summary>
            property int Y { int get() { return Native->Y; } };

            /// <summary>
            /// �}�E�X�� X �����̈ړ��ʂ��擾���܂��B
            /// </summary>
            property int MovementX { int get() { return Native->MovementX; } };

            /// <summary>
            /// �}�E�X�� Y �����̈ړ��ʂ��擾���܂��B
            /// </summary>
            property int MovementY { int get() { return Native->MovementY; } };

            /// <summary>
            /// �}�E�X�� Z �����̈ړ��ʂ��擾���܂��B
            /// </summary>
            property int MovementZ { int get() { return Native->MovementZ; } };

            /// <summary>
            /// �}�E�X�̍��{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState Left { ButtonState get() { return (ButtonState)Native->Left; } };

            /// <summary>
            /// �}�E�X�̉E�{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState Right { ButtonState get() { return (ButtonState)Native->Right; } };

            /// <summary>
            /// �}�E�X�̉E�{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            property ButtonState Center { ButtonState get() { return (ButtonState)Native->Center; } };

            /// <summary>
            /// �R���g���[�����ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            property bool IsConnected { bool get() { return Native->IsConnected; } }
        };
    }
}
