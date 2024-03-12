#pragma once

#include "common.h"

namespace ZephyrSharp
{
    generic <typename T> where T : value class
        public ref class ValueWrapper
    {
    public:

        static operator T(ValueWrapper<T> w)
        {
            return w.Value;
        }

        T operator =(T x)
        {
            return _t = x;
        }

        ValueWrapper() {}

        ValueWrapper(T t)
        {
            _t = t;
        }

        property T Value
        {
            T get() { return _t; }
            void set(T value) { _t = value; }
        }

        String^ ToString() override
        {
            return _t->ToString();
        }

    private:

        T _t;
    };
}
