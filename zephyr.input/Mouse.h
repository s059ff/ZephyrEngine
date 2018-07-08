#pragma once

#include "zephyr\property.h"

#include "Interface.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        enum class ButtonState;

        /// <summary>
        /// �}�E�X�f�o�C�X��\���܂��B
        /// </summary>
        class Mouse : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// ���̃N���X�̐V�����C���X�^���X�����������܂��B
            /// </summary>
            Mouse() = default;

            /// <summary>
            /// �C���X�^���X��j�����܂��B
            /// </summary>
            ~Mouse();

            /// <summary>
            /// �f�o�C�X�̏�Ԃ��X�V���܂��B���̃��\�b�h�͖��t���[���Ăяo���K�v������܂��B
            /// </summary>
            void Update();

        public:

            /// <summary>
            /// �}�E�X�̃X�N���[�����W�n�ł� X ���W���擾���܂��B
            /// </summary>
            READONLY_PROPERTY(int, X, { return this->mouseX; });

            /// <summary>
            /// �}�E�X�̃X�N���[�����W�n�ł� Y ���W���擾���܂��B
            /// </summary>
            READONLY_PROPERTY(int, Y, { return this->mouseY; });

            /// <summary>
            /// �}�E�X�� X �����̈ړ��ʂ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(int, MovementX, { return this->moveX; });

            /// <summary>
            /// �}�E�X�� Y �����̈ړ��ʂ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(int, MovementY, { return this->moveY; });

            /// <summary>
            /// �}�E�X�� Z �����̈ړ��ʂ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(int, MovementZ, { return this->moveZ; });

            /// <summary>
            /// �}�E�X�̍��{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(ButtonState, Left, ;);

            /// <summary>
            /// �}�E�X�̉E�{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(ButtonState, Right, ;);

            /// <summary>
            /// �}�E�X�̒����{�^���̏�Ԃ��擾���܂��B
            /// </summary>
            READONLY_PROPERTY(ButtonState, Center, ;);

            /// <summary>
            /// �R���g���[�����ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            __declspec(property(get = isConnected)) bool IsConnected;

            /// <summary>
            /// �}�E�X���ڑ�����Ă��邩���ׂ܂��B
            /// </summary>
            bool isConnected();

        private:

            // ����������
            void Create();

            // ���Z�b�g����
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // �}�E�X�̈ʒu
            long mouseX, mouseY;

            // �}�E�X�̈ړ���
            long moveX, moveY, moveZ;

            // �{�^���̏��
            bool left, right, center;

            // �O�t���[���̃{�^���̏��
            bool prevLeft, prevRight, prevCenter;
        };
    }
}
