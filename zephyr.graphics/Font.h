#pragma once

#include "zephyr\uncopyable.h"

namespace zephyr
{
    namespace graphics
    {
        enum class FontOption;

        /// <summary>
        /// フォントを表します。
        /// </summary>
        class Font : uncopyable
        {
        public:

            Font();

            ~Font();

            /// <summary>
            /// 新しいフォントを作成します。
            /// </summary>
            /// <param name="fontname">フォントファミリー。</param>
            /// <param name="size">フォントのサイズ。</param>
            void Create(const char* fontname, int size);

            /// <summary>
            /// 新しいフォントを作成します。
            /// </summary>
            /// <param name="fontname">フォントファミリー。</param>
            /// <param name="size">フォントのサイズ。</param>
            /// <param name="option">ボールド体やイタリック体などを指定する作成オプション。</param>
            void Create(const char* fontname, int size, FontOption option);

            /// <summary>
            /// このリソースを解放します。
            /// </summary>
            void Release();

            /// <summary>
            /// フォントのオブジェクトハンドルを取得します。
            /// </summary>
            __declspec(property(get = get_handle)) void* handle;

            void* get_handle() const { return this->m_hFont; }

            /// <summary>
            /// フォントのサイズを取得します。
            /// </summary>
            __declspec(property(get = get_size)) int size;

            int get_size() const { return this->m_size; }

        private:

            void* m_hFont;

            int m_size;
        };

        /// <summary>
        /// フォントの作成オプションを定義します。
        /// </summary>
        enum class FontOption
        {
            /// <summary>
            /// 通常体を表します。
            /// </summary>
            Normal = 0,

            /// <summary>
            /// ボールド体を表します。
            /// </summary>
            Bold = 1,

            /// <summary>
            /// イタリック体を表します。
            /// </summary>
            Italic = 2,

            /// <summary>
            /// 下線付きを表します。
            /// </summary>
            Underline = 4,

            /// <summary>
            /// 打消し線を表します。
            /// </summary>
            StrikeOut = 8
        };

        inline FontOption operator |(FontOption a, FontOption b)
        {
            return FontOption((int)a | (int)b);
        }
    }
}
