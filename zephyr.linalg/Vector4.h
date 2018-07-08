#pragma once

#include "zephyr\property.h"
#include "zephyr\string.h"

#include "Vector2.h"
#include "Vector3.h"

namespace zephyr
{
    namespace linalg
    {
        struct Vector4
        {
            Vector4()
                : x(0), y(0), z(0), w(0)
            {
            }

            Vector4(float x, float y, float z, float w)
                : x(x), y(y), z(z), w(w)
            {
            }

            Vector4(const Vector3& v, float w)
                : x(v.x), y(v.y), z(v.z), w(w)
            {
            }
            
            float x, y, z, w;

            READONLY_PROPERTY(Vector2, xy, { return Vector2(x, y); });

            READONLY_PROPERTY(Vector2, xz, { return Vector2(x, z); });

            READONLY_PROPERTY(Vector2, yz, { return Vector2(y, z); });

            READONLY_PROPERTY(Vector3, xyz, { return Vector3(x, y, z); });

            static Vector4 Parse(const string& str);

            static const Vector4 Zero;
        };
    }
}
