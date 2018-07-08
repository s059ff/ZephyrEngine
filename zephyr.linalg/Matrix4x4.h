#pragma once

#include "zephyr\assert.h"
#include "zephyr\string.h"

#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x3.h"

namespace zephyr
{
    namespace linalg
    {
        struct Quaternion;

        struct Matrix4x4
        {
            Matrix4x4() :
                m11(1), m12(0), m13(0), m14(0),
                m21(0), m22(1), m23(0), m24(0),
                m31(0), m32(0), m33(1), m34(0),
                m41(0), m42(0), m43(0), m44(1)
            {
            }

            Matrix4x4(
                float m11, float m12, float m13, float m14,
                float m21, float m22, float m23, float m24,
                float m31, float m32, float m33, float m34,
                float m41, float m42, float m43, float m44) :
                m11(m11), m12(m12), m13(m13), m14(m14),
                m21(m21), m22(m22), m23(m23), m24(m24),
                m31(m31), m32(m32), m33(m33), m34(m34),
                m41(m41), m42(m42), m43(m43), m44(m44)
            {
            }

            explicit Matrix4x4(const float m[16]) :
                m11(m[0]), m12(m[1]), m13(m[2]), m14(m[3]),
                m21(m[4]), m22(m[5]), m23(m[6]), m24(m[7]),
                m31(m[8]), m32(m[9]), m33(m[10]), m34(m[11]),
                m41(m[12]), m42(m[13]), m43(m[14]), m44(m[15])
            {
            }

            explicit Matrix4x4(const float m[4][4]) :
                m11(m[0][0]), m12(m[0][1]), m13(m[0][2]), m14(m[0][3]),
                m21(m[1][0]), m22(m[1][1]), m23(m[1][2]), m24(m[1][3]),
                m31(m[2][0]), m32(m[2][1]), m33(m[2][2]), m34(m[2][3]),
                m41(m[3][0]), m42(m[3][1]), m43(m[3][2]), m44(m[3][3])
            {
            }

            explicit Matrix4x4(const Quaternion& q);

            Matrix4x4(const Matrix3x3& m) :
                m11(m.m11), m12(m.m12), m13(m.m13), m14(0),
                m21(m.m21), m22(m.m22), m23(m.m23), m24(0),
                m31(m.m31), m32(m.m32), m33(m.m33), m34(0),
                m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f)
            {
            }

            Matrix4x4(const Matrix4x3& m) :
                m11(m.m11), m12(m.m12), m13(m.m13), m14(0),
                m21(m.m21), m22(m.m22), m23(m.m23), m24(0),
                m31(m.m31), m32(m.m32), m33(m.m33), m34(0),
                m41(m.m41), m42(m.m42), m43(m.m43), m44(1)
            {
            }

            Matrix4x4& identity()
            {
                this->m11 = 1; this->m12 = 0; this->m13 = 0; this->m14 = 0;
                this->m21 = 0; this->m22 = 1; this->m23 = 0; this->m24 = 0;
                this->m31 = 0; this->m32 = 0; this->m33 = 1; this->m34 = 0;
                this->m41 = 0; this->m42 = 0; this->m43 = 0; this->m44 = 1;
                return *this;
            }

            Matrix4x4& invert()
            {
                float det = this->determinant;
                assert(det != 0);
                float b11 = m22 * m33 * m44 + m23 * m34 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 - m24 * m33 * m42;
                float b12 = m12 * m34 * m43 + m13 * m32 * m44 + m14 * m33 * m42 - m12 * m33 * m44 - m13 * m34 * m42 - m14 * m32 * m43;
                float b13 = m12 * m23 * m44 + m13 * m24 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 - m14 * m23 * m42;
                float b14 = m12 * m24 * m33 + m13 * m22 * m34 + m14 * m23 * m32 - m12 * m23 * m34 - m13 * m24 * m32 - m14 * m22 * m33;
                float b21 = m21 * m34 * m43 + m23 * m31 * m44 + m24 * m33 * m41 - m21 * m33 * m44 - m23 * m34 * m41 - m24 * m31 * m43;
                float b22 = m11 * m33 * m44 + m13 * m34 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 - m14 * m33 * m41;
                float b23 = m11 * m24 * m43 + m13 * m21 * m44 + m14 * m23 * m41 - m11 * m23 * m44 - m13 * m24 * m41 - m14 * m21 * m43;
                float b24 = m11 * m23 * m34 + m13 * m24 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 - m14 * m23 * m31;
                float b31 = m21 * m32 * m44 + m22 * m34 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 - m24 * m32 * m41;
                float b32 = m11 * m34 * m42 + m12 * m31 * m44 + m14 * m32 * m41 - m11 * m32 * m44 - m12 * m34 * m41 - m14 * m31 * m42;
                float b33 = m11 * m22 * m44 + m12 * m24 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 - m14 * m22 * m41;
                float b34 = m11 * m24 * m32 + m12 * m21 * m34 + m14 * m22 * m31 - m11 * m22 * m34 - m12 * m24 * m31 - m14 * m21 * m32;
                float b41 = m21 * m33 * m42 + m22 * m31 * m43 + m23 * m32 * m41 - m21 * m32 * m43 - m22 * m33 * m41 - m23 * m31 * m42;
                float b42 = m11 * m32 * m43 + m12 * m33 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 - m13 * m32 * m41;
                float b43 = m11 * m23 * m42 + m12 * m21 * m43 + m13 * m22 * m41 - m11 * m22 * m43 - m12 * m23 * m41 - m13 * m21 * m42;
                float b44 = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31;
                this->m11 = b11 / det; this->m12 = b12 / det; this->m13 = b13 / det; this->m14 = b14 / det;
                this->m21 = b21 / det; this->m22 = b22 / det; this->m23 = b23 / det; this->m24 = b24 / det;
                this->m31 = b31 / det; this->m32 = b32 / det; this->m33 = b33 / det; this->m34 = b34 / det;
                this->m41 = b41 / det; this->m42 = b42 / det; this->m43 = b43 / det; this->m44 = b44 / det;
                return *this;
            }

            Matrix4x4& transpose()
            {
                float m11 = this->m11, m12 = this->m21, m13 = this->m31, m14 = this->m41;
                float m21 = this->m12, m22 = this->m22, m23 = this->m32, m24 = this->m42;
                float m31 = this->m13, m32 = this->m23, m33 = this->m33, m34 = this->m43;
                float m41 = this->m14, m42 = this->m24, m43 = this->m34, m44 = this->m44;

                this->m11 = m11; this->m12 = m12; this->m13 = m13; this->m14 = m14;
                this->m21 = m21; this->m22 = m22; this->m23 = m23; this->m24 = m24;
                this->m31 = m31; this->m32 = m32; this->m33 = m33; this->m34 = m34;
                this->m41 = m41; this->m42 = m42; this->m43 = m43; this->m44 = m44;

                return *this;
            }

            Matrix4x4& viewport(float width, float height)
            {
                this->identity();
                this->translate(0.5f * width, 0.5f * height, 0);
                this->scale(0.5f * width, -0.5f * height, 1);
                return *this;
            }

            Matrix4x4& perspective(float fovY, float aspect, float zn, float zf)
            {
                float h = tan(fovY / 2);
                float w = h * aspect;
                this->m11 = 1 / w; this->m12 = 0; this->m13 = 0; this->m14 = 0;
                this->m21 = 0; this->m22 = 1 / h; this->m23 = 0; this->m24 = 0;
                this->m31 = 0; this->m32 = 0; this->m33 = zf / (zf - zn); this->m34 = 1;
                this->m41 = 0; this->m42 = 0; this->m43 = -zn * zf / (zf - zn); this->m44 = 0;
                return *this;
            }

            Matrix4x4& orthogonal(float w, float h, float zn, float zf)
            {
                this->m11 = 2 / w; this->m12 = 0; this->m13 = 0; this->m14 = 0;
                this->m21 = 0; this->m22 = 2 / h; this->m23 = 0; this->m24 = 0;
                this->m31 = 0; this->m32 = 0; this->m33 = 1 / (zf - zn); this->m34 = 0;
                this->m41 = 0; this->m42 = 0; this->m43 = zn / (zn - zf); this->m44 = 1;
                return *this;
            }

            Matrix4x4& lookAt(const Vector3& from, const Vector3& at, const Vector3& up)
            {
                Vector3 zaxis = subtract(at, from);
                Vector3 xaxis = outer(up, zaxis);
                Vector3 yaxis = outer(zaxis, xaxis);
                zaxis.normalize();
                xaxis.normalize();
                yaxis.normalize();
                this->m11 = xaxis.x; this->m12 = xaxis.y; this->m13 = xaxis.z; this->m14 = 0;
                this->m21 = yaxis.x; this->m22 = yaxis.y; this->m23 = yaxis.z; this->m24 = 0;
                this->m31 = zaxis.x; this->m32 = zaxis.y; this->m33 = zaxis.z; this->m34 = 0;
                this->m41 = from.x; this->m42 = from.y; this->m43 = from.z; this->m44 = 1;
                return *this;
            }

            Matrix4x4& lookAt(const Vector3& from, const Vector3& at)
            {
                this->lookAt(from, at, Vector3(0, 1, 0));
                return *this;
            }

            Matrix4x4& translate(float x, float y)
            {
                this->m41 += x * this->m11 + y * this->m21;
                this->m42 += x * this->m12 + y * this->m22;
                this->m43 += x * this->m13 + y * this->m23;
                return *this;
            }

            Matrix4x4& translate(float x, float y, float z)
            {
                this->m41 += x * this->m11 + y * this->m21 + z * this->m31;
                this->m42 += x * this->m12 + y * this->m22 + z * this->m32;
                this->m43 += x * this->m13 + y * this->m23 + z * this->m33;
                return *this;
            }

            Matrix4x4& translate(const Vector3& v)
            {
                this->translate(v.x, v.y, v.z);
                return *this;
            }

            Matrix4x4& scale(float sx, float sy, float sz)
            {
                this->m11 *= sx; this->m12 *= sx; this->m13 *= sx;
                this->m21 *= sy; this->m22 *= sy; this->m23 *= sy;
                this->m31 *= sz; this->m32 *= sz; this->m33 *= sz;
                return *this;
            }

            Matrix4x4& scale(float s)
            {
                this->m11 *= s; this->m12 *= s; this->m13 *= s;
                this->m21 *= s; this->m22 *= s; this->m23 *= s;
                this->m31 *= s; this->m32 *= s; this->m33 *= s;
                return *this;
            }

            Matrix4x4& rotateX(float r)
            {
                float cos—¶ = cos(r);
                float sin—¶ = sin(r);
                float m21 = this->m21 * cos—¶ + this->m31 * sin—¶;
                float m22 = this->m22 * cos—¶ + this->m32 * sin—¶;
                float m23 = this->m23 * cos—¶ + this->m33 * sin—¶;
                float m31 = -this->m21 * sin—¶ + this->m31 * cos—¶;
                float m32 = -this->m22 * sin—¶ + this->m32 * cos—¶;
                float m33 = -this->m23 * sin—¶ + this->m33 * cos—¶;
                this->m21 = m21; this->m22 = m22; this->m23 = m23;
                this->m31 = m31; this->m32 = m32; this->m33 = m33;
                return *this;
            }

            Matrix4x4& rotateY(float r)
            {
                float cos—¶ = cos(r);
                float sin—¶ = sin(r);
                float m11 = this->m11 * cos—¶ - this->m31 * sin—¶;
                float m12 = this->m12 * cos—¶ - this->m32 * sin—¶;
                float m13 = this->m13 * cos—¶ - this->m33 * sin—¶;
                float m31 = this->m11 * sin—¶ + this->m31 * cos—¶;
                float m32 = this->m12 * sin—¶ + this->m32 * cos—¶;
                float m33 = this->m13 * sin—¶ + this->m33 * cos—¶;
                this->m11 = m11; this->m12 = m12; this->m13 = m13;
                this->m31 = m31; this->m32 = m32; this->m33 = m33;
                return *this;
            }

            Matrix4x4& rotateZ(float r)
            {
                float cos—¶ = cos(r);
                float sin—¶ = sin(r);
                float m11 = this->m11 * cos—¶ + this->m21 * sin—¶;
                float m12 = this->m12 * cos—¶ + this->m22 * sin—¶;
                float m13 = this->m13 * cos—¶ + this->m23 * sin—¶;
                float m21 = -this->m11 * sin—¶ + this->m21 * cos—¶;
                float m22 = -this->m12 * sin—¶ + this->m22 * cos—¶;
                float m23 = -this->m13 * sin—¶ + this->m23 * cos—¶;
                this->m11 = m11; this->m12 = m12; this->m13 = m13;
                this->m21 = m21; this->m22 = m22; this->m23 = m23;
                return *this;
            }

            Matrix4x4& transform(const Matrix4x4& m)
            {
                float _m11 = m.m11 * m11 + m.m12 * m21 + m.m13 * m31 + m.m14 * m41;
                float _m12 = m.m11 * m12 + m.m12 * m22 + m.m13 * m32 + m.m14 * m42;
                float _m13 = m.m11 * m13 + m.m12 * m23 + m.m13 * m33 + m.m14 * m43;
                float _m14 = m.m11 * m14 + m.m12 * m24 + m.m13 * m33 + m.m14 * m44;

                float _m21 = m.m21 * m11 + m.m22 * m21 + m.m23 * m31 + m.m24 * m41;
                float _m22 = m.m21 * m12 + m.m22 * m22 + m.m23 * m32 + m.m24 * m42;
                float _m23 = m.m21 * m13 + m.m22 * m23 + m.m23 * m33 + m.m24 * m43;
                float _m24 = m.m21 * m14 + m.m22 * m24 + m.m23 * m34 + m.m24 * m44;

                float _m31 = m.m31 * m11 + m.m32 * m21 + m.m33 * m31 + m.m34 * m41;
                float _m32 = m.m31 * m12 + m.m32 * m22 + m.m33 * m32 + m.m34 * m42;
                float _m33 = m.m31 * m13 + m.m32 * m23 + m.m33 * m33 + m.m34 * m43;
                float _m34 = m.m31 * m14 + m.m32 * m24 + m.m33 * m34 + m.m34 * m44;

                float _m41 = m.m41 * m11 + m.m42 * m21 + m.m43 * m31 + m.m44 * m41;
                float _m42 = m.m41 * m12 + m.m42 * m22 + m.m43 * m32 + m.m44 * m42;
                float _m43 = m.m41 * m13 + m.m42 * m23 + m.m43 * m33 + m.m44 * m43;
                float _m44 = m.m41 * m14 + m.m42 * m24 + m.m43 * m34 + m.m44 * m44;

                m11 = _m11; m12 = _m12; m13 = _m13; m14 = _m14;
                m21 = _m21; m22 = _m22; m23 = _m23; m24 = _m24;
                m31 = _m31; m32 = _m32; m33 = _m33; m34 = _m34;
                m41 = _m41; m42 = _m42; m43 = _m43; m44 = _m44;

                return *this;
            }

            float get_determinant() const
            {
                return m11 * m22 * m33 * m44 + m11 * m23 * m34 * m42 + m11 * m24 * m32 * m43
                    + m12 * m21 * m34 * m43 + m12 * m23 * m31 * m44 + m12 * m24 * m33 * m41
                    + m13 * m21 * m32 * m44 + m13 * m22 * m34 * m41 + m13 * m24 * m31 * m42
                    + m14 * m21 * m33 * m42 + m14 * m22 * m31 * m43 + m14 * m23 * m32 * m41
                    - m11 * m22 * m34 * m43 - m11 * m23 * m32 * m44 - m11 * m24 * m33 * m42
                    - m12 * m21 * m33 * m44 - m12 * m23 * m34 * m41 - m12 * m24 * m31 * m43
                    - m13 * m21 * m34 * m42 - m13 * m22 * m31 * m44 - m13 * m24 * m32 * m41
                    - m14 * m21 * m32 * m43 - m14 * m22 * m33 * m41 - m14 * m23 * m31 * m42;
            }

            Matrix4x4 get_inverse() const
            {
                Matrix4x4 ret = *this;
                ret.invert();
                return ret;
            }

            Matrix3x3 get_matrix3x3() const { return Matrix3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33); }

            void set_matrix3x3(Matrix3x3 m) {
                m11 = m.m11; m12 = m.m12; m13 = m.m13;
                m21 = m.m21; m22 = m.m22; m23 = m.m23;
                m31 = m.m31; m32 = m.m32; m33 = m.m33;
            }

            Matrix4x3 get_matrix4x3() const { return Matrix4x3(m11, m12, m13, m21, m22, m23, m31, m32, m33, m41, m42, m43); }

            void set_matrix4x3(Matrix4x3 m)
            {
                m11 = m.m11; m12 = m.m12; m13 = m.m13;
                m21 = m.m21; m22 = m.m22; m23 = m.m23;
                m31 = m.m31; m32 = m.m32; m33 = m.m33;
                m41 = m.m41; m42 = m.m42; m43 = m.m43;
            }

            __declspec(property(get = get_determinant)) float determinant;

            __declspec(property(get = get_inverse)) Matrix4x4 inverse;

            __declspec(property(get = get_matrix3x3, put = set_matrix3x3)) Matrix3x3 matrix3x3;

            __declspec(property(get = get_matrix4x3, put = set_matrix4x3)) Matrix4x3 matrix4x3;

            float m11, m12, m13, m14;
            float m21, m22, m23, m24;
            float m31, m32, m33, m34;
            float m41, m42, m43, m44;

        public:

            static Matrix4x4 Identity()
            {
                return Matrix4x4();
            }

            template <typename ...Args>
            static Matrix4x4 Translate(const Args& ...args)
            {
                return Matrix4x4().translate(args...);
            }

            template <typename ...Args>
            static Matrix4x4 Scale(const Args&...args)
            {
                return Matrix4x4().scale(args...);
            }

            static Matrix4x4 RotateX(float r)
            {
                return Matrix4x4().rotateX(r);
            }

            static Matrix4x4 RotateY(float r)
            {
                return Matrix4x4().rotateY(r);
            }

            static Matrix4x4 RotateZ(float r)
            {
                return Matrix4x4().rotateZ(r);
            }

            static Matrix4x4 Parse(const string& str);

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
