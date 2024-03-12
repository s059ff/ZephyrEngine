#pragma once

#include <string>

using std::string;
using std::wstring;

using System::String;
using System::Object;

namespace ZephyrSharp
{
    inline string to_string(String^ s)
    {
        using namespace System;
        using namespace System::Runtime::InteropServices;
        IntPtr mptr = Marshal::StringToHGlobalAnsi(s);
        string buffer = static_cast<const char*>(mptr.ToPointer());
        Marshal::FreeHGlobal(mptr);
        return buffer;
    }

    inline wstring to_wstring(String^ s)
    {
        using namespace System;
        using namespace System::Runtime::InteropServices;
        IntPtr mptr = Marshal::StringToHGlobalUni(s);
        wstring buffer = static_cast<const wchar_t*>(mptr.ToPointer());
        Marshal::FreeHGlobal(mptr);
        return buffer;
    }

    inline String^ to_string(const string& s)
    {
        return gcnew String(s.c_str());
    }

    inline String^ to_string(const char* s)
    {
        return gcnew String(s);
    }

    inline String^ to_string(const wchar_t* s)
    {
        return gcnew String(s);
    }
}
