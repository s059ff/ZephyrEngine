#include "Matrix4x4.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        System::String^ Matrix4x4::ToString()
        {
            return System::String::Format(
                "{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}, {10}, {11}, {12}, {13}, {14}, {15}",
                M11, M12, M13, M14, M21, M22, M23, M24, M31, M32, M33, M34, M41, M42, M43, M44);
        }

        Matrix4x4 Matrix4x4::Parse(System::String^ str)
        {
            array<System::String^>^ params = str->Split(',');
            float m11 = System::Single::Parse(params[0]->Trim());
            float m12 = System::Single::Parse(params[1]->Trim());
            float m13 = System::Single::Parse(params[2]->Trim());
            float m14 = System::Single::Parse(params[3]->Trim());
            float m21 = System::Single::Parse(params[4]->Trim());
            float m22 = System::Single::Parse(params[5]->Trim());
            float m23 = System::Single::Parse(params[6]->Trim());
            float m24 = System::Single::Parse(params[7]->Trim());
            float m31 = System::Single::Parse(params[8]->Trim());
            float m32 = System::Single::Parse(params[9]->Trim());
            float m33 = System::Single::Parse(params[10]->Trim());
            float m34 = System::Single::Parse(params[11]->Trim());
            float m41 = System::Single::Parse(params[12]->Trim());
            float m42 = System::Single::Parse(params[13]->Trim());
            float m43 = System::Single::Parse(params[14]->Trim());
            float m44 = System::Single::Parse(params[15]->Trim());
            return Matrix4x4(m11, m12, m13, m14, m21, m22, m23, m24, m31, m32, m33, m34, m41, m42, m43, m44);
        }
    }
}
