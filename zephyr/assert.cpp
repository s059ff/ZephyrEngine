#include <stdexcept>

#include "assert.h"

#ifdef _ENABLE_ASSERT

namespace zephyr
{
    void assert(bool expression)
    {
        if (!expression)
            throw std::exception();
    }

    void assert(bool expression, const char* message)
    {
        if (!expression)
            throw std::exception(message);
    }
}

#endif