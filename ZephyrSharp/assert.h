#if 0

namespace ZephyrSharp
{
    ref class AssertException;
    ref class RuntimeException;

    inline void assert(bool expression)
    {
#ifdef _DEBUG
        if (!expression)
            throw gcnew AssertException();
#endif

    }

    template <typename _MessageType>
    inline void assert(bool expression, const _MessageType& message)
    {
#ifdef _DEBUG
        if (!expression)
            throw gcnew AssertException(message);
#endif
    }

    inline void runtime_assert(bool expression)
    {
        if (!expression)
            throw gcnew RuntimeException();
    }

    template <typename _MessageType>
    inline void runtime_assert(bool expression, const _MessageType& message)
    {
        if (!expression)
            throw gcnew RuntimeException(message);
    }
}

#else

#define assert(exp, ...) if (!(exp)) throw gcnew AssertException(__VA_ARGS__  + __FILE__ + __LINE__);
#define runtime_assert(exp, ...) if (!(exp)) throw gcnew RuntimeException(__VA_ARGS__  + __FILE__ + __LINE__);

#endif
