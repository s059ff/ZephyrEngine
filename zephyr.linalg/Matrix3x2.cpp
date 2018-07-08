#include "Matrix3x2.h"

namespace zephyr
{
    namespace linalg
    {
        Matrix3x2 Matrix3x2::Parse(const string& str)
        {
            Matrix3x2 m;
            sscanf(str.c_str(), "%f ,%f ,%f ,%f ,%f ,%f ,",
                &m.m11,
                &m.m12,
                &m.m21,
                &m.m22,
                &m.m31,
                &m.m32);
            return m;
        }
    }
}
