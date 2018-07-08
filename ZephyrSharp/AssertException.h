#pragma once

#include "common.h"

namespace ZephyrSharp
{
    /// <summary>
    /// �A�T�[�V�����Ɏ��s�����Ƃ����o����܂��B
    /// </summary>
    public ref class AssertException : public System::Exception
    {
        using base = System::Exception;

    public:

        AssertException() : base() {}

        AssertException(String^ message) : base(message) {}

        AssertException(const char* message) : base(to_string(message)) {}
        
        AssertException(const wchar_t* message) : base(to_string(message)) {}

        AssertException(const string& message) : base(to_string(message)) {}
    };
}
