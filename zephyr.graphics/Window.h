#pragma once

#include "zephyr\event.h"

namespace zephyr
{
    namespace graphics
    {
        /// <summary>
        /// �E�B���h�E��\���܂��B
        /// </summary>
        class Window
        {
        public:

            /// <summary>
            /// �E�B���h�E���쐬���܂��B
            /// </summary>
            /// <param name="name">�L���v�V�����̖��O�B</param>
            /// <param name="width">�N���C�A���g�̈�̕��B</param>
            /// <param name="height">�N���C�A���g�̈�̍����B</param>
            void Create(const char* name, int width, int height);

            /// <summary>
            /// �E�B���h�E���쐬���܂��B
            /// </summary>
            /// <param name="name">�L���v�V�����̖��O�B</param>
            /// <param name="width">�N���C�A���g�̈�̕��B</param>
            /// <param name="height">�N���C�A���g�̈�̍����B</param>
            /// <param name="showFrame">�t���[����\������ꍇ�� true, �\�����Ȃ��ꍇ�� false�B</param>
            void Create(const char* name, int width, int height, bool showFrame);

            /// <summary>
            /// ���b�Z�[�W���[�v���J�n���܂��B�E�B���h�E��������܂ŁA���̊֐��͏I�����܂���B
            /// </summary>
            void Start();

            /// <summary>
            /// ���b�Z�[�W���[�v���I�����A�E�B���h�E����܂��B
            /// </summary>
            void Close();

            /// <summary>
            /// �E�B���h�E�̈ʒu��ύX���܂��B
            /// </summary>
            /// <param name="x">�E�B���h�E�̍���[�� X ���W�B</param>
            /// <param name="y">�E�B���h�E�̍���[�� Y ���W�B</param>
            void SetPosition(int x, int y);

            /// <summary>
            /// �N���C�A���g�̈�̑傫����ύX���܂��B
            /// </summary>
            /// <param name="sx">�N���C�A���g�̈�̕��B</param>
            /// <param name="sy">�N���C�A���g�̈�̍����B</param>
            void SetSize(int sx, int sy);

            /// <summary>
            /// �E�B���h�E�̃A�C�R����ݒ肵�܂��B
            /// </summary>
            /// <param name="resourceID">�A�C�R���̃��\�[�X ID �B</param> 
            void SetIcon(int resourceID);

            /// <summary>
            /// �E�B���h�E�̃A�C�R����ݒ肵�܂��B
            /// </summary>
            /// <param name="resourceID">�A�C�R���̃��\�[�X ID �B</param> 
            void SetSmallIcon(int resourceID);

            /// <summary>
            /// �E�B���h�E�̃A�C�R����ݒ肵�܂��B
            /// </summary>
            /// <param name="resourceName">�A�C�R���̃��\�[�X���B</param> 
            void SetIcon(const char* resourceName);

            /// <summary>
            /// �E�B���h�E�̃A�C�R����ݒ肵�܂��B
            /// </summary>
            /// <param name="resourceName">�A�C�R���̃��\�[�X���B</param> 
            void SetSmallIcon(const char* resourceName);

            /// <summary>
            /// �t���[����\�����܂��B
            /// </summary>
            void ShowFrame();

            /// <summary>
            /// �t���[�����B���܂��B
            /// </summary>
            void HideFrame();

            /// <summary>
            /// �J�[�\����\�����܂��B
            /// </summary>
            void ShowCursor();

            /// <summary>
            /// �J�[�\�����\���ɂ��܂��B
            /// </summary>
            void HideCursor();

            /// <summary>
            /// �E�B���h�E���A�N�e�B�u�ɂ��܂��B
            /// </summary>
            void Activate();

            __declspec(property(get = get_instnace_handle)) void* instanceHandle;

            __declspec(property(get = get_window_handle)) void* handle;

            __declspec(property(get = get_width)) int width;

            __declspec(property(get = get_height)) int height;

            void* get_instnace_handle() const { return m_hInstance; }

            void* get_window_handle() const { return m_hWindow; }

            int get_width() const { return m_width; }

            int get_height() const { return m_height; }

        public:

            /// <summary>
            /// ���b�Z�[�W���[�v�̊J�n���Ɏ��s����܂��B
            /// </summary>
            event<> Started;

            /// <summary>
            /// ���b�Z�[�W���[�v�̓x�Ɏ��s����܂��B
            /// </summary>
            event<> Updated;

            /// <summary>
            /// ���b�Z�[�W���[�v�̏I�����Ɏ��s����܂��B
            /// </summary>
            event<> Closed;

            /// <summary>
            /// �E�B���h�E�n���h�����������钼�O�Ɏ��s����܂��B
            /// </summary>
            event<> Destroyed;

        private:

            void* m_hWindow;

            void* m_hInstance;

            int m_width, m_height;

            void *m_hIcon, *m_hIconSmall;
        };
    }
}
