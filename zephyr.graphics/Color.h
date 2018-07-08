#pragma once

#include "zephyr\math.h"
#include "zephyr\string.h"

#include "ColorCode.h"

namespace zephyr
{
    namespace graphics
    {
        /// <summary>
        /// �����x���܂� RGB �J���[��\���܂��B
        /// </summary>
        struct Color
        {
            Color() : r(0), g(0), b(0), a(1) {}

            /// <summary>
            /// �����l���w�肵�āA�V�����C���X�^���X�����������܂��B�A���t�@������ 1.0f �ƂȂ�܂��B
            /// </summary>
            /// <param name="r">�ԁB0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="g">�΁B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="b">�B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            Color(float r, float g, float b) : r(r), g(g), b(b), a(1) {}

            /// <summary>
            /// �����l���w�肵�āA�V�����C���X�^���X�����������܂��B
            /// </summary>
            /// <param name="r">�ԁB0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="g">�΁B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="b">�B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="a">�A���t�@�B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}

            /// <summary>
            /// �J���[�R�[�h����V�����C���X�^���X�����������܂��B
            /// </summary>
            /// <param name="code">�J���[�R�[�h�B</param>
            Color(ColorCode code) :
                r(float(code.r) / 255.0f),
                g(float(code.g) / 255.0f),
                b(float(code.b) / 255.0f),
                a(float(code.a) / 255.0f)
            {
            }

            /// <summary>
            /// �J���[�R�[�h���擾���܂��B
            /// </summary>
            __declspec(property(get = get_code)) ColorCode code;

            /// <summary>
            /// �J���[�R�[�h���擾���܂��B
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
            /// RGB �\�F�n���� Color �\���̂��쐬���܂��B�A���t�@������ 1 �ɂȂ�܂��B
            /// </summary>
            /// <param name="r">�Ԑ����̒l�B0 �` 1.0f ���Ŏw�肷��B</param>
            /// <param name="g">�ΐ����̒l�B0 �` 1.0f ���Ŏw�肷��B</param>
            /// <param name="b">�����̒l�B0 �` 1.0f ���Ŏw�肷��B</param>
            static Color FromRGB(float r, float g, float b) { return Color(r, g, b); }

            /// <summary>
            /// RGBA �\�F�n���� Color �\���̂��쐬���܂��B�A���t�@������ 1 �ɂȂ�܂��B
            /// </summary>
            /// <param name="r">�Ԑ����̒l�B0 �` 1.0f ���Ŏw�肷��B</param>
            /// <param name="g">�ΐ����̒l�B0 �` 1.0f ���Ŏw�肷��B</param>
            /// <param name="b">�����̒l�B0 �` 1.0f ���Ŏw�肷��B</param>
            /// <param name="a">�A���t�@�����̒l�B0 �` 1.0f ���Ŏw�肷��B</param>
            static Color FromRGB(float r, float g, float b, float a) { return Color(r, g, b, a); }

            /// <summary>
            /// HSV �\�F�n���� Color �\���̂��쐬���܂��B�A���t�@������ 1 �ɂȂ�܂��B
            /// </summary>
            /// <param name="hue">�F���B0 �` 1.0f ���Ŏw�肷��B</param>
            /// <param name="saturation">�ʓx�B0 �` 1.0f ���Ŏw�肷��B</param>
            /// <param name="brightness">���x�B0 �` 1.0f ���Ŏw�肷��B</param>
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
            /// �J���[�R�[�h���� Color �\���̂��쐬���܂��B
            /// </summary>
            /// <param name="code">32bit ARGB �J���[�R�[�h�B</param>
            static Color FromCode(ColorCode code) { return Color(code); }

            static Color Parse(const string& str);

            float r, g, b, a;
        };
    }
}
