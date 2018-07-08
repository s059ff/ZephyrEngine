#pragma once

#include <Windows.h>

#include "common.h"

namespace ZephyrSharp
{
    /// <summary>
    /// ���b�Z�[�W�{�b�N�X�ɕ\�������A�C�R����\���܂��B
    /// </summary>
    public enum class MessageBoxIcon
    {
        /// <summary>
        /// ��� �ł��邱�Ƃ�\���܂��B
        /// </summary>
        Information = MB_ICONINFORMATION,

        /// <summary>
        /// �x�� �ł��邱�Ƃ�\���܂��B
        /// </summary>
        Warning = MB_ICONWARNING,

        /// <summary>
        /// �G���[ �ł��邱�Ƃ�\���܂��B
        /// </summary>
        Error = MB_ICONERROR
    };

    /// <summary>
    /// ���b�Z�[�W�{�b�N�X��\�����܂��B
    /// </summary>
    public ref class MessageBox
    {
    public:

        /// <summary>
        /// ���b�Z�[�W�{�b�N�X��\�����܂��B
        /// </summary>
        /// <param name="contents">���b�Z�[�W�{���B</param>
        /// <param name="caption">���b�Z�[�W�T�v�B</param>
        static void Show(String^ contents, String^ caption)
        {
            MessageBoxA(nullptr, to_string(contents).c_str(), to_string(caption).c_str(), (unsigned int)MessageBoxIcon::Information);
        }

        /// <summary>
        /// ���b�Z�[�W�{�b�N�X��\�����܂��B
        /// </summary>
        /// <param name="contents">���b�Z�[�W�{���B</param>
        /// <param name="caption">���b�Z�[�W�T�v�B</param>
        /// <param name="icon">�A�C�R���B</param>
        static void Show(String^ contents, String^ caption, MessageBoxIcon icon)
        {
            MessageBoxA(nullptr, to_string(contents).c_str(), to_string(caption).c_str(), (unsigned int)icon);
        }
    };
}
