#pragma once

#include "common.h"

namespace ZephyrSharp
{
    /// <summary>
    /// ランタイムエラーが発生したときに送出されます。
    /// </summary>
    public ref class RuntimeException : public System::Exception
    {
        using base = System::Exception;

    public:

        RuntimeException() : base() {}

        RuntimeException(String^ message) : base(message) {}

        RuntimeException(const char* message) : base(to_string(message)) {}

        RuntimeException(const wchar_t* message) : base(to_string(message)) {}

        RuntimeException(const string& message) : base(to_string(message)) {}
    };
}
