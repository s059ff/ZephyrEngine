#pragma once

#include "zephyr\property.h"
#include "zephyr\string.h"

#include "Vector2.h"

namespace zephyr
{
    namespace linalg
    {
        struct Vector3
        {
            Vector3()
                : x(0), y(0), z(0)
            {
            }

            Vector3(float x, float y, float z)
                : x(x), y(y), z(z)
            {
            }

            Vector3& normalize()
            {
                float oneOverMag = 1 / this->magnitude;
                this->x *= oneOverMag;
                this->y *= oneOverMag;
                this->z *= oneOverMag;
                return *this;
            }

            READONLY_PROPERTY(float, magnitude, { return sqrt(x*x + y*y + z*z); });

            READONLY_PROPERTY(float, squared_magnitude, { return x*x + y*y + z*z; });

            Vector3& operator +=(const Vector3& v)
            {
                x += v.x;
                y += v.y;
                z += v.z;
                return *this;
            }

            Vector3& operator -=(const Vector3& v)
            {
                x -= v.x;
                y -= v.y;
                z -= v.z;
                return *this;
            }

            Vector3 operator -()
            {
                return Vector3(-x, -y, -z);
            }

            float x, y, z;

            READONLY_PROPERTY(Vector2, xy, { return Vector2(x, y); });

            READONLY_PROPERTY(Vector2, xz, { return Vector2(x, z); });

            READONLY_PROPERTY(Vector2, yz, { return Vector2(y, z); });

            static Vector3 Parse(const string& str);

            static const Vector3 Zero;
        };
    }
}
