#pragma once

#include "common.h"
#include "assert.h"
#include "AssertException.h"
#include "RuntimeException.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Threading;

namespace ZephyrSharp
{
    public ref class ResourceManager
    {
    public:

        //delegate Object^ ResourceLoaderDelegate(String^ name);
        using ResourceLoaderDelegate = Func<String^, Object^>;

    private:

        ref class Resource
        {
        public:

            void LoadResource()
            {
                RawResource = gcnew WeakReference(Loader(Name));
                LoadThread = nullptr;
            }

            void LoadResourceInParallel()
            {
                LoadThread = gcnew Thread(gcnew ThreadStart(this, &Resource::LoadResource));
                LoadThread->Start();
            }

            String^ Name = String::Empty;
            ResourceLoaderDelegate^ Loader = nullptr;
            WeakReference^ RawResource = nullptr;
            Thread^ LoadThread = nullptr;
        };

    public:

        void Register(String^ name, ResourceLoaderDelegate^ loader)
        {
            auto res = gcnew Resource();
            res->Name = name;
            res->Loader = loader;
            res->RawResource = nullptr;
            Resources[name] = res;
        }

        bool IsRegistered(String^ name)
        {
            return Resources->ContainsKey(name);
        }

        Object^ Load(String^ name)
        {
            runtime_assert(IsRegistered(name), "Not registerd item: " + name + "!");

            auto res = Resources[name];

            if (res->RawResource == nullptr || !res->RawResource->IsAlive)
            {
                res->LoadResource();
            }
            return res->RawResource->Target;
        }

        Object^ LoadInParallel(String^ name)
        {
            runtime_assert(IsRegistered(name), "Not registerd item: " + name + "!");

            auto res = Resources[name];

            if (res->RawResource == nullptr || !res->RawResource->IsAlive)
            {
                if (res->LoadThread == nullptr)
                {
                    res->LoadResourceInParallel();
                }
                return nullptr;
            }
            return res->RawResource->Target;
        }

        void CleanUp()
        {
            for each (auto res in Resources->Values)
            {
                if (res->RawResource->IsAlive)
                {
                    delete res->RawResource->Target;
                    res->RawResource = nullptr;
                    delete res;
                }
            }
            Resources->Clear();
        }

    private:

        Dictionary<String^, Resource^>^ Resources = gcnew Dictionary<String^, Resource^>();
    };
}
