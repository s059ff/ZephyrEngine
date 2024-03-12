#pragma once

#include "zephyr\assert.h"
#include "zephyr\string.h"

#include "Vector3.h"
#include "Matrix3x3.h"

namespace zephyr
{
    namespace linalg
    {
        struct Quaternion;

        struct Matrix4x3
        {
            Matrix4x3() :
                m11(1), m12(0), m13(0),
                m21(0), m22(1), m23(0),
                m31(0), m32(0), m33(1),
                m41(0), m42(0), m43(0)
            {
            }

            Matrix4x3(
                float m11, float m12, float m13,
                float m21, float m22, float m23,
                float m31, float m32, float m33,
                float m41, float m42, float m43) :
                m11(m11), m12(m12), m13(m13),
                m21(m21), m22(m22), m23(m23),
                m31(m31), m32(m32), m33(m33),
                m41(m41), m42(m42), m43(m43)
            {
            }

            explicit Matrix4x3(const float m[12]) :
                m11(m[0]), m12(m[1]), m13(m[2]),
                m21(m[3]), m22(m[4]), m23(m[5]),
                m31(m[6]), m32(m[7]), m33(m[8]),
                m41(m[9]), m42(m[10]), m43(m[11])
            {
            }

            explicit Matrix4x3(const float m[4][3]) :
                m11(m[0][0]), m12(m[0][1]), m13(m[0][2]),
                m21(m[1][0]), m22(m[1][1]), m23(m[1][2]),
                m31(m[2][0]), m32(m[2][1]), m33(m[2][2]),
                m41(m[3][0]), m42(m[3][1]), m43(m[3][2])
            {
            }

            explicit Matrix4x3(const Quaternion& q);

            Matrix4x3(const Matrix3x3& m) :
                m11(m.m11), m12(m.m12), m13(m.m13),
                m21(m.m21), m22(m.m22), m23(m.m23),
                m31(m.m31), m32(m.m32), m33(m.m33),
                m41(0.0f), m42(0.0f), m43(0.0f)
            {
            }

            Matrix4x3& identity()
            {
                this->m11 = 1; this->m12 = 0; this->m13 = 0;
                this->m21 = 0; this->m22 = 1; this->m23 = 0;
                this->m31 = 0; this->m32 = 0; this->m33 = 1;
                this->m41 = 0; this->m42 = 0; this->m43 = 0;
                return *this;
            }

            Matrix4x3& invert()
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
                float b41 = m21 * m33 * m42 + m22 * m31 * m43 + m23 * m32 * m41 - m21 * m32 * m43 - m22 * m33 * m41 - m23 * m31 * m42;
                float b42 = m11 * m32 * m43 + m12 * m33 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 - m13 * m32 * m41;
                float b43 = m11 * m23 * m42 + m12 * m21 * m43 + m13 * m22 * m41 - m11 * m22 * m43 - m12 * m23 * m41 - m13 * m21 * m42;
                this->m11 = b11 / det; this->m12 = b12 / det; this->m13 = b13 / det;
                this->m21 = b21 / det; this->m22 = b22 / det; this->m23 = b23 / det;
                this->m31 = b31 / det; this->m32 = b32 / det; this->m33 = b33 / det;
                this->m41 = b41 / det; this->m42 = b42 / det; this->m43 = b43 / det;
                return *this;
            }

            Matrix4x3& lookAt(const Vector3& from, const Vector3& at, const Vector3& up)
            {
                Vector3 zaxis = subtract(at, from);
                Vector3 xaxis = outer(up, zaxis);
                Vector3 yaxis = outer(zaxis, xaxis);
                zaxis.normalize();
                xaxis.normalize();
                yaxis.normalize();
                this->m11 = xaxis.x; this->m12 = xaxis.y; this->m13 = xaxis.z;
                this->m21 = yaxis.x; this->m22 = yaxis.y; this->m23 = yaxis.z;
                this->m31 = zaxis.x; this->m32 = zaxis.y; this->m33 = zaxis.z;
                this->m41 = from.x; this->m42 = from.y; this->m43 = from.z;
                return *this;
            }

            Matrix4x3& lookAt(const Vector3& from, const Vector3& at)
            {
                this->lookAt(from, at, Vector3(0, 1, 0));
                return *this;
            }

            Matrix4x3& translate(float x, float y)
            {
                this->m41 += x * this->m11 + y * this->m21;
                this->m42 += x * this->m12 + y * this->m22;
                this->m43 += x * this->m13 + y * this->m23;
                return *this;
            }

            Matrix4x3& translate(float x, float y, float z)
            {
                this->m41 += x * this->m11 + y * this->m21 + z * this->m31;
                this->m42 += x * this->m12 + y * this->m22 + z * this->m32;
                this->m43 += x * this->m13 + y * this->m23 + z * this->m33;
                return *this;
            }

            Matrix4x3& translate(const Vector3& v)
            {
                this->translate(v.x, v.y, v.z);
                return *this;
            }

            Matrix4x3& scale(float sx, float sy, float sz)
            {
                this->m11 *= sx; this->m12 *= sx; this->m13 *= sx;
                this->m21 *= sy; this->m22 *= sy; this->m23 *= sy;
                this->m31 *= sz; this->m32 *= sz; this->m33 *= sz;
                return *this;
            }

            Matrix4x3& scale(float s)
            {
                this->m11 *= s; this->m12 *= s; this->m13 *= s;
                this->m21 *= s; this->m22 *= s; this->m23 *= s;
                this->m31 *= s; this->m32 *= s; this->m33 *= s;
                return *this;
            }

            Matrix4x3& rotateX(float r)
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

            Matrix4x3& rotateY(float r)
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

            Matrix4x3& rotateZ(float r)
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

            Matrix4x3& transform(const Matrix4x3& m)
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

                float _m41 = m.m41 * m11 + m.m42 * m21 + m.m43 * m31 + m41;
                float _m42 = m.m41 * m12 + m.m42 * m22 + m.m43 * m32 + m42;
                float _m43 = m.m41 * m13 + m.m42 * m23 + m.m43 * m33 + m43;

                m11 = _m11; m12 = _m12; m13 = _m13;
                m21 = _m21; m22 = _m22; m23 = _m23;
                m31 = _m31; m32 = _m32; m33 = _m33;
                m41 = _m41; m42 = _m42; m43 = _m43;

                return *this;
            }

            float get_determinant() const
            {
                return m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32
                    - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31;
            }

            Matrix4x3 get_inverse() const
            {
                Matrix4x3 ret = *this;
                ret.invert();
                return ret;
            }

            Vector3 get_position() const { return reinterpret_cast<const Vector3&>(m41); }

            void set_position(Vector3 v) { reinterpret_cast<Vector3&>(m41) = v; }

            Matrix3x3 get_matrix3x3() const { return Matrix3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33); }

            void set_matrix3x3(Matrix3x3 m)
            {
                m11 = m.m11; m12 = m.m12; m13 = m.m13;
                m21 = m.m21; m22 = m.m22; m23 = m.m23;
                m31 = m.m31; m32 = m.m32; m33 = m.m33;
            }

            __declspec(property(get = get_determinant)) float determinant;

            __declspec(property(get = get_inverse)) Matrix4x3 inverse;

            __declspec(property(get = get_position, put = set_position)) Vector3 position;

            __declspec(property(get = get_matrix3x3, put = set_matrix3x3)) Matrix3x3 matrix3x3;

            float m11, m12, m13;
            float m21, m22, m23;
            float m31, m32, m33;
            float m41, m42, m43;

        public:

            static Matrix4x3 Identity()
            {
                return Matrix4x3();
            }

            template <typename ...Args>
            static Matrix4x3 Translate(const Args& ...args)
            {
                return Matrix4x3().translate(args...);
            }

            template <typename ...Args>
            static Matrix4x3 Scale(const Args&...args)
            {
                return Matrix4x3().scale(args...);
            }

            static Matrix4x3 RotateX(float r)
            {
                return Matrix4x3().rotateX(r);
            }

            static Matrix4x3 RotateY(float r)
            {
                return Matrix4x3().rotateY(r);
            }

            static Matrix4x3 RotateZ(float r)
            {
                return Matrix4x3().rotateZ(r);
            }

            static Matrix4x3 Parse(const string& str);

        private:

            static Vector3 subtract(const Vector3& a, const Vector3& b)
            {
                return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
            }

            static Vector3 outer(const Vector3& a, const Vector3& b)
            {
                return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
            }
        };
    }
}
