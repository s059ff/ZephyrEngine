#pragma once

using namespace System;

namespace ZephyrSharp
{
    generic <typename A> public ref class Binder
    {
    public:

        Binder(Action<A>^ method, A bindValue) 
            : method(method), bindValue(bindValue)
        {
            this->Func = gcnew Action(this,&Binder<A>::call);
        }

        Action^ Func;

    private:

        void call() { this->method(bindValue); }

        Action<A>^ method;

        A bindValue;
    };
}
