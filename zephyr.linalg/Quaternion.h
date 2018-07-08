#pragma once

#include "zephyr\assert.h"
#include "zephyr\property.h"
#include "zephyr\string.h"

#include "Vector3.h"

namespace zephyr
{
    namespace linalg
    {
        struct Matrix3x3;

        struct Quaternion
        {
            Quaternion() : x(0), y(0), z(0), w(1) {}

            Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

            Quaternion(const Vector3& axis, float theta)
            {
                float ax = axis.x;
                float ay = axis.y;
                float az = axis.z;
                float mag = axis.magnitude;
                assert(mag > 0.99f && mag < 1.01f);

                float alpha = theta * 0.5f;
                float sin = ::sin(alpha);
                w = cos(alpha);
                x = ax * sin;
                y = ay * sin;
                z = az * sin;
            }

            Quaternion(const Vector3& point) : x(point.x), y(point.y), z(point.z), w(0) {}

            explicit Quaternion(const Matrix3x3& matrix);

            Quaternion& identity()
            {
                w = 1;
                x = y = z = 0;

                return *this;
            }

            Quaternion& normalize()
            {
                float mag = sqrt(w * w + x * x + y * y + z * z);
                float oneOverMag = 1.0f / mag;
                w *= oneOverMag;
                x *= oneOverMag;
                y *= oneOverMag;
                z *= oneOverMag;

                return *this;
            }

            READONLY_PROPERTY(Vector3, axis, const
            {
                float alpha = acos(w);
                float sin = ::sin(alpha);
                return Vector3(x / sin, y / sin, z / sin).normalize();
            });

            READONLY_PROPERTY(float, theta, const{ return acos(w) * 2; });

            float x, y, z, w;
        };
    }
}
