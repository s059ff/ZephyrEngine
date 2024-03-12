#pragma once

namespace ZephyrSharp
{
    template <typename _Native>
    public ref class INativeSingletonWrapper
    {
    public:

        typedef _Native Type;

        void Release()
        {
            m_native->Release();
        }

        ~INativeSingletonWrapper()
        {
            this->!INativeSingletonWrapper();
        }

        !INativeSingletonWrapper()
        {
            m_native->Release();
            const_cast<_Native*&>(m_native) = nullptr;
        }

        property void* NativePtr { void* get() { return m_native; } }

    internal:

        property _Native* Native { _Native* get() { return m_native; } }

        property _Native& NativeRef { _Native& get() { return *m_native; } }

    private:

        _Native* const m_native
            = reinterpret_cast<_Native*>(&reinterpret_cast<int&>(_Native::Instance));
    };
}
