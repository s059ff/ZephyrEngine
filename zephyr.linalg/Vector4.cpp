#include "Vector4.h"

namespace zephyr
{
    namespace linalg
    {
        const Vector4 Vector4::Zero = Vector4();

        Vector4 Vector4::Parse(const string& str)
        {
            Vector4 v;
            sscanf(str.c_str(), "%f ,%f ,%f ,%f ,", &v.x, &v.y, &v.z, &v.w);
            return v;
        }
    }
}
