#pragma once

#include <stdexcept>

#include "print.h"

namespace zephyr
{
    void test(const char* name, bool succeeded);

    template <typename Value1, typename Value2>
    inline void test(const char* name, const Value1& value1, const Value2& value2)
    {
        bool succeeded = (value1 == value2);
        test(name, succeeded);
        if (!succeeded)
            println(std::cout, "('{0}' /= '{1}')", value1, value2);
    }
}
