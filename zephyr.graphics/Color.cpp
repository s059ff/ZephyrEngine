#include "Color.h"

namespace zephyr
{
    namespace graphics
    {
        Color Color::Parse(const string& str)
        {
            Color v;
            sscanf("%f ,%f ,%f ,%f ,", str.c_str(), &v.r, &v.g, &v.b, &v.a);
            return v;
        }
    }
}
