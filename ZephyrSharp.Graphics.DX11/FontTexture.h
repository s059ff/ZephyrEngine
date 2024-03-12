#pragma once

#include "common.h"

#include "Texture2D.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// テキストをレンダリングするためのテクスチャ リソースを表します。
        /// </summary>
        public ref class FontTexture
        {
        public:

            /// <summary>
            /// リソースを作成します。
            /// </summary>
            /// <param name="font">テキストのフォント。</param> 
            void Create(Font^ font)
            {
                this->font = font;
            }

            /// <summary>
            /// リソースを開放します。
            /// </summary>
            void Release()
            {
                delete textures;
                textures = nullptr;
            }

            virtual ~FontTexture()
            {
                this->!FontTexture();
            }

            !FontTexture()
            {
                delete textures;
                textures = nullptr;
            }

            /// <summary>
            /// 文字に対応するテクスチャを取得します。
            /// </summary>
            /// <param name="c">文字コード。</param> 
            Texture2D^ GetTexture(wchar_t c)
            {
                Texture2D^ tex = textures[c];
                if (tex->Stride == 0)
                {
                    tex->Print(this->font, c);
                }
                return tex;
            }

            /// <summary>
            /// フォントのデフォルトサイズを取得します。
            /// </summary>
            property int Size { int get() { return this->font->Size; }}

        private:

            Font^ font;

            ArrayCache<Texture2D^>^ textures = gcnew ArrayCache<Texture2D^>(65536, 1024);
        };
    }
}
