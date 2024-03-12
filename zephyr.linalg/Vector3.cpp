#include "Vector3.h"

namespace zephyr
{
    namespace linalg
    {
        const Vector3 Vector3::Zero = Vector3();

        Vector3 Vector3::Parse(const string& str)
        {
            Vector3 v;
            sscanf(str.c_str(), "%f ,%f ,%f ,", &v.x, &v.y, &v.z);
            return v;
        }
    }
}
