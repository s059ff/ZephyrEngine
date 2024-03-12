#include "Vector3.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        System::String ^ Vector3::ToString()
        {
            return System::String::Format("{0}, {1}, {2}", this->X, this->Y, this->Z);
        }

        Vector3 Vector3::Parse(System::String^ str)
        {
            array<System::String^>^ params = { "0", "0", "0" };
            int i = 0;
            for each (auto s in str->Split(','))
            {
                if (s != String::Empty)
                    params[i++] = s->Trim();
            }
            float x = System::Single::Parse(params[0]);
            float y = System::Single::Parse(params[1]);
            float z = System::Single::Parse(params[2]);
            return Vector3(x, y, z);
        }
    }
}
