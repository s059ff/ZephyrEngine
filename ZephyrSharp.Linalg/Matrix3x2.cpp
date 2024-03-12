#include "Matrix3x2.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        System::String^ Matrix3x2::ToString()
        {
            return System::String::Format("{0}, {1}, {2}, {3}, {4}, {5}", M11, M12, M21, M22, M31, M32);
        }

        Matrix3x2 Matrix3x2::Parse(System::String^ str)
        {
            array<System::String^>^ params = str->Split(',');
            float m11 = System::Single::Parse(params[0]->Trim());
            float m12 = System::Single::Parse(params[1]->Trim());
            float m21 = System::Single::Parse(params[2]->Trim());
            float m22 = System::Single::Parse(params[3]->Trim());
            float m31 = System::Single::Parse(params[4]->Trim());
            float m32 = System::Single::Parse(params[5]->Trim());
            return Matrix3x2(m11, m12, m21, m22, m31, m32);
        }
    }
}
