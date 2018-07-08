#pragma once

#include "zephyr\uncopyable.h"

namespace zephyr
{
    namespace graphics
    {
        enum class FontOption;

        /// <summary>
        /// �t�H���g��\���܂��B
        /// </summary>
        class Font : uncopyable
        {
        public:

            Font();

            ~Font();

            /// <summary>
            /// �V�����t�H���g���쐬���܂��B
            /// </summary>
            /// <param name="fontname">�t�H���g�t�@�~���[�B</param>
            /// <param name="size">�t�H���g�̃T�C�Y�B</param>
            void Create(const char* fontname, int size);

            /// <summary>
            /// �V�����t�H���g���쐬���܂��B
            /// </summary>
            /// <param name="fontname">�t�H���g�t�@�~���[�B</param>
            /// <param name="size">�t�H���g�̃T�C�Y�B</param>
            /// <param name="option">�{�[���h�̂�C�^���b�N�̂Ȃǂ��w�肷��쐬�I�v�V�����B</param>
            void Create(const char* fontname, int size, FontOption option);

            /// <summary>
            /// ���̃��\�[�X��������܂��B
            /// </summary>
            void Release();

            /// <summary>
            /// �t�H���g�̃I�u�W�F�N�g�n���h�����擾���܂��B
            /// </summary>
            __declspec(property(get = get_handle)) void* handle;

            void* get_handle() const { return this->m_hFont; }

            /// <summary>
            /// �t�H���g�̃T�C�Y���擾���܂��B
            /// </summary>
            __declspec(property(get = get_size)) int size;

            int get_size() const { return this->m_size; }

        private:

            void* m_hFont;

            int m_size;
        };

        /// <summary>
        /// �t�H���g�̍쐬�I�v�V�������`���܂��B
        /// </summary>
        enum class FontOption
        {
            /// <summary>
            /// �ʏ�̂�\���܂��B
            /// </summary>
            Normal = 0,

            /// <summary>
            /// �{�[���h�̂�\���܂��B
            /// </summary>
            Bold = 1,

            /// <summary>
            /// �C�^���b�N�̂�\���܂��B
            /// </summary>
            Italic = 2,

            /// <summary>
            /// �����t����\���܂��B
            /// </summary>
            Underline = 4,

            /// <summary>
            /// �ŏ�������\���܂��B
            /// </summary>
            StrikeOut = 8
        };

        inline FontOption operator |(FontOption a, FontOption b)
        {
            return FontOption((int)a | (int)b);
        }
    }
}
