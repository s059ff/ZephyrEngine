#pragma once

#include "zephyr\math.h"
#include "zephyr\assert.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x2.h"
#include "Matrix3x3.h"
#include "Matrix4x3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

namespace zephyr
{
    namespace linalg
    {
        inline Vector3 add(const Vector3& a, const Vector3& b)
        {
            return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
        }

        inline Vector3 sub(const Vector3& a, const Vector3& b)
        {
            return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
        }

        inline float inner(const Vector3& a, const Vector3& b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }

        inline Vector3 outer(const Vector3& a, const Vector3& b)
        {
            return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }

        inline Matrix3x3 mul(const Matrix3x3& a, const Matrix3x3& b)
        {
            Matrix3x3 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
            return dest;
        }

        inline Matrix4x3 mul(const Matrix3x3& a, const Matrix4x3& b)
        {
            Matrix4x3 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
            dest.m41 = b.m41;
            dest.m42 = b.m42;
            dest.m43 = b.m43;
            return dest;
        }

        inline Matrix4x4 mul(const Matrix3x3& a, const Matrix4x4& b)
        {
            Matrix4x4 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
            dest.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
            dest.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
            dest.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34;
            dest.m41 = b.m41;
            dest.m42 = b.m42;
            dest.m43 = b.m43;
            dest.m44 = b.m44;
            return dest;
        }

        inline Matrix4x3 mul(const Matrix4x3& a, const Matrix3x3& b)
        {
            Matrix4x3 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
            dest.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31;
            dest.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32;
            dest.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33;
            return dest;
        }

        inline Matrix4x3 mul(const Matrix4x3& a, const Matrix4x3& b)
        {
            Matrix4x3 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
            dest.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + b.m41;
            dest.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + b.m42;
            dest.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + b.m43;
            return dest;
        }

        inline Matrix4x4 mul(const Matrix4x3& a, const Matrix4x4& b)
        {
            Matrix4x4 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
            dest.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
            dest.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
            dest.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34;
            dest.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + b.m41;
            dest.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + b.m42;
            dest.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + b.m43;
            dest.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + b.m44;
            return dest;
        }

        inline Matrix4x4 mul(const Matrix4x4& a, const Matrix3x3& b)
        {
            Matrix4x4 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33;
            dest.m14 = a.m14;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33;
            dest.m24 = a.m24;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33;
            dest.m34 = a.m34;
            dest.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31;
            dest.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32;
            dest.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33;
            dest.m44 = a.m44;
            return dest;
        }

        inline Matrix4x4 mul(const Matrix4x4& a, const Matrix4x3& b)
        {
            Matrix4x4 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
            dest.m14 = a.m14;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
            dest.m24 = a.m24;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
            dest.m34 = a.m34;
            dest.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
            dest.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
            dest.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
            dest.m44 = a.m44;
            return dest;
        }

        inline Matrix4x4 mul(const Matrix4x4& a, const Matrix4x4& b)
        {
            Matrix4x4 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21 + a.m13 * b.m31 + a.m14 * b.m41;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22 + a.m13 * b.m32 + a.m14 * b.m42;
            dest.m13 = a.m11 * b.m13 + a.m12 * b.m23 + a.m13 * b.m33 + a.m14 * b.m43;
            dest.m14 = a.m11 * b.m14 + a.m12 * b.m24 + a.m13 * b.m34 + a.m14 * b.m44;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21 + a.m23 * b.m31 + a.m24 * b.m41;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22 + a.m23 * b.m32 + a.m24 * b.m42;
            dest.m23 = a.m21 * b.m13 + a.m22 * b.m23 + a.m23 * b.m33 + a.m24 * b.m43;
            dest.m24 = a.m21 * b.m14 + a.m22 * b.m24 + a.m23 * b.m34 + a.m24 * b.m44;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + a.m33 * b.m31 + a.m34 * b.m41;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + a.m33 * b.m32 + a.m34 * b.m42;
            dest.m33 = a.m31 * b.m13 + a.m32 * b.m23 + a.m33 * b.m33 + a.m34 * b.m43;
            dest.m34 = a.m31 * b.m14 + a.m32 * b.m24 + a.m33 * b.m34 + a.m34 * b.m44;
            dest.m41 = a.m41 * b.m11 + a.m42 * b.m21 + a.m43 * b.m31 + a.m44 * b.m41;
            dest.m42 = a.m41 * b.m12 + a.m42 * b.m22 + a.m43 * b.m32 + a.m44 * b.m42;
            dest.m43 = a.m41 * b.m13 + a.m42 * b.m23 + a.m43 * b.m33 + a.m44 * b.m43;
            dest.m44 = a.m41 * b.m14 + a.m42 * b.m24 + a.m43 * b.m34 + a.m44 * b.m44;
            return dest;
        }

        inline Vector3 mul(const Vector3& v, const Matrix4x4& m)
        {
            float x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + m.m41;
            float y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + m.m42;
            float z = v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + m.m43;
            return Vector3(x, y, z);
        }

        inline Vector4 mul(const Vector4& v, const Matrix4x4& m)
        {
            float x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + v.w * m.m41;
            float y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + v.w * m.m42;
            float z = v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + v.w * m.m43;
            float w = v.x * m.m14 + v.y * m.m24 + v.z * m.m34 + v.w * m.m44;
            return Vector4(x, y, z, w);
        }

        inline Vector3 mul(const Vector3& v, const Matrix4x3& m)
        {
            Vector3 dest;
            dest.x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + m.m41;
            dest.y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + m.m42;
            dest.z = v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + m.m43;
            return dest;
        }

        inline Vector4 mul(const Vector4& v, const Matrix4x3& m)
        {
            Vector4 dest;
            dest.x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31 + v.w * m.m41;
            dest.y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32 + v.w * m.m42;
            dest.z = v.x * m.m13 + v.y * m.m23 + v.z * m.m33 + v.w * m.m43;
            dest.w = v.w;
            return dest;
        }

        inline Vector3 mul(const Vector3& v, const Matrix3x3& m)
        {
            Vector3 dest;
            dest.x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31;
            dest.y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32;
            dest.z = v.x * m.m13 + v.y * m.m23 + v.z * m.m33;
            return dest;
        }

        inline Vector3 mul(const Vector3& v, float s)
        {
            return Vector3(s * v.x, s * v.y, s * v.z);
        }

        inline Vector3 div(const Vector3& v, float s)
        {
            return Vector3(v.x / s, v.y / s, v.z / s);
        }

        inline Vector3 mul(float s, const Vector3& v)
        {
            return Vector3(s * v.x, s * v.y, s * v.z);
        }

        inline float magnitude(const Vector3& v)
        {
            return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        }

        inline float squared_magnitude(const Vector3& v)
        {
            return v.x * v.x + v.y * v.y + v.z * v.z;
        }

        inline float distance(const Vector3& v1, const Vector3& v2)
        {
            return sub(v1, v2).magnitude;
        }

        inline Vector3& normalize(Vector3& v)
        {
            float squareMag = squared_magnitude(v);
            assert(squareMag > 0);
            float oneOverMag = 1.0f / sqrt(squareMag);
            v.x *= oneOverMag;
            v.y *= oneOverMag;
            v.z *= oneOverMag;
            return v;
        }

        inline float angle(const Vector3& a, const Vector3& b)
        {
            return acos(inner(a, b) / (magnitude(a) * magnitude(b)));
        }

        inline Vector3 project(const Vector3& v, const Vector3& n)
        {
            return mul(n, (inner(v, n) / squared_magnitude(n)));
        }

        inline float determinant(const Matrix3x3& m)
        {
            return m.m11 * m.m22 * m.m33 + m.m12 * m.m23 * m.m31 + m.m13 * m.m21 * m.m32
                - m.m11 * m.m23 * m.m32 - m.m12 * m.m21 * m.m33 - m.m13 * m.m22 * m.m31;
        }

        inline float determinant(const Matrix4x3& m)
        {
            return m.m11 * m.m22 * m.m33 + m.m12 * m.m23 * m.m31 + m.m13 * m.m21 * m.m32
                - m.m11 * m.m23 * m.m32 - m.m12 * m.m21 * m.m33 - m.m13 * m.m22 * m.m31;
        }

        inline float determinant(const Matrix4x4& m)
        {
            return m.m11 * m.m22 * m.m33 * m.m44 + m.m11 * m.m23 * m.m34 * m.m42 + m.m11 * m.m24 * m.m32 * m.m43
                + m.m12 * m.m21 * m.m34 * m.m43 + m.m12 * m.m23 * m.m31 * m.m44 + m.m12 * m.m24 * m.m33 * m.m41
                + m.m13 * m.m21 * m.m32 * m.m44 + m.m13 * m.m22 * m.m34 * m.m41 + m.m13 * m.m24 * m.m31 * m.m42
                + m.m14 * m.m21 * m.m33 * m.m42 + m.m14 * m.m22 * m.m31 * m.m43 + m.m14 * m.m23 * m.m32 * m.m41
                - m.m11 * m.m22 * m.m34 * m.m43 - m.m11 * m.m23 * m.m32 * m.m44 - m.m11 * m.m24 * m.m33 * m.m42
                - m.m12 * m.m21 * m.m33 * m.m44 - m.m12 * m.m23 * m.m34 * m.m41 - m.m12 * m.m24 * m.m31 * m.m43
                - m.m13 * m.m21 * m.m34 * m.m42 - m.m13 * m.m22 * m.m31 * m.m44 - m.m13 * m.m24 * m.m32 * m.m41
                - m.m14 * m.m21 * m.m32 * m.m43 - m.m14 * m.m22 * m.m33 * m.m41 - m.m14 * m.m23 * m.m31 * m.m42;
        }

        inline Matrix4x3 invert(const Matrix3x3& m)
        {
            float det = determinant(m);
            assert(det != 0);
            float b11 = m.m22 * m.m33 - m.m23 * m.m32;
            float b12 = m.m13 * m.m32 - m.m12 * m.m33;
            float b13 = m.m12 * m.m23 - m.m13 * m.m22;
            float b21 = m.m23 * m.m31 - m.m21 * m.m33;
            float b22 = m.m11 * m.m33 - m.m13 * m.m31;
            float b23 = m.m13 * m.m21 - m.m11 * m.m23;
            float b31 = m.m21 * m.m32 - m.m22 * m.m31;
            float b32 = m.m12 * m.m31 - m.m11 * m.m32;
            float b33 = m.m11 * m.m22 - m.m12 * m.m21;
            float _det = 1 / det;
            return Matrix3x3(
                b11 * _det, b12 * _det, b13 * _det,
                b21 * _det, b22 * _det, b23 * _det,
                b31 * _det, b32 * _det, b33 * _det
            );
        }

        inline Matrix4x3 invert(const Matrix4x3& m)
        {
            float det = determinant(m);
            assert(det != 0);
            float b11 = m.m22 * m.m33 - m.m23 * m.m32;
            float b12 = m.m13 * m.m32 - m.m12 * m.m33;
            float b13 = m.m12 * m.m23 - m.m13 * m.m22;
            float b21 = m.m23 * m.m31 - m.m21 * m.m33;
            float b22 = m.m11 * m.m33 - m.m13 * m.m31;
            float b23 = m.m13 * m.m21 - m.m11 * m.m23;
            float b31 = m.m21 * m.m32 - m.m22 * m.m31;
            float b32 = m.m12 * m.m31 - m.m11 * m.m32;
            float b33 = m.m11 * m.m22 - m.m12 * m.m21;
            float b41 = m.m21 * m.m33 * m.m42 + m.m22 * m.m31 * m.m43 + m.m23 * m.m32 * m.m41 - m.m21 * m.m32 * m.m43 - m.m22 * m.m33 * m.m41 - m.m23 * m.m31 * m.m42;
            float b42 = m.m11 * m.m32 * m.m43 + m.m12 * m.m33 * m.m41 + m.m13 * m.m31 * m.m42 - m.m11 * m.m33 * m.m42 - m.m12 * m.m31 * m.m43 - m.m13 * m.m32 * m.m41;
            float b43 = m.m11 * m.m23 * m.m42 + m.m12 * m.m21 * m.m43 + m.m13 * m.m22 * m.m41 - m.m11 * m.m22 * m.m43 - m.m12 * m.m23 * m.m41 - m.m13 * m.m21 * m.m42;
            float _det = 1 / det;
            return Matrix4x3(
                b11 * _det, b12 * _det, b13 * _det,
                b21 * _det, b22 * _det, b23 * _det,
                b31 * _det, b32 * _det, b33 * _det,
                b41 * _det, b42 * _det, b43 * _det
            );
        }

        inline Matrix4x4 invert(const Matrix4x4& m)
        {
            float det = determinant(m);
            assert(det != 0);
            float b11 = m.m22 * m.m33 * m.m44 + m.m23 * m.m34 * m.m42 + m.m24 * m.m32 * m.m43 - m.m22 * m.m34 * m.m43 - m.m23 * m.m32 * m.m44 - m.m24 * m.m33 * m.m42;
            float b12 = m.m12 * m.m34 * m.m43 + m.m13 * m.m32 * m.m44 + m.m14 * m.m33 * m.m42 - m.m12 * m.m33 * m.m44 - m.m13 * m.m34 * m.m42 - m.m14 * m.m32 * m.m43;
            float b13 = m.m12 * m.m23 * m.m44 + m.m13 * m.m24 * m.m42 + m.m14 * m.m22 * m.m43 - m.m12 * m.m24 * m.m43 - m.m13 * m.m22 * m.m44 - m.m14 * m.m23 * m.m42;
            float b14 = m.m12 * m.m24 * m.m33 + m.m13 * m.m22 * m.m34 + m.m14 * m.m23 * m.m32 - m.m12 * m.m23 * m.m34 - m.m13 * m.m24 * m.m32 - m.m14 * m.m22 * m.m33;
            float b21 = m.m21 * m.m34 * m.m43 + m.m23 * m.m31 * m.m44 + m.m24 * m.m33 * m.m41 - m.m21 * m.m33 * m.m44 - m.m23 * m.m34 * m.m41 - m.m24 * m.m31 * m.m43;
            float b22 = m.m11 * m.m33 * m.m44 + m.m13 * m.m34 * m.m41 + m.m14 * m.m31 * m.m43 - m.m11 * m.m34 * m.m43 - m.m13 * m.m31 * m.m44 - m.m14 * m.m33 * m.m41;
            float b23 = m.m11 * m.m24 * m.m43 + m.m13 * m.m21 * m.m44 + m.m14 * m.m23 * m.m41 - m.m11 * m.m23 * m.m44 - m.m13 * m.m24 * m.m41 - m.m14 * m.m21 * m.m43;
            float b24 = m.m11 * m.m23 * m.m34 + m.m13 * m.m24 * m.m31 + m.m14 * m.m21 * m.m33 - m.m11 * m.m24 * m.m33 - m.m13 * m.m21 * m.m34 - m.m14 * m.m23 * m.m31;
            float b31 = m.m21 * m.m32 * m.m44 + m.m22 * m.m34 * m.m41 + m.m24 * m.m31 * m.m42 - m.m21 * m.m34 * m.m42 - m.m22 * m.m31 * m.m44 - m.m24 * m.m32 * m.m41;
            float b32 = m.m11 * m.m34 * m.m42 + m.m12 * m.m31 * m.m44 + m.m14 * m.m32 * m.m41 - m.m11 * m.m32 * m.m44 - m.m12 * m.m34 * m.m41 - m.m14 * m.m31 * m.m42;
            float b33 = m.m11 * m.m22 * m.m44 + m.m12 * m.m24 * m.m41 + m.m14 * m.m21 * m.m42 - m.m11 * m.m24 * m.m42 - m.m12 * m.m21 * m.m44 - m.m14 * m.m22 * m.m41;
            float b34 = m.m11 * m.m24 * m.m32 + m.m12 * m.m21 * m.m34 + m.m14 * m.m22 * m.m31 - m.m11 * m.m22 * m.m34 - m.m12 * m.m24 * m.m31 - m.m14 * m.m21 * m.m32;
            float b41 = m.m21 * m.m33 * m.m42 + m.m22 * m.m31 * m.m43 + m.m23 * m.m32 * m.m41 - m.m21 * m.m32 * m.m43 - m.m22 * m.m33 * m.m41 - m.m23 * m.m31 * m.m42;
            float b42 = m.m11 * m.m32 * m.m43 + m.m12 * m.m33 * m.m41 + m.m13 * m.m31 * m.m42 - m.m11 * m.m33 * m.m42 - m.m12 * m.m31 * m.m43 - m.m13 * m.m32 * m.m41;
            float b43 = m.m11 * m.m23 * m.m42 + m.m12 * m.m21 * m.m43 + m.m13 * m.m22 * m.m41 - m.m11 * m.m22 * m.m43 - m.m12 * m.m23 * m.m41 - m.m13 * m.m21 * m.m42;
            float b44 = m.m11 * m.m22 * m.m33 + m.m12 * m.m23 * m.m31 + m.m13 * m.m21 * m.m32 - m.m11 * m.m23 * m.m32 - m.m12 * m.m21 * m.m33 - m.m13 * m.m22 * m.m31;
            float _det = 1 / det;
            return Matrix4x4(
                b11 * _det, b12 * _det, b13 * _det, b14 * _det,
                b21 * _det, b22 * _det, b23 * _det, b24 * _det,
                b31 * _det, b32 * _det, b33 * _det, b34 * _det,
                b41 * _det, b42 * _det, b43 * _det, b44 * _det);
        }

        inline Vector3 operator +(const Vector3& a, const Vector3& b)
        {
            return add(a, b);
        }

        inline Vector3 operator -(const Vector3& a, const Vector3& b)
        {
            return sub(a, b);
        }

        inline Matrix3x3 operator *(const Matrix3x3& a, const Matrix3x3& b)
        {
            return mul(a, b);
        }

        inline Matrix4x3 operator *(const Matrix3x3& a, const Matrix4x3& b)
        {
            return mul(a, b);
        }

        inline Matrix4x4 operator *(const Matrix3x3& a, const Matrix4x4& b)
        {
            return mul(a, b);
        }

        inline Matrix4x3 operator *(const Matrix4x3& a, const Matrix3x3& b)
        {
            return mul(a, b);
        }

        inline Matrix4x3 operator *(const Matrix4x3& a, const Matrix4x3& b)
        {
            return mul(a, b);
        }

        inline Matrix4x4 operator *(const Matrix4x3& a, const Matrix4x4& b)
        {
            return mul(a, b);
        }

        inline Matrix4x4 operator *(const Matrix4x4& a, const Matrix3x3& b)
        {
            return mul(a, b);
        }

        inline Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x3& b)
        {
            return mul(a, b);
        }

        inline Matrix4x4 operator *(const Matrix4x4& a, const Matrix4x4& b)
        {
            return mul(a, b);
        }

        inline Vector3 operator *(const Vector3& a, const Matrix3x3& b)
        {
            return mul(a, b);
        }

        inline Vector3 operator *(const Vector3& a, const Matrix4x3& b)
        {
            return mul(a, b);
        }

        inline Vector4 operator *(const Vector4& a, const Matrix4x3& b)
        {
            return mul(a, b);
        }

        inline Vector3 operator *(const Vector3& a, const Matrix4x4& b)
        {
            return mul(a, b);
        }

        inline Vector4 operator *(const Vector4& a, const Matrix4x4& b)
        {
            return mul(a, b);
        }

        inline Vector3 operator *(const Vector3& v, float s)
        {
            return mul(v, s);
        }

        inline Vector3 operator *(float s, const Vector3& v)
        {
            return mul(v, s);
        }

        inline Vector3 operator /(const Vector3& v, float s)
        {
            return div(v, s);
        }

        inline Vector3 operator -(const Vector3& v)
        {
            return Vector3(-v.x, -v.y, -v.z);
        }
    }

    namespace linalg
    {
        inline Vector2 add(const Vector2& a, const Vector2& b)
        {
            return Vector2(a.x + b.x, a.y + b.y);
        }

        inline Vector2 sub(const Vector2& a, const Vector2& b)
        {
            return Vector2(a.x - b.x, a.y - b.y);
        }

        inline float inner(const Vector2& a, const Vector2& b)
        {
            return a.x * b.x + a.y * b.y;
        }

        inline float outer(const Vector2& a, const Vector2& b)
        {
            return a.x * b.y - a.y * b.x;
        }

        inline Matrix3x2 mul(const Matrix3x2& a, const Matrix3x2& b)
        {
            Matrix3x2 dest;
            dest.m11 = a.m11 * b.m11 + a.m12 * b.m21;
            dest.m12 = a.m11 * b.m12 + a.m12 * b.m22;
            dest.m21 = a.m21 * b.m11 + a.m22 * b.m21;
            dest.m22 = a.m21 * b.m12 + a.m22 * b.m22;
            dest.m31 = a.m31 * b.m11 + a.m32 * b.m21 + b.m31;
            dest.m32 = a.m31 * b.m12 + a.m32 * b.m22 + b.m32;
            return dest;
        }

        inline Vector2 mul(const Vector2& v, const Matrix3x2& m)
        {
            float x = v.x * m.m11 + v.y * m.m21 + m.m31;
            float y = v.x * m.m12 + v.y * m.m22 + m.m32;
            return Vector2(x, y);
        }

        inline Vector3 mul(const Vector3& v, const Matrix3x2& m)
        {
            float x = v.x * m.m11 + v.y * m.m21 + v.z * m.m31;
            float y = v.x * m.m12 + v.y * m.m22 + v.z * m.m32;
            float z = v.z;

            return Vector3(x, y, z);
        }

        inline Vector2 mul(const Vector2& v, float s)
        {
            return Vector2(v.x * s, v.y * s);
        }

        inline Vector2 mul(float s, const Vector2& v)
        {
            return Vector2(v.x * s, v.y * s);
        }

        inline Vector2 div(const Vector2& v, float s)
        {
            return Vector2(v.x / s, v.y / s);
        }

        inline float magnitude(const Vector2& v)
        {
            return sqrt(v.x * v.x + v.y * v.y);
        }

        inline float squared_magnitude(const Vector2& v)
        {
            return v.x * v.x + v.y * v.y;
        }

        inline float distance(const Vector2& v1, const Vector2& v2)
        {
            return sub(v1, v2).magnitude;
        }

        inline Vector2& normalize(Vector2& v)
        {
            float squareMag = squared_magnitude(v);
            assert(squareMag > 0);
            float oneOverMag = 1.0f / sqrt(squareMag);
            v.x *= oneOverMag;
            v.y *= oneOverMag;
            return v;
        }

        inline float angle(const Vector2& a, const Vector2& b)
        {
            return acos(inner(a, b) / (magnitude(a) * magnitude(b)));
        }

        inline Vector2 project(const Vector2& v, const Vector2& n)
        {
            return mul(n, (inner(v, n) / squared_magnitude(n)));
        }

        inline float determinant(const Matrix3x2& m)
        {
            return m.m11 * m.m22 - m.m21 * m.m12;
        }

        inline Matrix3x2 invert(const Matrix3x2& m)
        {
            float det = determinant(m);
            assert(det != 0);

            float b11 = m.m22;
            float b12 = -m.m12;
            float b21 = -m.m21;
            float b22 = m.m11;

            float b31 = m.m21 * m.m32 - m.m22 * m.m31;
            float b32 = m.m12 * m.m31 - m.m11 * m.m32;

            Matrix3x2 dest;
            dest.m11 = b11 / det;
            dest.m12 = b12 / det;
            dest.m21 = b21 / det;
            dest.m22 = b22 / det;
            dest.m31 = b31 / det;
            dest.m32 = b32 / det;

            return dest;
        }

        inline Vector2 operator +(const Vector2& a, const Vector2& b)
        {
            return add(a, b);
        }

        inline Vector2 operator -(const Vector2& a, const Vector2& b)
        {
            return sub(a, b);
        }

        inline Matrix3x2 operator *(const Matrix3x2& a, const Matrix3x2& b)
        {
            return mul(a, b);
        }

        inline Vector2 operator *(const Vector2& a, const Matrix3x2& b)
        {
            return mul(a, b);
        }

        inline Vector3 operator *(const Vector3& a, const Matrix3x2& b)
        {
            return mul(a, b);
        }

        inline Vector2 operator *(const Vector2& v, float s)
        {
            return mul(v, s);
        }

        inline Vector2 operator *(float s, const Vector2& v)
        {
            return mul(v, s);
        }

        inline Vector2 operator /(const Vector2& v, float s)
        {
            return div(v, s);
        }

        inline Vector2 operator -(const Vector2& v)
        {
            return Vector2(-v.x, -v.y);
        }
    }

    namespace linalg
    {
        inline Quaternion mul(const Quaternion& q1, const Quaternion& q2)
        {
            float w1 = q1.w;
            float w2 = q2.w;
            Vector3 v1 = Vector3(q1.x, q1.y, q1.z);
            Vector3 v2 = Vector3(q2.x, q2.y, q2.z);
            float w = w1 * w2 - inner(v1, v2);
            Vector3 xyz = w1 * v2 + w2 * v1 + outer(v2, v1);
            float x = xyz.x;
            float y = xyz.y;
            float z = xyz.z;

            return Quaternion(x, y, z, w);
        }

        inline Quaternion operator -(const Quaternion& q)
        {
            return Quaternion(-q.x, -q.y, -q.z, q.w);
        }

        inline Quaternion operator *(const Quaternion& q1, const Quaternion& q2)
        {
            return mul(q1, q2);
        }

        inline float inner(const Quaternion& q1, const Quaternion& q2)
        {
            return q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
        }

        inline Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t)
        {
            assert(0 <= t && t <= 1);

            float cosOmega = inner(q0, q1);
            assert(-1.1f < cosOmega && cosOmega < 1.1f);

            float q1w = q1.w;
            float q1x = q1.x;
            float q1y = q1.y;
            float q1z = q1.z;

            if (cosOmega < 0)
            {
                q1w = -q1.w;
                q1x = -q1.x;
                q1y = -q1.y;
                q1z = -q1.z;
                cosOmega = -cosOmega;
            }

            float k0, k1;
            if (cosOmega > 0.9999f)
            {
                k0 = 1 - t;
                k1 = t;
            }
            else
            {
                float sinOmega = sqrt(1 - cosOmega*cosOmega);
                float omega = atan2(sinOmega, cosOmega);
                float oneOverSinOmega = 1 / sinOmega;
                k0 = sin((1 - t) * omega) * oneOverSinOmega;
                k1 = sin(t * omega) * oneOverSinOmega;
            }

            float x = k0 * q0.x + k1 * q1x;
            float y = k0 * q0.y + k1 * q1y;
            float z = k0 * q0.z + k1 * q1z;
            float w = k0 * q0.w + k1 * q1w;
            return Quaternion(x, y, z, w);
        }

        inline Quaternion pow(const Quaternion& q, float t)
        {
            float w = q.w;
            float x = q.x;
            float y = q.y;
            float z = q.z;

            if (abs(w) < .9990f)
            {
                float oldAlpha = acos(w);
                float newAlpha = oldAlpha * t;
                w = cos(newAlpha);

                float k = sin(newAlpha) / sin(oldAlpha);
                x *= k;
                y *= k;
                z *= k;
            }
            return Quaternion(x, y, z, w);
        }
    }
}
