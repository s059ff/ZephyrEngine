#pragma once

namespace zephyr
{
    template <typename Head> class type
    {
    public:

        Head value;
    };

    template <typename ...> class composit {};

    template <typename Head, typename ...Body>
    class composit<Head, Body...> : public type<Head>, public composit<Body...>
    {
    };
}
