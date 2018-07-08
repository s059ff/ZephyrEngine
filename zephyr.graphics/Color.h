#pragma once

#include "zephyr\math.h"
#include "zephyr\string.h"

#include "ColorCode.h"

namespace zephyr
{
    namespace graphics
    {
        /// <summary>
        /// 透明度を含む RGB カラーを表します。
        /// </summary>
        struct Color
        {
            Color() : r(0), g(0), b(0), a(1) {}

            /// <summary>
            /// 初期値を指定して、新しいインスタンスを初期化します。アルファ成分は 1.0f となります。
            /// </summary>
            /// <param name="r">赤。0.0f ～ 1.0f の範囲で指定。</param>
            /// <param name="g">緑。0.0f ～ 1.0f の範囲で指定。</param>
            /// <param name="b">青。0.0f ～ 1.0f の範囲で指定。</param>
            Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}

            /// <summary>
            /// 初期値を指定して、新しいインスタンスを初期化します。
            /// </summary>
            /// <param name="r">赤。0.0f ～ 1.0f の範囲で指定。</param>
            /// <param name="g">緑。0.0f ～ 1.0f の範囲で指定。</param>
            /// <param name="b">青。0.0f ～ 1.0f の範囲で指定。</param>
            /// <param name="a">アルファ。0.0f ～ 1.0f の範囲で指定。</param>
            Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

            /// <summary>
            /// カラーコードから新しいインスタンスを初期化します。
            /// </summary>
            /// <param name="code">カラーコード。</param>
            Color(ColorCode code) :
                r(float(code.r) / 255.0f),
                g(float(code.g) / 255.0f),
                b(float(code.b) / 255.0f),
                a(float(code.a) / 255.0f)
            {
            }

            /// <summary>
            /// カラーコードを取得します。
            /// </summary>
            __declspec(property(get = get_code)) ColorCode code;

            /// <summary>
            /// カラーコードを取得します。
            /// </summary>
            ColorCode get_code() const
            {
                byte r = (byte)(int)(this->r * 255.0f);
                byte g = (byte)(int)(this->g * 255.0f);
                byte b = (byte)(int)(this->b * 255.0f);
                byte a = (byte)(int)(this->a * 255.0f);

                return ColorCode::FromRGBA(r, g, b, a);
            }

            /// <summary>
            /// RGB 表色系から Color 構造体を作成します。アルファ成分は 1 になります。
            /// </summary>
            /// <param name="r">赤成分の値。0 ～ 1.0f 内で指定する。</param>
            /// <param name="g">緑成分の値。0 ～ 1.0f 内で指定する。</param>
            /// <param name="b">青成分の値。0 ～ 1.0f 内で指定する。</param>
            static Color FromRGB(float r, float g, float b) { return Color(r, g, b); }

            /// <summary>
            /// RGBA 表色系から Color 構造体を作成します。アルファ成分は 1 になります。
            /// </summary>
            /// <param name="r">赤成分の値。0 ～ 1.0f 内で指定する。</param>
            /// <param name="g">緑成分の値。0 ～ 1.0f 内で指定する。</param>
            /// <param name="b">青成分の値。0 ～ 1.0f 内で指定する。</param>
            /// <param name="a">アルファ成分の値。0 ～ 1.0f 内で指定する。</param>
            static Color FromRGB(float r, float g, float b, float a) { return Color(r, g, b, a); }

            /// <summary>
            /// HSV 表色系から Color 構造体を作成します。アルファ成分は 1 になります。
            /// </summary>
            /// <param name="hue">色相。0 ～ 1.0f 内で指定する。</param>
            /// <param name="saturation">彩度。0 ～ 1.0f 内で指定する。</param>
            /// <param name="brightness">明度。0 ～ 1.0f 内で指定する。</param>
            static Color FromHSV(float hue, float saturation, float brightness)
            {
                float v = brightness;
                float s = saturation;

                float r, g, b;
                if (s == 0)
                {
                    r = v;
                    g = v;
                    b = v;
                }
                else
                {
                    float h = hue * 6.0f;
                    int i = (int)floor(h);
                    float f = h - i;
                    float p = v * (1.0f - s);
                    float q;
                    if (i % 2 == 0)
                    {
                        q = v * (1.0f - (1.0f - f) * s);
                    }
                    else
                    {
                        q = v * (1.0f - f * s);
                    }

                    switch (i)
                    {
                    case 0:
                        r = v;
                        g = q;
                        b = p;
                        break;
                    case 1:
                        r = q;
                        g = v;
                        b = p;
                        break;
                    case 2:
                        r = p;
                        g = v;
                        b = q;
                        break;
                    case 3:
                        r = p;
                        g = q;
                        b = v;
                        break;
                    case 4:
                        r = q;
                        g = p;
                        b = v;
                        break;
                    case 5:
                        r = v;
                        g = p;
                        b = q;
                        break;
                    default:
                        r = g = b = 1;
                        break;
                    }
                }

                return Color(r, g, b);
            }

            /// <summary>
            /// カラーコードから Color 構造体を作成します。
            /// </summary>
            /// <param name="code">32bit ARGB カラーコード。</param>
            static Color FromCode(ColorCode code) { return Color(code); }

            static Color Parse(const string& str);

            float r, g, b, a;
        };
    }
}
