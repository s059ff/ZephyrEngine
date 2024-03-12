#pragma once

#undef max
#undef min

#include <cmath>

namespace zephyr
{
    template <typename T = float>
    constexpr T PI = static_cast<T>(3.14159265359);

    template <typename T = float>
    constexpr T PI2 = static_cast<T>(3.14159265359 * 2);

    template <typename T = float>
    constexpr T PIOver2 = static_cast<T>(3.14159265359 / 2);

    template <typename T = float>
    constexpr T PIOver4 = static_cast<T>(3.14159265359 / 4);

    template <typename T = float>
    constexpr T Napier = static_cast<T>(2.71828182846);

    template <typename T> T square(T x) { return x * x; }
    template <typename T> T max(T a, T b) { return a > b ? a : b; }
    template <typename T> T min(T a, T b) { return a < b ? a : b; }

    template <typename T> T deg2rad(T deg) { return deg / static_cast<T>(180) * PI<T>; }
    template <typename T> T rad2deg(T rad) { return rad / PI<T> * static_cast<T>(180); }

    template <typename T> T clamp(T x, T min, T max) { return x < min ? min : x > max ? max : x; }

    template <typename T> bool is_inner(T value, T min, T max) { return value >= min && value <= max; }
    template <typename T> bool is_outer(T value, T min, T max) { return value < min || value > max; }

#if 0
    template <typename T> T map(T x, T x0, T x1, T y0, T y1)
    {
        T a = (y1 - y0) / (x1 - x0);
        T y = a * (x - x0) + y0;
        return y;
    }

    template <typename T> T close(T value, T desired_value, T delta)
    {
        if (abs(value - desired_value) < delta)
            return desired_value;
        else
            return value + ((desired_value > value) ? delta : -delta);
    }
#endif
}
