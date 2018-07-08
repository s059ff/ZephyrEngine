#include <Windows.h>

#include "Font.h"

#define this (*this)

namespace zephyr
{
    namespace graphics
    {
        namespace
        {
            bool isContained(FontOption a, FontOption b)
            {
                return ((int)a & (int)b) != 0;
            }
        }

        Font::Font() : m_hFont(nullptr)
        {
        }

        Font::~Font()
        {
            this.Release();
        }

        void Font::Create(const char* fontname, int size)
        {
            this.Create(fontname, size, (FontOption)(0));
        }

        void Font::Create(const char* fontname, int size, FontOption option)
        {
            this.Release();

            bool isBold = isContained(option, FontOption::Bold);
            bool isItalic = isContained(option, FontOption::Italic);
            bool isUnderline = isContained(option, FontOption::Underline);
            bool isStrikeOut = isContained(option, FontOption::StrikeOut);
            m_hFont = (CreateFont(
                size,
                0,
                0,
                0,
                isBold ? FW_BOLD : FW_DONTCARE,
                isItalic,
                isUnderline,
                isStrikeOut,
                SHIFTJIS_CHARSET,
                OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS,
                DEFAULT_QUALITY,
                DEFAULT_PITCH,
                fontname));
            m_size = size;
        }

        void Font::Release()
        {
            if (m_hFont != nullptr)
            {
                DeleteObject(m_hFont);
                m_hFont = nullptr;
            }
        }
    }
}
