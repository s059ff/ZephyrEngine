#pragma once

#include "zephyr.graphics\Font.h"

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        enum class FontOption;

        /// <summary>
        /// �t�H���g��\���܂��B
        /// </summary>
        public ref class Font
            : public INativeWrapper<zephyr::graphics::Font>
        {
        public:

            /// <summary>
            /// �V�����t�H���g���쐬���܂��B
            /// </summary>
            /// <param name="fontname">�t�H���g�t�@�~���[�B</param>
            /// <param name="size">�t�H���g�̃T�C�Y�B</param>
            void Create(String^ fontname, int size)
            {
                Native->Create(to_string(fontname).c_str(), size);
            }

            /// <summary>
            /// �V�����t�H���g���쐬���܂��B
            /// </summary>
            /// <param name="fontname">�t�H���g�t�@�~���[�B</param>
            /// <param name="size">�t�H���g�̃T�C�Y�B</param>
            /// <param name="option">�{�[���h�̂�C�^���b�N�̂Ȃǂ��w�肷��쐬�I�v�V�����B</param>
            void Create(String^ fontname, int size, FontOption option)
            {
                Native->Create(to_string(fontname).c_str(), size, (zephyr::graphics::FontOption)option);
            }

            /// <summary>
            /// �t�H���g�̃I�u�W�F�N�g�n���h�����擾���܂��B
            /// </summary>
            property void* Handle { void* get() { return Native->handle; }}

            /// <summary>
            /// �t�H���g�̃T�C�Y���擾���܂��B
            /// </summary>
            property int Size { int get() { return Native->size; }}
        };

        /// <summary>
        /// �t�H���g�̍쐬�I�v�V�������`���܂��B
        /// </summary>
        [System::FlagsAttribute]
        public enum class FontOption
        {
            /// <summary>
            /// �ʏ�̂�\���܂��B
            /// </summary>
            Normal = (int)zephyr::graphics::FontOption::Normal,

            /// <summary>
            /// �{�[���h�̂�\���܂��B
            /// </summary>
            Bold = (int)zephyr::graphics::FontOption::Bold,

            /// <summary>
            /// �C�^���b�N�̂�\���܂��B
            /// </summary>
            Italic = (int)zephyr::graphics::FontOption::Italic,

            /// <summary>
            /// �����t����\���܂��B
            /// </summary>
            Underline = (int)zephyr::graphics::FontOption::Underline,

            /// <summary>
            /// �ŏ�������\���܂��B
            /// </summary>
            StrikeOut = (int)zephyr::graphics::FontOption::StrikeOut
        };
    }
}
