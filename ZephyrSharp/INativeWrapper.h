#pragma once

namespace ZephyrSharp
{
    template <typename _Native>
    public ref class INativeWrapper
    {
    public:

        typedef _Native Type;

        template <typename ...Args>
        INativeWrapper(const Args& ...args)
            : m_native(new _Native(args...))
        {
        }

        virtual ~INativeWrapper()
        {
            this->!INativeWrapper();
        }

        !INativeWrapper()
        {
            if (m_native != nullptr)
            {
                delete m_native;
                const_cast<_Native*&>(m_native) = nullptr;
            }
        }

        property void* NativePtr { void* get() { return m_native; } }

    internal:

        property _Native* Native { _Native* get() { return m_native; } }

        property _Native& NativeRef { _Native& get() { return *m_native; } }

    private:

        _Native* const m_native;
    };
}
