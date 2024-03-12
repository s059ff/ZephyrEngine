#pragma once

#include <stdexcept>

namespace zephyr
{
    class undefined_exception : public std::runtime_error
    {
    public:

        undefined_exception()
            : std::runtime_error("This function is not supported.") {}

        undefined_exception(const std::string& message)
            : std::runtime_error(message) {}


        undefined_exception(const char* message)
            : std::runtime_error(message) {}
    };
}
