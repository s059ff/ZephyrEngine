#include "zephyr\algorithm.h"
#include "zephyr\assert.h"

#include "Matrix3x3.h"
#include "Quaternion.h"

namespace zephyr
{
    namespace linalg
    {
        Quaternion::Quaternion(const Matrix3x3& matrix)
        {
            float m11 = matrix.m11, m12 = matrix.m12, m13 = matrix.m13;
            float m21 = matrix.m21, m22 = matrix.m22, m23 = matrix.m23;
            float m31 = matrix.m31, m32 = matrix.m32, m33 = matrix.m33;

            float x, y, z, w;

            float fourWSquaredMinus1 = m11 + m22 + m33;
            float fourXSquaredMinus1 = m11 - m22 - m33;
            float fourYSquaredMinus1 = m22 - m11 - m33;
            float fourZSquaredMinus1 = m33 - m11 - m22;
            auto four_SquaredMinus1 = { fourWSquaredMinus1, fourXSquaredMinus1, fourYSquaredMinus1, fourZSquaredMinus1 };

            auto biggestIndex = distance(four_SquaredMinus1.begin(), max_element(four_SquaredMinus1.begin(), four_SquaredMinus1.end()));
            float fourBiggestSquaredMinus1 = max(four_SquaredMinus1);

            float biggestValue = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
            float mult = 0.25f / biggestValue;

            switch (biggestIndex)
            {
            case 0:
                w = biggestValue;
                x = (m23 - m32) * mult;
                y = (m31 - m13) * mult;
                z = (m12 - m21) * mult;
                break;

            case 1:
                x = biggestValue;
                w = (m23 - m32) * mult;
                y = (m12 + m21) * mult;
                z = (m31 + m13) * mult;
                break;

            case 2:
                y = biggestValue;
                w = (m31 - m13) * mult;
                x = (m12 + m21) * mult;
                z = (m23 + m32) * mult;
                break;

            case 3:
                z = biggestValue;
                w = (m12 - m21) * mult;
                x = (m31 + m13) * mult;
                y = (m23 + m32) * mult;
                break;
            }

            this->w = w;
            this->x = x;
            this->y = y;
            this->z = z;
        }
    }
}
