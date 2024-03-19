#pragma once

#include "zephyr\property.h"
#include "zephyr\string.h"
#include "zephyr\math.h"

namespace zephyr
{
    namespace linalg
    {
        struct Vector2
        {
            Vector2() : x(0), y(0) {}

            Vector2(float x, float y) : x(x), y(y) {}

            Vector2& normalize()
            {
                float oneOverMag = 1 / this->magnitude;
                this->x *= oneOverMag;
                this->y *= oneOverMag;
                return *this;
            }

            READONLY_PROPERTY(float, magnitude, { return sqrt(x*x + y*y); });

            READONLY_PROPERTY(float, squared_magnitude, { return x*x + y*y; });

            Vector2& operator +=(const Vector2& v)
            {
                x += v.x;
                y += v.y;
                return *this;
            }

            Vector2& operator -=(const Vector2& v)
            {
                x -= v.x;
                y -= v.y;
                return *this;
            }

            float x, y;

            static Vector2 Parse(const string& str);

            static const Vector2 Zero;
        };
    }
}
