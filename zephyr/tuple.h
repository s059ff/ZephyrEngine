#pragma once

namespace zephyr
{
    template <typename T>
    struct tuple1
    {
        T item1;
    };

    template <typename T1, typename T2>
    struct tuple2
    {
        T1 item1;
        T2 item2;
    };

    template <typename T1, typename T2, typename T3>
    struct tuple3
    {
        T1 item1;
        T2 item2;
        T3 item3;
    };

    template <typename T1, typename T2, typename T3, typename T4>
    struct tuple4
    {
        T1 item1;
        T2 item2;
        T3 item3;
        T4 item4;
    };
}
