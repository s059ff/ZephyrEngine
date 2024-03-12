#pragma once

#include "zephyr\type.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// 透明度を含む RGB カラーを表します。各要素は byte 型になります。
        /// </summary>
        public value struct ColorCode
        {
            /// <summary>
            /// 初期値を指定して、新しいインスタンスを初期化します。アルファ成分は 255 となります。
            /// </summary>
            /// <param name="r">赤。0 〜 255 の範囲で指定。</param>
            /// <param name="g">緑。0 〜 255 の範囲で指定。</param>
            /// <param name="b">青。0 〜 255 の範囲で指定。</param>
            ColorCode(byte r, byte g, byte b) : r(r), g(g), b(b), a(255) {}

            /// <summary>
            /// 初期値を指定して、新しいインスタンスを初期化します。
            /// </summary>
            /// <param name="r">赤。0 〜 255 の範囲で指定。</param>
            /// <param name="g">緑。0 〜 255 の範囲で指定。</param>
            /// <param name="b">青。0 〜 255 の範囲で指定。</param>
            /// <param name="a">アルファ。0 〜 255 の範囲で指定。</param>
            ColorCode(byte r, byte g, byte b, byte a) : r(r), g(g), b(b), a(a) {}

            byte r, g, b, a;

            /// <summary>
            /// RGBA の順に各要素が格納されている 32bit 整数を ColorCode に変換します。
            /// </summary>
            /// <param name="code">32bit RGBA コード。</param>
            static ColorCode FromRGBA(uint32_t code)
            {
                byte r = (code >> 24) & 0xff;
                byte g = (code >> 16) & 0xff;
                byte b = (code >> 8) & 0xff;
                byte a = (code >> 0) & 0xff;
                return ColorCode(r, g, b, a);
            }

            /// <summary>
            /// ARGB の順に各要素が格納されている 32bit 整数を ColorCode に変換します。
            /// </summary>
            /// <param name="code">32bit ARGB コード。</param>
            static ColorCode FromARGB(uint32_t code)
            {
                byte a = (code >> 24) & 0xff;
                byte r = (code >> 16) & 0xff;
                byte g = (code >> 8) & 0xff;
                byte b = (code >> 0) & 0xff;
                return ColorCode(r, g, b, a);
            }

            /// <summary>
            /// ABGR の順に各要素が格納されている 32bit 整数を ColorCode に変換します。
            /// </summary>
            /// <param name="code">32bit ABGR コード。</param>
            static ColorCode FromABGR(uint32_t code)
            {
                byte a = (code >> 24) & 0xff;
                byte b = (code >> 16) & 0xff;
                byte g = (code >> 8) & 0xff;
                byte r = (code >> 0) & 0xff;
                return ColorCode(r, g, b, a);
            }

            /// <summary>
            /// BGRA の順に各要素が格納されている 32bit 整数を ColorCode に変換します。
            /// </summary>
            /// <param name="code">32bit BGRA コード。</param>
            static ColorCode FromBGRA(uint32_t code)
            {
                byte b = (code >> 24) & 0xff;
                byte g = (code >> 16) & 0xff;
                byte r = (code >> 8) & 0xff;
                byte a = (code >> 0) & 0xff;
                return ColorCode(r, g, b, a);
            }

            /// <summary>
            /// ColorCode を 32bit RGBA コードに変換します。
            /// </summary>
            /// <param name="code">変換元の ColorCode。</param>
            static uint32_t ToRGBA(ColorCode code)
            {
                return (code.r << 24) | (code.g << 16) | (code.b << 8) | code.a;
            }

            /// <summary>
            /// ColorCode を 32bit ARGB コードに変換します。
            /// </summary>
            /// <param name="code">変換元の ColorCode。</param>
            static uint32_t ToARGB(ColorCode code)
            {
                return (code.a << 24) | (code.r << 16) | (code.g << 8) | code.b;
            }

            /// <summary>
            /// ColorCode を 32bit ABGR コードに変換します。
            /// </summary>
            /// <param name="code">変換元の ColorCode。</param>
            static uint32_t ToABGR(ColorCode code)
            {
                return (code.a << 24) | (code.b << 16) | (code.g << 8) | code.r;
            }

            /// <summary>
            /// ColorCode を 32bit BGRA コードに変換します。
            /// </summary>
            /// <param name="code">変換元の ColorCode。</param>
            static uint32_t ToBGRA(ColorCode code)
            {
                return (code.b << 24) | (code.g << 16) | (code.r << 8) | code.a;
            }

            /// <summary>
            /// 各要素を別々に指定して ColorCode を作成します。
            /// </summary>
            /// <param name="r">赤。0 〜 255 の範囲で指定。</param>
            /// <param name="g">緑。0 〜 255 の範囲で指定。</param>
            /// <param name="b">青。0 〜 255 の範囲で指定。</param>
            /// <param name="a">アルファ。0 〜 255 の範囲で指定。</param>
            static ColorCode FromRGBA(byte r, byte g, byte b, byte a)
            {
                return ColorCode(r, g, b, a);
            }

            /// <summary>
            /// 各要素を別々に指定して ColorCode を作成します。
            /// </summary>
            /// <param name="r">赤。0 〜 255 の範囲で指定。</param>
            /// <param name="g">緑。0 〜 255 の範囲で指定。</param>
            /// <param name="b">青。0 〜 255 の範囲で指定。</param>
            /// <param name="a">アルファ。0 〜 255 の範囲で指定。</param>
            static ColorCode FromARGB(byte a, byte r, byte g, byte b)
            {
                return ColorCode(r, g, b, a);
            }

            /// <summary>
            /// 各要素を別々に指定して ColorCode を作成します。
            /// </summary>
            /// <param name="r">赤。0 〜 255 の範囲で指定。</param>
            /// <param name="g">緑。0 〜 255 の範囲で指定。</param>
            /// <param name="b">青。0 〜 255 の範囲で指定。</param>
            /// <param name="a">アルファ。0 〜 255 の範囲で指定。</param>
            static ColorCode FromABGR(byte a, byte b, byte g, byte r)
            {
                return ColorCode(r, g, b, a);
            }

            /// <summary>
            /// 各要素を別々に指定して ColorCode を作成します。
            /// </summary>
            /// <param name="r">赤。0 〜 255 の範囲で指定。</param>
            /// <param name="g">緑。0 〜 255 の範囲で指定。</param>
            /// <param name="b">青。0 〜 255 の範囲で指定。</param>
            /// <param name="a">アルファ。0 〜 255 の範囲で指定。</param>
            static ColorCode FromBGRA(byte b, byte g, byte r, byte a)
            {
                return ColorCode(r, g, b, a);
            }

            static const ColorCode ColorCode::White = ColorCode::FromRGBA(0xFFFFFFFF);
            static const ColorCode ColorCode::Snow = ColorCode::FromRGBA(0xFFFAFAFF);
            static const ColorCode ColorCode::GhostWhite = ColorCode::FromRGBA(0xF8F8FFFF);
            static const ColorCode ColorCode::MintCream = ColorCode::FromRGBA(0xF5FFFAFF);
            static const ColorCode ColorCode::Azure = ColorCode::FromRGBA(0xF0FFFFFF);
            static const ColorCode ColorCode::Ivory = ColorCode::FromRGBA(0xFFFFF0FF);
            static const ColorCode ColorCode::FloralWhite = ColorCode::FromRGBA(0xFFFAF0FF);
            static const ColorCode ColorCode::AliceBlue = ColorCode::FromRGBA(0xF0F8FFFF);
            static const ColorCode ColorCode::LavenderBlush = ColorCode::FromRGBA(0xFFF0F5FF);
            static const ColorCode ColorCode::SeaShell = ColorCode::FromRGBA(0xFFF5EEFF);
            static const ColorCode ColorCode::WhiteSmoke = ColorCode::FromRGBA(0xF5F5F5FF);
            static const ColorCode ColorCode::Honeydew = ColorCode::FromRGBA(0xF0FFF0FF);
            static const ColorCode ColorCode::LightCyan = ColorCode::FromRGBA(0xE0FFFFFF);
            static const ColorCode ColorCode::LightYellow = ColorCode::FromRGBA(0xFFFFE0FF);
            static const ColorCode ColorCode::OldLace = ColorCode::FromRGBA(0xFDF5E6FF);
            static const ColorCode ColorCode::Cornsilk = ColorCode::FromRGBA(0xFFF8DCFF);
            static const ColorCode ColorCode::Linen = ColorCode::FromRGBA(0xFAF0E6FF);
            static const ColorCode ColorCode::LemonChiffon = ColorCode::FromRGBA(0xFFFACDFF);
            static const ColorCode ColorCode::LightGoldenrodYellow = ColorCode::FromRGBA(0xFAFAD2FF);
            static const ColorCode ColorCode::Lavender = ColorCode::FromRGBA(0xE6E6FAFF);
            static const ColorCode ColorCode::Beige = ColorCode::FromRGBA(0xF5F5DCFF);
            static const ColorCode ColorCode::MistyRose = ColorCode::FromRGBA(0xFFE4E1FF);
            static const ColorCode ColorCode::PapayaWhip = ColorCode::FromRGBA(0xFFEFD5FF);
            static const ColorCode ColorCode::AntiqueWhite = ColorCode::FromRGBA(0xFAEBD7FF);
            static const ColorCode ColorCode::BlanchedAlmond = ColorCode::FromRGBA(0xFFEBCDFF);
            static const ColorCode ColorCode::Bisque = ColorCode::FromRGBA(0xFFE4C4FF);
            static const ColorCode ColorCode::Moccasin = ColorCode::FromRGBA(0xFFE4B5FF);
            static const ColorCode ColorCode::Gainsboro = ColorCode::FromRGBA(0xDCDCDCFF);
            static const ColorCode ColorCode::PeachPuff = ColorCode::FromRGBA(0xFFDAB9FF);
            static const ColorCode ColorCode::PaleTurquoise = ColorCode::FromRGBA(0xAFEEEEFF);
            static const ColorCode ColorCode::NavajoWhite = ColorCode::FromRGBA(0xFFDEADFF);
            static const ColorCode ColorCode::Pink = ColorCode::FromRGBA(0xFFC0CBFF);
            static const ColorCode ColorCode::Wheat = ColorCode::FromRGBA(0xF5DEB3FF);
            static const ColorCode ColorCode::PaleGoldenrod = ColorCode::FromRGBA(0xEEE8AAFF);
            static const ColorCode ColorCode::LightGray = ColorCode::FromRGBA(0xD3D3D3FF);
            static const ColorCode ColorCode::LightPink = ColorCode::FromRGBA(0xFFB6C1FF);
            static const ColorCode ColorCode::PowderBlue = ColorCode::FromRGBA(0xB0E0E6FF);
            static const ColorCode ColorCode::Thistle = ColorCode::FromRGBA(0xD8BFD8FF);
            static const ColorCode ColorCode::LightBlue = ColorCode::FromRGBA(0xADD8E6FF);
            static const ColorCode ColorCode::Khaki = ColorCode::FromRGBA(0xF0E68CFF);
            static const ColorCode ColorCode::Violet = ColorCode::FromRGBA(0xEE82EEFF);
            static const ColorCode ColorCode::Plum = ColorCode::FromRGBA(0xDDA0DDFF);
            static const ColorCode ColorCode::Aquamarine = ColorCode::FromRGBA(0x7FFFD4FF);
            static const ColorCode ColorCode::LightSteelBlue = ColorCode::FromRGBA(0xB0C4DEFF);
            static const ColorCode ColorCode::LightSkyBlue = ColorCode::FromRGBA(0x87CEFAFF);
            static const ColorCode ColorCode::Silver = ColorCode::FromRGBA(0xC0C0C0FF);
            static const ColorCode ColorCode::SkyBlue = ColorCode::FromRGBA(0x87CEEBFF);
            static const ColorCode ColorCode::PaleGreen = ColorCode::FromRGBA(0x98FB98FF);
            static const ColorCode ColorCode::Orchid = ColorCode::FromRGBA(0xDA70D6FF);
            static const ColorCode ColorCode::BurlyWood = ColorCode::FromRGBA(0xDEB887FF);
            static const ColorCode ColorCode::HotPink = ColorCode::FromRGBA(0xFF69B4FF);
            static const ColorCode ColorCode::LightSalmon = ColorCode::FromRGBA(0xFFA07AFF);
            static const ColorCode ColorCode::Tan = ColorCode::FromRGBA(0xD2B48CFF);
            static const ColorCode ColorCode::LightGreen = ColorCode::FromRGBA(0x90EE90FF);
            static const ColorCode ColorCode::Cyan = ColorCode::FromRGBA(0x00FFFFFF);
            static const ColorCode ColorCode::Magenta = ColorCode::FromRGBA(0xFF00FFFF);
            static const ColorCode ColorCode::Fuchsia = ColorCode::FromRGBA(0xFF00FFFF);
            static const ColorCode ColorCode::Aqua = ColorCode::FromRGBA(0x00FFFFFF);
            static const ColorCode ColorCode::Yellow = ColorCode::FromRGBA(0xFFFF00FF);
            static const ColorCode ColorCode::DarkGray = ColorCode::FromRGBA(0xA9A9A9FF);
            static const ColorCode ColorCode::DarkSalmon = ColorCode::FromRGBA(0xE9967AFF);
            static const ColorCode ColorCode::SandyBrown = ColorCode::FromRGBA(0xF4A460FF);
            static const ColorCode ColorCode::LightCoral = ColorCode::FromRGBA(0xF08080FF);
            static const ColorCode ColorCode::Turquoise = ColorCode::FromRGBA(0x40E0D0FF);
            static const ColorCode ColorCode::Salmon = ColorCode::FromRGBA(0xFA8072FF);
            static const ColorCode ColorCode::CornflowerBlue = ColorCode::FromRGBA(0x6495EDFF);
            static const ColorCode ColorCode::MediumTurquoise = ColorCode::FromRGBA(0x48D1CCFF);
            static const ColorCode ColorCode::MediumOrchid = ColorCode::FromRGBA(0xBA55D3FF);
            static const ColorCode ColorCode::DarkKhaki = ColorCode::FromRGBA(0xBDB76BFF);
            static const ColorCode ColorCode::MediumPurple = ColorCode::FromRGBA(0x9370DBFF);
            static const ColorCode ColorCode::PaleVioletRed = ColorCode::FromRGBA(0xDB7093FF);
            static const ColorCode ColorCode::MediumAquamarine = ColorCode::FromRGBA(0x66CDAAFF);
            static const ColorCode ColorCode::GreenYellow = ColorCode::FromRGBA(0xADFF2FFF);
            static const ColorCode ColorCode::RosyBrown = ColorCode::FromRGBA(0xBC8F8FFF);
            static const ColorCode ColorCode::Gold = ColorCode::FromRGBA(0xFFD700FF);
            static const ColorCode ColorCode::DarkSeaGreen = ColorCode::FromRGBA(0x8FBC8BFF);
            static const ColorCode ColorCode::MediumSlateBlue = ColorCode::FromRGBA(0x7B68EEFF);
            static const ColorCode ColorCode::Coral = ColorCode::FromRGBA(0xFF7F50FF);
            static const ColorCode ColorCode::DeepSkyBlue = ColorCode::FromRGBA(0x00BFFFFF);
            static const ColorCode ColorCode::DodgerBlue = ColorCode::FromRGBA(0x1E90FFFF);
            static const ColorCode ColorCode::Tomato = ColorCode::FromRGBA(0xFF6347FF);
            static const ColorCode ColorCode::DeepPink = ColorCode::FromRGBA(0xFF1493FF);
            static const ColorCode ColorCode::Orange = ColorCode::FromRGBA(0xFFA500FF);
            static const ColorCode ColorCode::DarkTurquoise = ColorCode::FromRGBA(0x00CED1FF);
            static const ColorCode ColorCode::Goldenrod = ColorCode::FromRGBA(0xDAA520FF);
            static const ColorCode ColorCode::CadetBlue = ColorCode::FromRGBA(0x5F9EA0FF);
            static const ColorCode ColorCode::YellowGreen = ColorCode::FromRGBA(0x9ACD32FF);
            static const ColorCode ColorCode::LightSlateGray = ColorCode::FromRGBA(0x778899FF);
            static const ColorCode ColorCode::BlueViolet = ColorCode::FromRGBA(0x8A2BE2FF);
            static const ColorCode ColorCode::DarkOrchid = ColorCode::FromRGBA(0x9932CCFF);
            static const ColorCode ColorCode::MediumSpringGreen = ColorCode::FromRGBA(0x00FA9AFF);
            static const ColorCode ColorCode::SlateBlue = ColorCode::FromRGBA(0x6A5ACDFF);
            static const ColorCode ColorCode::Peru = ColorCode::FromRGBA(0xCD853FFF);
            static const ColorCode ColorCode::RoyalBlue = ColorCode::FromRGBA(0x4169E1FF);
            static const ColorCode ColorCode::DarkOrange = ColorCode::FromRGBA(0xFF8C00FF);
            static const ColorCode ColorCode::IndianRed = ColorCode::FromRGBA(0xCD5C5CFF);
            static const ColorCode ColorCode::Gray = ColorCode::FromRGBA(0x808080FF);
            static const ColorCode ColorCode::SlateGray = ColorCode::FromRGBA(0x708090FF);
            static const ColorCode ColorCode::Chartreuse = ColorCode::FromRGBA(0x7FFF00FF);
            static const ColorCode ColorCode::SpringGreen = ColorCode::FromRGBA(0x00FF7FFF);
            static const ColorCode ColorCode::LightSeaGreen = ColorCode::FromRGBA(0x20B2AAFF);
            static const ColorCode ColorCode::SteelBlue = ColorCode::FromRGBA(0x4682B4FF);
            static const ColorCode ColorCode::LawnGreen = ColorCode::FromRGBA(0x7CFC00FF);
            static const ColorCode ColorCode::DarkViolet = ColorCode::FromRGBA(0x9400D3FF);
            static const ColorCode ColorCode::MediumVioletRed = ColorCode::FromRGBA(0xC71585FF);
            static const ColorCode ColorCode::MediumSeaGreen = ColorCode::FromRGBA(0x3CB371FF);
            static const ColorCode ColorCode::Chocolate = ColorCode::FromRGBA(0xD2691EFF);
            static const ColorCode ColorCode::DarkGoldenrod = ColorCode::FromRGBA(0xB8860BFF);
            static const ColorCode ColorCode::OrangeRed = ColorCode::FromRGBA(0xFF4500FF);
            static const ColorCode ColorCode::DimGray = ColorCode::FromRGBA(0x696969FF);
            static const ColorCode ColorCode::LimeGreen = ColorCode::FromRGBA(0x32CD32FF);
            static const ColorCode ColorCode::Crimson = ColorCode::FromRGBA(0xDC143CFF);
            static const ColorCode ColorCode::Sienna = ColorCode::FromRGBA(0xA0522DFF);
            static const ColorCode ColorCode::OliveDrab = ColorCode::FromRGBA(0x6B8E23FF);
            static const ColorCode ColorCode::DarkMagenta = ColorCode::FromRGBA(0x8B008BFF);
            static const ColorCode ColorCode::DarkCyan = ColorCode::FromRGBA(0x008B8BFF);
            static const ColorCode ColorCode::SeaGreen = ColorCode::FromRGBA(0x2E8B57FF);
            static const ColorCode ColorCode::DarkSlateBlue = ColorCode::FromRGBA(0x483D8BFF);
            static const ColorCode ColorCode::Teal = ColorCode::FromRGBA(0x008080FF);
            static const ColorCode ColorCode::Olive = ColorCode::FromRGBA(0x808000FF);
            static const ColorCode ColorCode::Purple = ColorCode::FromRGBA(0x800080FF);
            static const ColorCode ColorCode::Blue = ColorCode::FromRGBA(0x0000FFFF);
            static const ColorCode ColorCode::Lime = ColorCode::FromRGBA(0x00FF00FF);
            static const ColorCode ColorCode::Red = ColorCode::FromRGBA(0xFF0000FF);
            static const ColorCode ColorCode::Brown = ColorCode::FromRGBA(0xA52A2AFF);
            static const ColorCode ColorCode::Firebrick = ColorCode::FromRGBA(0xB22222FF);
            static const ColorCode ColorCode::DarkOliveGreen = ColorCode::FromRGBA(0x556B2FFF);
            static const ColorCode ColorCode::SaddleBrown = ColorCode::FromRGBA(0x8B4513FF);
            static const ColorCode ColorCode::ForestGreen = ColorCode::FromRGBA(0x228B22FF);
            static const ColorCode ColorCode::DarkSlateGray = ColorCode::FromRGBA(0x2F4F4FFF);
            static const ColorCode ColorCode::MediumBlue = ColorCode::FromRGBA(0x0000CDFF);
            static const ColorCode ColorCode::Indigo = ColorCode::FromRGBA(0x4B0082FF);
            static const ColorCode ColorCode::MidnightBlue = ColorCode::FromRGBA(0x191970FF);
            static const ColorCode ColorCode::DarkBlue = ColorCode::FromRGBA(0x00008BFF);
            static const ColorCode ColorCode::DarkRed = ColorCode::FromRGBA(0x8B0000FF);
            static const ColorCode ColorCode::Maroon = ColorCode::FromRGBA(0x800000FF);
            static const ColorCode ColorCode::Navy = ColorCode::FromRGBA(0x000080FF);
            static const ColorCode ColorCode::Green = ColorCode::FromRGBA(0x008000FF);
            static const ColorCode ColorCode::DarkGreen = ColorCode::FromRGBA(0x006400FF);
            static const ColorCode ColorCode::Black = ColorCode::FromRGBA(0x000000FF);
            static const ColorCode ColorCode::Transparent = ColorCode::FromRGBA(0x00000000);
        };
    }
}
