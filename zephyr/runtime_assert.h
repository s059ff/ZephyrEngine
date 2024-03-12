#pragma once

#include <stdexcept>

namespace zephyr
{
    inline void runtime_assert(bool expression)
    {
        if (!expression)
            throw std::runtime_error("runtime error.");
    }

    inline void runtime_assert(bool expression, const char* message)
    {
        if (!expression)
            throw std::runtime_error(message);
    }

    template <typename String>
    inline void runtime_assert(bool expression, const String& message)
    {
        if (!expression)
            throw std::runtime_error(message);
    }
}
