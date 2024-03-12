#include "Quaternion.h"
#include "Matrix3x3.h"

namespace zephyr
{
    namespace linalg
    {
        Matrix3x3::Matrix3x3(const Quaternion& q)
        {
            float w = q.w;
            float x = q.x;
            float y = q.y;
            float z = q.z;
            this->m11 = 1 - 2 * y * y - 2 * z * z;
            this->m12 = 2 * x * y + 2 * w * z;
            this->m13 = 2 * x * z - 2 * w * y;
            this->m21 = 2 * x * y - 2 * w * z;
            this->m22 = 1 - 2 * x * x - 2 * z * z;
            this->m23 = 2 * y * z + 2 * w * x;
            this->m31 = 2 * x * z + 2 * w * y;
            this->m32 = 2 * y * z - 2 * w * x;
            this->m33 = 1 - 2 * x * x - 2 * y * y;
        }

        Matrix3x3 Matrix3x3::Parse(const string& str)
        {
            Matrix3x3 m;
            sscanf(str.c_str(), "%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,",
                &m.m11, 
                &m.m12,
                &m.m13,
                &m.m21, 
                &m.m22,
                &m.m23,
                &m.m31, 
                &m.m32,
                &m.m33);
            return m;
        }
    }
}
