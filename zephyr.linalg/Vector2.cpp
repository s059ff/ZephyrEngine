#include "Vector2.h"

namespace zephyr
{
    namespace linalg
    {
        const Vector2 Vector2::Zero = Vector2();

        Vector2 Vector2::Parse(const string& str)
        {
            Vector2 v;
            sscanf(str.c_str(), "%f ,%f ,", &v.x, &v.y);
            return v;
        }
    }
}
