#pragma once

#include <iostream>

#include "string.h"
#include "format.h"
#include "stream.h"

namespace zephyr
{
    template <
        typename Arg0 = int,
        typename Arg1 = int,
        typename Arg2 = int,
        typename Arg3 = int,
        typename Arg4 = int,
        typename Arg5 = int,
        typename Arg6 = int,
        typename Arg7 = int>
        void print(
            ostream& stream,
            const std::string& _format,
            const Arg0& arg0 = 0,
            const Arg1& arg1 = 0,
            const Arg2& arg2 = 0,
            const Arg3& arg3 = 0,
            const Arg4& arg4 = 0,
            const Arg5& arg5 = 0,
            const Arg6& arg6 = 0,
            const Arg7& arg7 = 0)
    {
        stream << format(_format, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    template <
        typename Arg0 = int,
        typename Arg1 = int,
        typename Arg2 = int,
        typename Arg3 = int,
        typename Arg4 = int,
        typename Arg5 = int,
        typename Arg6 = int,
        typename Arg7 = int>
        void print(
            const std::string& _format,
            const Arg0& arg0 = 0,
            const Arg1& arg1 = 0,
            const Arg2& arg2 = 0,
            const Arg3& arg3 = 0,
            const Arg4& arg4 = 0,
            const Arg5& arg5 = 0,
            const Arg6& arg6 = 0,
            const Arg7& arg7 = 0)
    {
        auto& stream = std::cout;
        stream << format(_format, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    }

    template <
        typename Arg0 = int,
        typename Arg1 = int,
        typename Arg2 = int,
        typename Arg3 = int,
        typename Arg4 = int,
        typename Arg5 = int,
        typename Arg6 = int,
        typename Arg7 = int>
        void println(
            ostream& stream,
            const std::string& _format,
            const Arg0& arg0 = 0,
            const Arg1& arg1 = 0,
            const Arg2& arg2 = 0,
            const Arg3& arg3 = 0,
            const Arg4& arg4 = 0,
            const Arg5& arg5 = 0,
            const Arg6& arg6 = 0,
            const Arg7& arg7 = 0)
    {
        stream << format(_format, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) << std::endl;
    }

    template <
        typename Arg0 = int,
        typename Arg1 = int,
        typename Arg2 = int,
        typename Arg3 = int,
        typename Arg4 = int,
        typename Arg5 = int,
        typename Arg6 = int,
        typename Arg7 = int>
        void println(
            const std::string& _format,
            const Arg0& arg0 = 0,
            const Arg1& arg1 = 0,
            const Arg2& arg2 = 0,
            const Arg3& arg3 = 0,
            const Arg4& arg4 = 0,
            const Arg5& arg5 = 0,
            const Arg6& arg6 = 0,
            const Arg7& arg7 = 0)
    {
        auto& stream = std::cout;
        stream << format(_format, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7) << std::endl;
    }

    inline void println(ostream& stream = std::cout)
    {
        stream << std::endl;
    }
}
