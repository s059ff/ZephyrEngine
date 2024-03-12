#include "Matrix3x3.h"
#include "Quaternion.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        Quaternion::Quaternion(Matrix3x3 matrix)
        {
            auto& _matrix = reinterpret_cast<const zephyr::linalg::Matrix3x3&>(matrix);
            zephyr::linalg::Quaternion _q(_matrix);
            reinterpret_cast<zephyr::linalg::Quaternion&>(*this) = _q;
        }
    }
}
