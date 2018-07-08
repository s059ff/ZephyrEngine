#pragma once

#include "zephyr\array_cache.h"
#include "zephyr.graphics\Font.h"

#include "common.h"

namespace zephyr
{
    namespace graphics
    {
        namespace dx11
        {
            class Texture2D;

            class FontTexture
            {
            public:

                FontTexture();

                void Create(const char* familyname, int size, FontOption option = FontOption::Normal);

                void Release();

                Texture2D& Get(wchar_t code);

            private:

                Font font;

                array_cache<Texture2D> texes;
            };
        }
    }
}
