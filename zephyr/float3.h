#pragma once

namespace zephyr
{
    struct float3
    {
        union
        {
            struct
            {
                float x, y, z;
            };
            float a[3];
        };
    };
}
