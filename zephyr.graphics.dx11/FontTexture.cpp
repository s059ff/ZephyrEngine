#include "FontTexture.h"
#include "Texture2D.h"

#define this (*this)

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            FontTexture::FontTexture()
                : texes(65536, 1024)
            {
            }

            void FontTexture::Create(const char* familyname, int size, FontOption option)
            {
                this.font.Create(familyname, size, option);
            }

            Texture2D& FontTexture::Get(wchar_t code)
            {
                return this.texes.get(code);
            }
        }
    }
}
