#include "Matrix3x3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        System::String^ Matrix3x3::ToString()
        {
            return System::String::Format(
                "{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}",
                M11, M12, M13, M21, M22, M23, M31, M32, M33);
        }

        Matrix3x3 Matrix3x3::Parse(System::String^ str)
        {
            array<System::String^>^ params = str->Split(',');
            float m11 = System::Single::Parse(params[0]->Trim());
            float m12 = System::Single::Parse(params[1]->Trim());
            float m13 = System::Single::Parse(params[2]->Trim());
            float m21 = System::Single::Parse(params[3]->Trim());
            float m22 = System::Single::Parse(params[4]->Trim());
            float m23 = System::Single::Parse(params[5]->Trim());
            float m31 = System::Single::Parse(params[6]->Trim());
            float m32 = System::Single::Parse(params[7]->Trim());
            float m33 = System::Single::Parse(params[8]->Trim());
            return Matrix3x3(m11, m12, m13, m21, m22, m23, m31, m32, m33);
        }
    }
}
