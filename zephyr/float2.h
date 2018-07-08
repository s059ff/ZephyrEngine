#pragma once

namespace zephyr
{
    struct float2
    {
        union
        {
            struct
            {
                float x, y;
            };
            struct
            {
                float u, v;
            };
            float a[2];
        };
    };
}
