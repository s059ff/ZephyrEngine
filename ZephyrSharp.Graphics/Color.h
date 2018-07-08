#pragma once

#include "zephyr\math.h"

#include "ColorCode.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �����x���܂� RGB �J���[��\���܂��B�e�v�f�� float �^�ɂȂ�܂��B
        /// </summary>
        public value struct Color
        {
            /// <summary>
            /// �����l���w�肵�āA�V�����C���X�^���X�����������܂��B�A���t�@������ 1.0f �ƂȂ�܂��B
            /// </summary>
            /// <param name="r">�ԁB0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="g">�΁B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="b">�B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            Color(float r, float g, float b) : R(r), G(g), B(b), A(1) {}

            /// <summary>
            /// �����l���w�肵�āA�V�����C���X�^���X�����������܂��B
            /// </summary>
            /// <param name="r">�ԁB0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="g">�΁B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="b">�B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            /// <param name="a">�A���t�@�B0.0f �` 1.0f �͈̔͂Ŏw��B</param>
            Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {}

            /// <summary>
            /// �J���[�R�[�h����V�����C���X�^���X�����������܂��B
            /// </summary>
            /// <param name="code">�J���[�R�[�h�B</param>
            Color(ColorCode code) :
                R(float(code.r) / 255.0f),
                G(float(code.g) / 255.0f),
                B(float(code.b) / 255.0f),
                A(float(code.a) / 255.0f)
            {
            }

            /// <summary>
            /// �J���[�R�[�h���擾���܂��B
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
            /// ������� Color �ɕϊ����܂��B
            /// </summary>
            /// <param name="str">�ϊ����̕�����B�e�v�f�� , �ŋ�؂邱�ƁB</param> 
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

            /// <summary>
            /// R �l�B
            /// </summary>
            float R;

            /// <summary>
            /// G �l�B
            /// </summary>
            float G;

            /// <summary>
            /// B �l�B
            /// </summary>
            float B;

            /// <summary>
            /// �A���t�@�l�B
            /// </summary>
            float A;
        };
    }
}
