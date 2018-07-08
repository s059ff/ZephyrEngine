#pragma once

#include "zephyr\math.h"
#include "zephyr.linalg\Vector3.h"

#include "common.h"

using namespace zephyr;

namespace ZephyrSharp
{
    namespace Linalg
    {
        /// <summary>
        /// �O�����x�N�g����\���܂��B
        /// </summary>
        public value class Vector3
        {
        public:

            /// <summary>
            /// �S�����̒l���ʂɎw�肵�ăx�N�g�����쐬���܂��B
            /// </summary>
            /// <param name="x">X �̏����l</param> 
            /// <param name="y">Y �̏����l</param> 
            /// <param name="z">Z �̏����l</param> 
            Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

            Vector3(const zephyr::linalg::Vector3& v)
                : X(v.x), Y(v.y), Z(v.z)
            {
            }

            /// <summary>
            /// ���̃x�N�g���𐳋K�����ĕԂ��܂��B
            /// </summary>
            Vector3 Normalize()
            {
                float oneOverMag = 1 / this->Magnitude;
                this->X *= oneOverMag;
                this->Y *= oneOverMag;
                this->Z *= oneOverMag;
                return *this;
            }

            System::String^ ToString() override;

            /// <summary>
            /// �x�N�g���̑傫����Ԃ��܂��B
            /// </summary>
            property float Magnitude { float get() { return sqrt(X*X + Y*Y + Z*Z); } };

            /// <summary>
            /// �x�N�g���̑傫���̂Q���Ԃ��܂��B
            /// </summary>
            property float SquaredMagnitude { float get() { return X*X + Y*Y + Z*Z; } };

            /// <summary>
            /// ���K�������x�N�g����Ԃ��܂��B
            /// </summary>
            /// <param name="v">���K������x�N�g���B</param> 
            static Vector3 Normalize(Vector3 v)
            {
                return v.Normalize();
            }

            /// <summary>
            /// �x�N�g���̓��ς�Ԃ��܂��B
            /// </summary>
            /// <param name="a">���Z�Ώۂ̃x�N�g���B</param> 
            /// <param name="b">���Z�Ώۂ̃x�N�g���B</param> 
            static float Inner(Vector3 a, Vector3 b)
            {
                return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
            }

            /// <summary>
            /// �x�N�g���̊O�ς�Ԃ��܂��B
            /// </summary>
            /// <param name="a">���Z�Ώۂ̃x�N�g���B</param> 
            /// <param name="b">���Z�Ώۂ̃x�N�g���B</param> 
            static Vector3 Outer(Vector3 a, Vector3 b)
            {
                return Vector3(a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z, a.X * b.Y - a.Y * b.X);
            }

            /// <summary>
            /// ��̃x�N�g���̐����p��Ԃ��܂��B
            /// </summary>
            /// <param name="a">���Z�Ώۂ̃x�N�g���B</param> 
            /// <param name="b">���Z�Ώۂ̃x�N�g���B</param> 
            static float Angle(Vector3 a, Vector3 b)
            {
                float cos = Inner(a, b) / (a.Magnitude * b.Magnitude);
                return acos((cos > 1) ? 1 : (cos < -1) ? -1 : cos);
            }

            /// <summary>
            /// ����x�N�g����ʂ̃x�N�g���ɓ��e�����x�N�g����Ԃ��܂��B
            /// </summary>
            /// <param name="v">���e����x�N�g���B</param> 
            /// <param name="n">���e�����x�N�g���B</param> 
            static Vector3 Project(Vector3 v, Vector3 n)
            {
                return n * (Inner(v, n) / n.SquaredMagnitude);
            }

            /// <summary>
            /// ��������x�N�g���ɕϊ����܂��B
            /// </summary>
            /// <param name="str">�ϊ����̕�����B�e�v�f�� , �ŋ�؂邱�ƁB</param> 
            static Vector3 Parse(System::String^ str);

            /// <summary>
            /// �[���x�N�g���B
            /// </summary>
            static const Vector3 Zero = Vector3(0, 0, 0);

            static Vector3 operator - (Vector3 v)
            {
                return Vector3(-v.X, -v.Y, -v.Z);
            }

            static Vector3 operator +(Vector3 a, Vector3 b)
            {
                return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
            }

            static Vector3 operator -(Vector3 a, Vector3 b)
            {
                return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
            }

            static Vector3 operator *(Vector3 v, float s)
            {
                return Vector3(s * v.X, s * v.Y, s * v.Z);
            }

            static Vector3 operator *(float s, Vector3 v)
            {
                return Vector3(s * v.X, s * v.Y, s * v.Z);
            }

            static Vector3 operator /(Vector3 v, float s)
            {
                return Vector3(v.X / s, v.Y / s, v.Z / s);
            }

            float X, Y, Z;

        public:

            property zephyr::linalg::Vector3 Native
            {
                zephyr::linalg::Vector3 get()
                {
                    return zephyr::linalg::Vector3(X, Y, Z);
                }

                void set(zephyr::linalg::Vector3 v)
                {
                    X = v.x;
                    Y = v.y;
                    Z = v.z;
                }
            }
        };
    }
}
