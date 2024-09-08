#pragma once

#include "zephyr\assert.h"
#include "zephyr\string.h"

#include "Matrix4x3.h"
#include "Matrix4x4.h"
#include "Vector2.h"

namespace zephyr
{
    namespace linalg
    {
        struct Matrix3x2
        {
            Matrix3x2() :
                m11(1), m12(0),
                m21(0), m22(1),
                m31(0), m32(0)
            {
            }

            Matrix3x2(
                float m11, float m12,
                float m21, float m22,
                float m31, float m32) :
                m11(m11), m12(m12),
                m21(m21), m22(m22),
                m31(m31), m32(m32)
            {
            }

            explicit Matrix3x2(const float(&m)[6]) :
                m11(m[0]), m12(m[1]),
                m21(m[2]), m22(m[3]),
                m31(m[4]), m32(m[5])
            {
            }

            operator Matrix4x3() const
            {
                float m13 = 0;
                float m23 = 0;
                float m31 = 0;
                float m32 = 0;
                float m33 = 1;
                float m41 = this->m31;
                float m42 = this->m32;
                float m43 = 0;
                return Matrix4x3(m11, m12, m13, m21, m22, m23, m31, m32, m33, m41, m42, m43);
            }

            operator Matrix4x4() const
            {
                float m13 = 0;
                float m23 = 0;
                float m31 = 0;
                float m32 = 0;
                float m33 = 1;
                float m41 = this->m31;
                float m42 = this->m32;
                float m43 = 0;
                return Matrix4x4(m11, m12, m13, 0, m21, m22, m23, 0, m31, m32, m33, 0, m41, m42, m43, 1);
            }

            Matrix3x2& identity()
            {
                this->m11 = 1; this->m12 = 0;
                this->m21 = 0; this->m22 = 1;
                this->m31 = 0; this->m32 = 0;
                return *this;
            }

            Matrix3x2& invert()
            {
                float det = this->determinant;
                assert(det != 0);

                float b11 = m22;
                float b12 = -m12;
                float b21 = -m21;
                float b22 = m11;

                float b31 = m21 * m32 - m22 * m31;
                float b32 = m12 * m31 - m11 * m32;

                this->m11 = b11 / det;
                this->m12 = b12 / det;
                this->m21 = b21 / det;
                this->m22 = b22 / det;
                this->m31 = b31 / det;
                this->m32 = b32 / det;

                return *this;
            }

            Matrix3x2& translate(float x, float y)
            {
                this->m31 += x * this->m11 + y * this->m21;
                this->m32 += x * this->m12 + y * this->m22;
                return *this;
            }

            Matrix3x2& translate(const Vector2& v)
            {
                this->translate(v.x, v.y);
                return *this;
            }

            Matrix3x2& scale(float sx, float sy)
            {
                this->m11 *= sx; this->m12 *= sx;
                this->m21 *= sy; this->m22 *= sy;
                return *this;
            }

            Matrix3x2& scale(float s)
            {
                this->m11 *= s; this->m12 *= s;
                this->m21 *= s; this->m22 *= s;
                this->m31 *= s; this->m32 *= s;
                return *this;
            }

            Matrix3x2& rotate(float r)
            {
                float cosθ = cos(r);
                float sinθ = sin(r);
                float m11 = this->m11 * cosθ + this->m21 * sinθ;
                float m12 = this->m12 * cosθ + this->m22 * sinθ;
                float m21 = -this->m11 * sinθ + this->m21 * cosθ;
                float m22 = -this->m12 * sinθ + this->m22 * cosθ;
                this->m11 = m11; this->m12 = m12;
                this->m21 = m21; this->m22 = m22;
                return *this;
            }

            Matrix3x2& transform(const Matrix3x2& m)
            {
                float _m11 = m.m11 * m11 + m.m12 * m21;
                float _m12 = m.m11 * m12 + m.m12 * m22;

                float _m21 = m.m21 * m11 + m.m22 * m21;
                float _m22 = m.m21 * m12 + m.m22 * m22;

                float _m31 = m.m31 * m11 + m.m32 * m21 + m31;
                float _m32 = m.m31 * m12 + m32 * m22 + m32;

                m11 = _m11; m12 = _m12;
                m21 = _m21; m22 = _m22;
                m31 = _m31; m32 = _m32;

                return *this;
            }

            float get_determinant() const
            {
                return m11 * m22 - m21 * m12;
            }

            Matrix3x2 get_inverse() const
            {
                Matrix3x2 ret = *this;
                ret.invert();
                return ret;
            }

            Vector2 get_position() const { return reinterpret_cast<const Vector2&>(m31); }

            void set_position(Vector2 v) { reinterpret_cast<Vector2&>(m31) = v; }

            __declspec(property(get = get_determinant)) float determinant;

            __declspec(property(get = get_inverse)) Matrix3x2 inverse;

            __declspec(property(get = get_position, put = set_position)) Vector2 position;

            float m11, m12;
            float m21, m22;
            float m31, m32;

        public:

            static Matrix3x2 Identity()
            {
                return Matrix3x2();
            }

            template <typename ...Args>
            static Matrix3x2 Translate(const Args& ...args)
            {
                return Matrix3x2().translate(args...);
            }

            template <typename ...Args>
            static Matrix3x2 Scale(const Args&...args)
            {
                return Matrix3x2().scale(args...);
            }

            static Matrix3x2 Rotate(float r)
            {
                return Matrix3x2().rotate(r);
            }

            static Matrix3x2 Parse(const string& str);
        };
    }
}
