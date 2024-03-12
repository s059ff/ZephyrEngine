#pragma once

#include "zephyr\type.h"

namespace zephyr
{
    namespace graphics
    {
        struct ColorCode
        {
            ColorCode() : ColorCode(0, 0, 0, 255) {}

            ColorCode(byte r, byte g, byte b, byte a = 255) : r(r), g(g), b(b), a(a) {}

            byte r = 0, g = 0, b = 0, a = 0;

            static ColorCode FromRGBA(uint32_t code)
            {
                byte r = (code >> 24)& 0xff;
                byte g = (code >> 16)& 0xff;
                byte b = (code >> 8)& 0xff;
                byte a = (code >> 0)& 0xff;
                return ColorCode(r, g, b, a);
            }

            static ColorCode FromARGB(uint32_t code)
            {
                byte a = (code >> 24)& 0xff;
                byte r = (code >> 16)& 0xff;
                byte g = (code >> 8)& 0xff;
                byte b = (code >> 0)& 0xff;
                return ColorCode(r, g, b, a);
            }

            static ColorCode FromABGR(uint32_t code)
            {
                byte a = (code >> 24)& 0xff;
                byte b = (code >> 16)& 0xff;
                byte g = (code >> 8)& 0xff;
                byte r = (code >> 0)& 0xff;
                return ColorCode(r, g, b, a);
            }

            static ColorCode FromBGRA(uint32_t code)
            {
                byte b = (code >> 24)& 0xff;
                byte g = (code >> 16)& 0xff;
                byte r = (code >> 8)& 0xff;
                byte a = (code >> 0)& 0xff;
                return ColorCode(r, g, b, a);
            }

            static uint32_t ToRGBA(ColorCode code)
            {
                return (code.r << 24) | (code.g << 16) | (code.b << 8) | code.a;
            }

            static uint32_t ToARGB(ColorCode code)
            {
                return (code.a << 24) | (code.r << 16) | (code.g << 8) | code.b;
            }

            static uint32_t ToABGR(ColorCode code)
            {
                return (code.a << 24) | (code.b << 16) | (code.g << 8) | code.r;
            }

            static uint32_t ToBGRA(ColorCode code)
            {
                return (code.b << 24) | (code.g << 16) | (code.r << 8) | code.a;
            }

            static ColorCode FromRGBA(byte r, byte g, byte b, byte a)
            {
                return ColorCode(r, g, b, a);
            }

            static ColorCode FromARGB(byte a, byte r, byte g, byte b)
            {
                return ColorCode(r, g, b, a);
            }

            static ColorCode FromABGR(byte a, byte b, byte g, byte r)
            {
                return ColorCode(r, g, b, a);
            }

            static ColorCode FromBGRA(byte b, byte g, byte r, byte a)
            {
                return ColorCode(r, g, b, a);
            }

            static const ColorCode White;
            static const ColorCode Snow;
            static const ColorCode GhostWhite;
            static const ColorCode MintCream;
            static const ColorCode Azure;
            static const ColorCode Ivory;
            static const ColorCode FloralWhite;
            static const ColorCode AliceBlue;
            static const ColorCode LavenderBlush;
            static const ColorCode SeaShell;
            static const ColorCode WhiteSmoke;
            static const ColorCode Honeydew;
            static const ColorCode LightCyan;
            static const ColorCode LightYellow;
            static const ColorCode OldLace;
            static const ColorCode Cornsilk;
            static const ColorCode Linen;
            static const ColorCode LemonChiffon;
            static const ColorCode LightGoldenrodYellow;
            static const ColorCode Lavender;
            static const ColorCode Beige;
            static const ColorCode MistyRose;
            static const ColorCode PapayaWhip;
            static const ColorCode AntiqueWhite;
            static const ColorCode BlanchedAlmond;
            static const ColorCode Bisque;
            static const ColorCode Moccasin;
            static const ColorCode Gainsboro;
            static const ColorCode PeachPuff;
            static const ColorCode PaleTurquoise;
            static const ColorCode NavajoWhite;
            static const ColorCode Pink;
            static const ColorCode Wheat;
            static const ColorCode PaleGoldenrod;
            static const ColorCode LightGray;
            static const ColorCode LightPink;
            static const ColorCode PowderBlue;
            static const ColorCode Thistle;
            static const ColorCode LightBlue;
            static const ColorCode Khaki;
            static const ColorCode Violet;
            static const ColorCode Plum;
            static const ColorCode Aquamarine;
            static const ColorCode LightSteelBlue;
            static const ColorCode LightSkyBlue;
            static const ColorCode Silver;
            static const ColorCode SkyBlue;
            static const ColorCode PaleGreen;
            static const ColorCode Orchid;
            static const ColorCode BurlyWood;
            static const ColorCode HotPink;
            static const ColorCode LightSalmon;
            static const ColorCode Tan;
            static const ColorCode LightGreen;
            static const ColorCode Cyan;
            static const ColorCode Magenta;
            static const ColorCode Fuchsia;
            static const ColorCode Aqua;
            static const ColorCode Yellow;
            static const ColorCode DarkGray;
            static const ColorCode DarkSalmon;
            static const ColorCode SandyBrown;
            static const ColorCode LightCoral;
            static const ColorCode Turquoise;
            static const ColorCode Salmon;
            static const ColorCode CornflowerBlue;
            static const ColorCode MediumTurquoise;
            static const ColorCode MediumOrchid;
            static const ColorCode DarkKhaki;
            static const ColorCode MediumPurple;
            static const ColorCode PaleVioletRed;
            static const ColorCode MediumAquamarine;
            static const ColorCode GreenYellow;
            static const ColorCode RosyBrown;
            static const ColorCode Gold;
            static const ColorCode DarkSeaGreen;
            static const ColorCode MediumSlateBlue;
            static const ColorCode Coral;
            static const ColorCode DeepSkyBlue;
            static const ColorCode DodgerBlue;
            static const ColorCode Tomato;
            static const ColorCode DeepPink;
            static const ColorCode Orange;
            static const ColorCode DarkTurquoise;
            static const ColorCode Goldenrod;
            static const ColorCode CadetBlue;
            static const ColorCode YellowGreen;
            static const ColorCode LightSlateGray;
            static const ColorCode BlueViolet;
            static const ColorCode DarkOrchid;
            static const ColorCode MediumSpringGreen;
            static const ColorCode SlateBlue;
            static const ColorCode Peru;
            static const ColorCode RoyalBlue;
            static const ColorCode DarkOrange;
            static const ColorCode IndianRed;
            static const ColorCode Gray;
            static const ColorCode SlateGray;
            static const ColorCode Chartreuse;
            static const ColorCode SpringGreen;
            static const ColorCode LightSeaGreen;
            static const ColorCode SteelBlue;
            static const ColorCode LawnGreen;
            static const ColorCode DarkViolet;
            static const ColorCode MediumVioletRed;
            static const ColorCode MediumSeaGreen;
            static const ColorCode Chocolate;
            static const ColorCode DarkGoldenrod;
            static const ColorCode OrangeRed;
            static const ColorCode DimGray;
            static const ColorCode LimeGreen;
            static const ColorCode Crimson;
            static const ColorCode Sienna;
            static const ColorCode OliveDrab;
            static const ColorCode DarkMagenta;
            static const ColorCode DarkCyan;
            static const ColorCode SeaGreen;
            static const ColorCode DarkSlateBlue;
            static const ColorCode Teal;
            static const ColorCode Olive;
            static const ColorCode Purple;
            static const ColorCode Blue;
            static const ColorCode Lime;
            static const ColorCode Red;
            static const ColorCode Brown;
            static const ColorCode Firebrick;
            static const ColorCode DarkOliveGreen;
            static const ColorCode SaddleBrown;
            static const ColorCode ForestGreen;
            static const ColorCode DarkSlateGray;
            static const ColorCode MediumBlue;
            static const ColorCode Indigo;
            static const ColorCode MidnightBlue;
            static const ColorCode DarkBlue;
            static const ColorCode DarkRed;
            static const ColorCode Maroon;
            static const ColorCode Navy;
            static const ColorCode Green;
            static const ColorCode DarkGreen;
            static const ColorCode Black;
            static const ColorCode Transparent;
        };

        static_assert(sizeof(ColorCode) == 4, "ColorCode size is not 32bit.");
    }
}
