#pragma once

#include "zephyr\math.h"
#include "zephyr.linalg\Vector2.h"

#include "common.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// �񎟌��x�N�g����\���܂��B
        /// </summary>
        public value class Vector2
        {
        public:
            
            /// <summary>
            /// �S�����̒l���ʂɎw�肵�ăx�N�g�����쐬���܂��B
            /// </summary>
            /// <param name="x">X �̏����l</param> 
            /// <param name="y">Y �̏����l</param> 
            Vector2(float x, float y) : X(x), Y(y) {}

            Vector2(const zephyr::linalg::Vector2& v)
                : X(v.x), Y(v.y)
            {
            }

            /// <summary>
            /// ���̃x�N�g���𐳋K�����ĕԂ��܂��B
            /// </summary>
            Vector2 Normalize()
            {
                float oneOverMag = 1 / this->Magnitude;
                this->X *= oneOverMag;
                this->Y *= oneOverMag;
                return *this;
            }

            System::String^ ToString() override;

            /// <summary>
            /// �x�N�g���̑傫����Ԃ��܂��B
            /// </summary>
            property float Magnitude { float get() { return sqrt(X*X + Y*Y); } };

            /// <summary>
            /// �x�N�g���̑傫���̂Q���Ԃ��܂��B
            /// </summary>
            property float SquaredMagnitude { float get() { return X*X + Y*Y; } };

            /// <summary>
            /// ���K�������x�N�g����Ԃ��܂��B
            /// </summary>
            /// <param name="v">���K������x�N�g���B</param> 
            static Vector2 Normalize(Vector2 v)
            {
                return v.Normalize();
            }

            /// <summary>
            /// ��������x�N�g���ɕϊ����܂��B
            /// </summary>
            /// <param name="str">�ϊ����̕�����B�e�v�f�� , �ŋ�؂邱�ƁB</param> 
            static Vector2 Parse(System::String^ str);

            static Vector2 operator - (Vector2 a)
            {
                return Vector2(-a.X, -a.Y);
            }

            static Vector2 operator + (Vector2 a, Vector2 b)
            {
                return Vector2(a.X + b.X, a.Y + b.Y);
            }

            static Vector2 operator - (Vector2 a, Vector2 b)
            {
                return Vector2(a.X - b.X, a.Y - b.Y);
            }

            static Vector2 operator * (Vector2 v, float s)
            {
                return Vector2(v.X * s, v.Y * s);
            }

            static Vector2 operator * (float s, Vector2 v)
            {
                return Vector2(v.X * s, v.Y * s);
            }

            static Vector2 operator / (Vector2 v, float s)
            {
                return Vector2(v.X / s, v.Y / s);
            }

            /// <summary>
            /// �[���x�N�g���B
            /// </summary>
            static const Vector2 Zero = Vector2(0, 0);

            float X, Y;

        public:

            property zephyr::linalg::Vector2 Native
            {
                zephyr::linalg::Vector2 get()
                {
                    return zephyr::linalg::Vector2(X, Y);
                }

                void set(zephyr::linalg::Vector2 v)
                {
                    X = v.x;
                    Y = v.y;
                }
            }
        };
    }
}
