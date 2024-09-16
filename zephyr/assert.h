#pragma once

#undef assert

#ifdef _DEBUG
#define _ENABLE_ASSERT
#endif

#ifdef _ENABLE_ASSERT

namespace zephyr
{
    void assert(bool expression);

    void assert(bool expression, const char* message);
}

#else

namespace zephyr
{
    inline void assert(bool) {}
    inline void assert(bool, const char*) {}
}

#endif
