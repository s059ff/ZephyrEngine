#pragma once

#include "zephyr\math.h"

#include "ColorCode.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// 透明度を含む RGB カラーを表します。各要素は float 型になります。
        /// </summary>
        public value struct Color
        {
            /// <summary>
            /// 初期値を指定して、新しいインスタンスを初期化します。アルファ成分は 1.0f となります。
            /// </summary>
            /// <param name="r">赤。0.0f 〜 1.0f の範囲で指定。</param>
            /// <param name="g">緑。0.0f 〜 1.0f の範囲で指定。</param>
            /// <param name="b">青。0.0f 〜 1.0f の範囲で指定。</param>
            Color(float r, float g, float b) : R(r), G(g), B(b), A(1) {}

            /// <summary>
            /// 初期値を指定して、新しいインスタンスを初期化します。
            /// </summary>
            /// <param name="r">赤。0.0f 〜 1.0f の範囲で指定。</param>
            /// <param name="g">緑。0.0f 〜 1.0f の範囲で指定。</param>
            /// <param name="b">青。0.0f 〜 1.0f の範囲で指定。</param>
            /// <param name="a">アルファ。0.0f 〜 1.0f の範囲で指定。</param>
            Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}

            /// <summary>
            /// カラーコードから新しいインスタンスを初期化します。
            /// </summary>
            /// <param name="code">カラーコード。</param>
            Color(ColorCode code) :
                R(float(code.r) / 255.0f),
                G(float(code.g) / 255.0f),
                B(float(code.b) / 255.0f),
                A(float(code.a) / 255.0f)
            {
            }

            /// <summary>
            /// カラーコードを取得します。
            /// </summary>
            property ColorCode code
            {
                ColorCode get()
                {
                    byte r = (byte)(int)(this->R * 255.0f);
                    byte g = (byte)(int)(this->G * 255.0f);
                    byte b = (byte)(int)(this->B * 255.0f);
                    byte a = (byte)(int)(this->A * 255.0f);

                    return ColorCode::FromRGBA(r, g, b, a);
                }
            }

            System::String^ ToString() override
            {
                return System::String::Format("{0}, {1}, {2}, {3}", R, G, B, A);
            }

            /// <summary>
            /// 文字列を Color に変換します。
            /// </summary>
            /// <param name="str">変換元の文字列。各要素は , で区切ること。</param> 
            static Color Parse(System::String^ str)
            {
                array<System::String^>^ params = { "0", "0", "0", "0" };
                int i = 0;
                for each (auto s in str->Split(','))
                {
                    if (s != System::String::Empty)
                        params[i++] = s->Trim();
                }
                float r = System::Single::Parse(params[0]);
                float g = System::Single::Parse(params[1]);
                float b = System::Single::Parse(params[2]);
                float a = System::Single::Parse(params[3]);
                return Color(r, g, b, a);
            }

            /// <summary>
            /// RGB 表色系から Color 構造体を作成します。アルファ成分は 1 になります。
            /// </summary>
            /// <param name="r">赤成分の値。0 〜 1.0f 内で指定する。</param>
            /// <param name="g">緑成分の値。0 〜 1.0f 内で指定する。</param>
            /// <param name="b">青成分の値。0 〜 1.0f 内で指定する。</param>
            static Color FromRGB(float r, float g, float b) { return Color(r, g, b); }

            /// <summary>
            /// RGBA 表色系から Color 構造体を作成します。アルファ成分は 1 になります。
            /// </summary>
            /// <param name="r">赤成分の値。0 〜 1.0f 内で指定する。</param>
            /// <param name="g">緑成分の値。0 〜 1.0f 内で指定する。</param>
            /// <param name="b">青成分の値。0 〜 1.0f 内で指定する。</param>
            /// <param name="a">アルファ成分の値。0 〜 1.0f 内で指定する。</param>
            static Color FromRGB(float r, float g, float b, float a) { return Color(r, g, b, a); }

            /// <summary>
            /// HSV 表色系から Color 構造体を作成します。アルファ成分は 1 になります。
            /// </summary>
            /// <param name="hue">色相。0 〜 1.0f 内で指定する。</param>
            /// <param name="saturation">彩度。0 〜 1.0f 内で指定する。</param>
            /// <param name="brightness">明度。0 〜 1.0f 内で指定する。</param>
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

            /// <summary>
            /// R 値。
            /// </summary>
            float R;

            /// <summary>
            /// G 値。
            /// </summary>
            float G;

            /// <summary>
            /// B 値。
            /// </summary>
            float B;

            /// <summary>
            /// アルファ値。
            /// </summary>
            float A;
        };
    }
}
