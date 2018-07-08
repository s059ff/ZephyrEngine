#include "Quaternion.h"
#include "Matrix4x4.h"

namespace zephyr
{
    namespace linalg
    {
        Matrix4x4::Matrix4x4(const Quaternion& q)
        {
            float w = q.w;
            float x = q.x;
            float y = q.y;
            float z = q.z;
            this->m11 = 1 - 2 * y * y - 2 * z * z;
            this->m12 = 2 * x * y + 2 * w * z;
            this->m13 = 2 * x * z - 2 * w * y;
            this->m14 = 0;
            this->m21 = 2 * x * y - 2 * w * z;
            this->m22 = 1 - 2 * x * x - 2 * z * z;
            this->m23 = 2 * y * z + 2 * w * x;
            this->m24 = 0;
            this->m31 = 2 * x * z + 2 * w * y;
            this->m32 = 2 * y * z - 2 * w * x;
            this->m33 = 1 - 2 * x * x - 2 * y * y;
            this->m34 = 0;
            this->m41 = this->m42 = this->m43 = 0;
            this->m44 = 1;
        }

        Matrix4x4 Matrix4x4::Parse(const string& str)
        {
            Matrix4x4 m;
            sscanf(str.c_str(), "%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,%f ,",
                &m.m11,
                &m.m12,
                &m.m13,
                &m.m14,
                &m.m21,
                &m.m22,
                &m.m23,
                &m.m24,
                &m.m31,
                &m.m32,
                &m.m33,
                &m.m34,
                &m.m41,
                &m.m42,
                &m.m43,
                &m.m44);
            return m;
        }
    }
}
