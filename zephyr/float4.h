#pragma once

namespace zephyr
{
    struct float4
    {
        union
        {
            struct
            {
                float x, y, z, w;
            };
            float a[4];
        };
    };
}
