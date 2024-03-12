#pragma once

#include "zephyr.graphics\Font.h"

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        enum class FontOption;

        /// <summary>
        /// フォントを表します。
        /// </summary>
        public ref class Font
            : public INativeWrapper<zephyr::graphics::Font>
        {
        public:

            /// <summary>
            /// 新しいフォントを作成します。
            /// </summary>
            /// <param name="fontname">フォントファミリー。</param>
            /// <param name="size">フォントのサイズ。</param>
            void Create(String^ fontname, int size)
            {
                Native->Create(to_string(fontname).c_str(), size);
            }

            /// <summary>
            /// 新しいフォントを作成します。
            /// </summary>
            /// <param name="fontname">フォントファミリー。</param>
            /// <param name="size">フォントのサイズ。</param>
            /// <param name="option">ボールド体やイタリック体などを指定する作成オプション。</param>
            void Create(String^ fontname, int size, FontOption option)
            {
                Native->Create(to_string(fontname).c_str(), size, (zephyr::graphics::FontOption)option);
            }

            /// <summary>
            /// フォントのオブジェクトハンドルを取得します。
            /// </summary>
            property void* Handle { void* get() { return Native->handle; }}

            /// <summary>
            /// フォントのサイズを取得します。
            /// </summary>
            property int Size { int get() { return Native->size; }}
        };

        /// <summary>
        /// フォントの作成オプションを定義します。
        /// </summary>
        [System::FlagsAttribute]
        public enum class FontOption
        {
            /// <summary>
            /// 通常体を表します。
            /// </summary>
            Normal = (int)zephyr::graphics::FontOption::Normal,

            /// <summary>
            /// ボールド体を表します。
            /// </summary>
            Bold = (int)zephyr::graphics::FontOption::Bold,

            /// <summary>
            /// イタリック体を表します。
            /// </summary>
            Italic = (int)zephyr::graphics::FontOption::Italic,

            /// <summary>
            /// 下線付きを表します。
            /// </summary>
            Underline = (int)zephyr::graphics::FontOption::Underline,

            /// <summary>
            /// 打消し線を表します。
            /// </summary>
            StrikeOut = (int)zephyr::graphics::FontOption::StrikeOut
        };
    }
}
