#include "Vector4.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        System::String ^ Vector4::ToString()
        {
            return System::String::Format("{0}, {1}, {2}, {3}", this->X, this->Y, this->Z, this->W);
        }

        Vector4 Vector4::Parse(System::String^ str)
        {
            array<System::String^>^ params = { "0", "0", "0", "0" };
            int i = 0;
            for each (auto s in str->Split(','))
            {
                if (s != String::Empty)
                    params[i++] = s->Trim();
            }
            float x = System::Single::Parse(params[0]);
            float y = System::Single::Parse(params[1]);
            float z = System::Single::Parse(params[2]);
            float w = System::Single::Parse(params[3]);
            return Vector4(x, y, z, w);
        }
    }
}
