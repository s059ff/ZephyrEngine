#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �E�B���h�E��\���܂��B
        /// </summary>
        public ref class Window
            : public INativeWrapper<zephyr::graphics::Window>
        {
        public:

            Window()
            {
                Native->Started += s_start;
                Native->Updated += s_update;
                Native->Closed += s_close;
                Native->Destroyed += s_destroy;
            }

            /// <summary>
            /// �E�B���h�E���쐬���܂��B
            /// </summary>
            /// <param name="name">�L���v�V�����̖��O�B</param>
            /// <param name="width">�N���C�A���g�̈�̕��B</param>
            /// <param name="height">�N���C�A���g�̈�̍����B</param>
            void Create(String^ name, int width, int height)
            {
                Native->Create(to_string(name).c_str(), width, height);
            }

            /// <summary>
            /// �E�B���h�E���쐬���܂��B
            /// </summary>
            /// <param name="name">�L���v�V�����̖��O�B</param>
            /// <param name="width">�N���C�A���g�̈�̕��B</param>
            /// <param name="height">�N���C�A���g�̈�̍����B</param>
            /// <param name="showFrame">�t���[����\������ꍇ�� true, �\�����Ȃ��ꍇ�� false�B</param>
            void Create(String^ name, int width, int height, bool showFrame)
            {
                Native->Create(to_string(name).c_str(), width, height, showFrame);
            }

            /// <summary>
            /// ���b�Z�[�W���[�v���J�n���܂��B�E�B���h�E��������܂ŁA���̊֐��͏I�����܂���B
            /// </summary>
            void Start()
            {
                s_instance = this;

                Native->Start();
            }

            /// <summary>
            /// ���b�Z�[�W���[�v���I�����A�E�B���h�E����܂��B
            /// </summary>
            void Close()
            {
                Native->Close();
            }

            /// <summary>
            /// �E�B���h�E�̈ʒu��ύX���܂��B
            /// </summary>
            /// <param name="x">�E�B���h�E�̍���[�� X ���W�B</param>
            /// <param name="y">�E�B���h�E�̍���[�� Y ���W�B</param>
            void SetPosition(int x, int y)
            {
                Native->SetPosition(x, y);
            }

            /// <summary>
            /// �N���C�A���g�̈�̑傫����ύX���܂��B
            /// </summary>
            /// <param name="sx">�N���C�A���g�̈�̕��B</param>
            /// <param name="sy">�N���C�A���g�̈�̍����B</param>
            void SetSize(int sx, int sy)
            {
                Native->SetSize(sx, sy);
            }

            /// <summary>
            /// �t���[����\�����܂��B
            /// </summary>
            void ShowFrame()
            {
                Native->ShowFrame();
            }

            /// <summary>
            /// �t���[�����B���܂��B
            /// </summary>
            void HideFrame()
            {
                Native->HideFrame();
            }

            /// <summary>
            /// �J�[�\����\�����܂��B
            /// </summary>
            void ShowCursor()
            {
                Native->ShowCursor();
            }

            /// <summary>
            /// �J�[�\�����\���ɂ��܂��B
            /// </summary>
            void HideCursor()
            {
                Native->HideCursor();
            }

            /// <summary>
            /// �E�B���h�E���A�N�e�B�u�ɂ��܂��B
            /// </summary>
            void Activate()
            {
                Native->Activate();
            }

            /// <summary>
            /// �C���X�^���X�n���h�����擾���܂��B
            /// </summary>
            property unsigned long long InstanceHandle
            {
                unsigned long long get()
                {
                    return (unsigned long long)Native->instanceHandle;
                }
            }

            /// <summary>
            /// �E�B���h�E�n���h�����擾���܂��B
            /// </summary>
            property unsigned long long Handle
            {
                unsigned long long get()
                {
                    return (unsigned long long)Native->handle;
                }
            }

            /// <summary>
            /// �N���C�A���g�̈�̕����擾���܂��B
            /// </summary>
            property int Width
            {
                int get()
                {
                    return Native->width;
                }
            }

            /// <summary>
            /// �N���C�A���g�̈�̍������擾���܂��B
            /// </summary>
            property int Height
            {
                int get()
                {
                    return Native->height;
                }
            }

        public:

            /// <summary>
            /// ���b�Z�[�W���[�v�̊J�n���Ɏ��s����܂��B
            /// </summary>
            event System::Action^ Started;

            /// <summary>
            /// ���b�Z�[�W���[�v�̓x�Ɏ��s����܂��B
            /// </summary>
            event System::Action^ Updated;

            /// <summary>
            /// ���b�Z�[�W���[�v�̏I�����Ɏ��s����܂��B
            /// </summary>
            event System::Action^ Closed;

            /// <summary>
            /// �E�B���h�E�n���h�����������钼�O�Ɏ��s����܂��B
            /// </summary>
            event System::Action^ Destroyed;

        private:

            static void s_start() { s_instance->Started(); }

            static void s_update() { s_instance->Updated(); }

            static void s_close() { s_instance->Closed(); }

            static void s_destroy() { s_instance->Destroyed(); }

            static Window^ s_instance;
        };
    }
}
