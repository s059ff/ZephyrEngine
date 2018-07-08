#include "Vector2.h"

namespace ZephyrSharp
{
    namespace Linalg
    {
        System::String^ Vector2::ToString()
        {
            return System::String::Format("{0}, {1}", this->X, this->Y);
        }

        Vector2 Vector2::Parse(System::String^ str)
        {
            array<System::String^>^ params = { "0", "0" };
            int i = 0;
            for each (auto s in str->Split(','))
            {
                if (s != String::Empty)
                    params[i++] = s->Trim();
            }
            float x = System::Single::Parse(params[0]);
            float y = System::Single::Parse(params[1]);
            return Vector2(x, y);
        }
    }
}

