#pragma once

#include "common.h"

#include "Texture2D.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �e�L�X�g�������_�����O���邽�߂̃e�N�X�`�� ���\�[�X��\���܂��B
        /// </summary>
        public ref class FontTexture
        {
        public:

            /// <summary>
            /// ���\�[�X���쐬���܂��B
            /// </summary>
            /// <param name="font">�e�L�X�g�̃t�H���g�B</param> 
            void Create(Font^ font)
            {
                this->font = font;
            }

            /// <summary>
            /// ���\�[�X���J�����܂��B
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
            /// �����ɑΉ�����e�N�X�`�����擾���܂��B
            /// </summary>
            /// <param name="c">�����R�[�h�B</param> 
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
            /// �t�H���g�̃f�t�H���g�T�C�Y���擾���܂��B
            /// </summary>
            property int Size { int get() { return this->font->Size; }}

        private:

            Font^ font;

            ArrayCache<Texture2D^>^ textures = gcnew ArrayCache<Texture2D^>(65536, 1024);
        };
    }
}
