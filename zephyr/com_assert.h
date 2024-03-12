#pragma once

#include <Windows.h>

#include "runtime_assert.h"

namespace zephyr
{
    inline void com_assert(HRESULT hr)
    {
        runtime_assert(SUCCEEDED(hr));
    }

    inline void com_assert(HRESULT hr, const char* message)
    {
        runtime_assert(SUCCEEDED(hr), message);
    }

    template <typename String>
    inline void com_assert(HRESULT hr, const String& message)
    {
        runtime_assert(SUCCEEDED(hr), message);
    }
}
