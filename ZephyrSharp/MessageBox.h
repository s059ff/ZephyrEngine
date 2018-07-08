#pragma once

#include <Windows.h>

#include "common.h"

namespace ZephyrSharp
{
    /// <summary>
    /// メッセージボックスに表示されるアイコンを表します。
    /// </summary>
    public enum class MessageBoxIcon
    {
        /// <summary>
        /// 情報 であることを表します。
        /// </summary>
        Information = MB_ICONINFORMATION,

        /// <summary>
        /// 警告 であることを表します。
        /// </summary>
        Warning = MB_ICONWARNING,

        /// <summary>
        /// エラー であることを表します。
        /// </summary>
        Error = MB_ICONERROR
    };

    /// <summary>
    /// メッセージボックスを表示します。
    /// </summary>
    public ref class MessageBox
    {
    public:

        /// <summary>
        /// メッセージボックスを表示します。
        /// </summary>
        /// <param name="contents">メッセージ本文。</param>
        /// <param name="caption">メッセージ概要。</param>
        static void Show(String^ contents, String^ caption)
        {
            MessageBoxA(nullptr, to_string(contents).c_str(), to_string(caption).c_str(), (unsigned int)MessageBoxIcon::Information);
        }

        /// <summary>
        /// メッセージボックスを表示します。
        /// </summary>
        /// <param name="contents">メッセージ本文。</param>
        /// <param name="caption">メッセージ概要。</param>
        /// <param name="icon">アイコン。</param>
        static void Show(String^ contents, String^ caption, MessageBoxIcon icon)
        {
            MessageBoxA(nullptr, to_string(contents).c_str(), to_string(caption).c_str(), (unsigned int)icon);
        }
    };
}
