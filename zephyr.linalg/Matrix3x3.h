#pragma once

#include "zephyr\assert.h"
#include "zephyr\string.h"

#include "Vector3.h"

namespace zephyr
{
    namespace linalg
    {
        struct Quaternion;

        struct Matrix3x3
        {
            Matrix3x3() :
                m11(1), m12(0), m13(0),
                m21(0), m22(1), m23(0),
                m31(0), m32(0), m33(1)
            {
            }

            Matrix3x3(
                float m11, float m12, float m13,
                float m21, float m22, float m23,
                float m31, float m32, float m33) :
                m11(m11), m12(m12), m13(m13),
                m21(m21), m22(m22), m23(m23),
                m31(m31), m32(m32), m33(m33)
            {
            }

            explicit Matrix3x3(const float m[9]) :
                m11(m[0]), m12(m[1]), m13(m[2]),
                m21(m[3]), m22(m[4]), m23(m[5]),
                m31(m[6]), m32(m[7]), m33(m[8])
            {
            }

            explicit Matrix3x3(const float m[3][3]) :
                m11(m[0][0]), m12(m[0][1]), m13(m[0][2]),
                m21(m[1][0]), m22(m[1][1]), m23(m[1][2]),
                m31(m[2][0]), m32(m[2][1]), m33(m[2][2])
            {
            }

            explicit Matrix3x3(const Quaternion& q);

            Matrix3x3& identity()
            {
                this->m11 = 1; this->m12 = 0; this->m13 = 0;
                this->m21 = 0; this->m22 = 1; this->m23 = 0;
                this->m31 = 0; this->m32 = 0; this->m33 = 1;
                return *this;
            }

            Matrix3x3& invert()
            {
                float det = this->determinant;
                assert(det != 0);
                float b11 = m22 * m33 - m23 * m32;
                float b12 = m13 * m32 - m12 * m33;
                float b13 = m12 * m23 - m13 * m22;
                float b21 = m23 * m31 - m21 * m33;
                float b22 = m11 * m33 - m13 * m31;
                float b23 = m13 * m21 - m11 * m23;
                float b31 = m21 * m32 - m22 * m31;
                float b32 = m12 * m31 - m11 * m32;
                float b33 = m11 * m22 - m12 * m21;
                this->m11 = b11 / det; this->m12 = b12 / det; this->m13 = b13 / det;
                this->m21 = b21 / det; this->m22 = b22 / det; this->m23 = b23 / det;
                this->m31 = b31 / det; this->m32 = b32 / det; this->m33 = b33 / det;
                return *this;
            }

            Matrix3x3& scale(float sx, float sy, float sz)
            {
                this->m11 *= sx; this->m12 *= sx; this->m13 *= sx;
                this->m21 *= sy; this->m22 *= sy; this->m23 *= sy;
                this->m31 *= sz; this->m32 *= sz; this->m33 *= sz;
                return *this;
            }

            Matrix3x3& scale(float s)
            {
                this->m11 *= s; this->m12 *= s; this->m13 *= s;
                this->m21 *= s; this->m22 *= s; this->m23 *= s;
                this->m31 *= s; this->m32 *= s; this->m33 *= s;
                return *this;
            }

            Matrix3x3& rotateX(float r)
            {
                float cos慮 = cos(r);
                float sin慮 = sin(r);
                float m21 = this->m21 * cos慮 + this->m31 * sin慮;
                float m22 = this->m22 * cos慮 + this->m32 * sin慮;
                float m23 = this->m23 * cos慮 + this->m33 * sin慮;
                float m31 = -this->m21 * sin慮 + this->m31 * cos慮;
                float m32 = -this->m22 * sin慮 + this->m32 * cos慮;
                float m33 = -this->m23 * sin慮 + this->m33 * cos慮;
                this->m21 = m21; this->m22 = m22; this->m23 = m23;
                this->m31 = m31; this->m32 = m32; this->m33 = m33;
                return *this;
            }

            Matrix3x3& rotateY(float r)
            {
                float cos慮 = cos(r);
                float sin慮 = sin(r);
                float m11 = this->m11 * cos慮 - this->m31 * sin慮;
                float m12 = this->m12 * cos慮 - this->m32 * sin慮;
                float m13 = this->m13 * cos慮 - this->m33 * sin慮;
                float m31 = this->m11 * sin慮 + this->m31 * cos慮;
                float m32 = this->m12 * sin慮 + this->m32 * cos慮;
                float m33 = this->m13 * sin慮 + this->m33 * cos慮;
                this->m11 = m11; this->m12 = m12; this->m13 = m13;
                this->m31 = m31; this->m32 = m32; this->m33 = m33;
                return *this;
            }

            Matrix3x3& rotateZ(float r)
            {
                float cos慮 = cos(r);
                float sin慮 = sin(r);
                float m11 = this->m11 * cos慮 + this->m21 * sin慮;
                float m12 = this->m12 * cos慮 + this->m22 * sin慮;
                float m13 = this->m13 * cos慮 + this->m23 * sin慮;
                float m21 = -this->m11 * sin慮 + this->m21 * cos慮;
                float m22 = -this->m12 * sin慮 + this->m22 * cos慮;
                float m23 = -this->m13 * sin慮 + this->m23 * cos慮;
                this->m11 = m11; this->m12 = m12; this->m13 = m13;
                this->m21 = m21; this->m22 = m22; this->m23 = m23;
                return *this;
            }

            Matrix3x3& transform(const Matrix3x3& m)
            {
                float _m11 = m.m11 * m11 + m.m12 * m21 + m.m13 * m31;
                float _m12 = m.m11 * m12 + m.m12 * m22 + m.m13 * m32;
                float _m13 = m.m11 * m13 + m.m12 * m23 + m.m13 * m33;

                float _m21 = m.m21 * m11 + m.m22 * m21 + m.m23 * m31;
                float _m22 = m.m21 * m12 + m.m22 * m22 + m.m23 * m32;
                float _m23 = m.m21 * m13 + m.m22 * m23 + m.m23 * m33;

                float _m31 = m.m31 * m11 + m.m32 * m21 + m.m33 * m31;
                float _m32 = m.m31 * m12 + m.m32 * m22 + m.m33 * m32;
                float _m33 = m.m31 * m13 + m.m32 * m23 + m.m33 * m33;

                m11 = _m11; m12 = _m12; m13 = _m13;
                m21 = _m21; m22 = _m22; m23 = _m23;
                m31 = _m31; m32 = _m32; m33 = _m33;

                return *this;
            }

            float get_determinant() const
            {
                return m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32
                    - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31;
            }

            Matrix3x3 get_inverse() const
            {
                Matrix3x3 ret = *this;
                ret.invert();
                return ret;
            }

            __declspec(property(get = get_determinant)) float determinant;

            __declspec(property(get = get_inverse)) Matrix3x3 inverse;

            __declspec(property(get = get_position, put = set_position)) Vector3 position;

            float m11, m12, m13;
            float m21, m22, m23;
            float m31, m32, m33;

        public:

            static Matrix3x3 Identity()
            {
                return Matrix3x3();
            }

            template <typename ...Args>
            static Matrix3x3 Scale(const Args&...args)
            {
                return Matrix3x3().scale(args...);
            }

            static Matrix3x3 RotateX(float r)
            {
                return Matrix3x3().rotateX(r);
            }

            static Matrix3x3 RotateY(float r)
            {
                return Matrix3x3().rotateY(r);
            }

            static Matrix3x3 RotateZ(float r)
            {
                return Matrix3x3().rotateZ(r);
            }

            static Matrix3x3 Parse(const string& str);
        };
    }
}
