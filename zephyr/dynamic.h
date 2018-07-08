#pragma once

#include "zephyr\string.h"
#include "zephyr\vector.h"
#include "zephyr\function.h"
#include "zephyr\runtime_assert.h"

namespace zephyr
{
    struct MethodMetadata
    {
        static_string<64> name;
        function<void(void)> method;

        template <typename C, typename R, typename ...Args>
        MethodMetadata(static_string<64> name, R(C::*method)(Args...)) : name(name)
        {
            reinterpret_cast<function<R(Args...)>&>(this->method) = function<R(Args...)>(method);
        }
    };

    struct PropertyMetadata
    {
        static_string<64> name;
        const type_info &type;
        function<void(void)> getter;
        function<void(void)> setter;

        template <typename C, typename T>
        PropertyMetadata(static_string<64> name, T(C::*getter)(), void(C::*setter)(T))
            : name(name), type(typeid(T))
        {
            reinterpret_cast<function<T(void)>&>(this->getter) = getter;
            reinterpret_cast<function<void(T)>&>(this->setter) = setter;
        }

        template <typename C, typename T>
        PropertyMetadata(static_string<64> name, nullptr_t, void(C::*setter)(T))
            : name(name), type(typeid(T))
        {
            reinterpret_cast<function<void(T)>&>(this->setter) = setter;
        }

        template <typename C, typename T>
        PropertyMetadata(static_string<64> name, T(C::*getter)(), nullptr_t)
            : name(name), type(typeid(T))
        {
            reinterpret_cast<function<T(void)>&>(this->getter) = getter;
        }
    };


    struct ClassMetadata
    {
        const type_info &type;
        static_string<64> name;
        size_t offset;
        size_t size;
        vector<ClassMetadata> fields;
        vector<PropertyMetadata> properties;
        vector<MethodMetadata> methods;
        ClassMetadata* owner;

        ClassMetadata(const ClassMetadata& obj) :
            type(obj.type),
            name(obj.name),
            offset(obj.offset),
            size(obj.size),
            fields(obj.fields),
            properties(obj.properties),
            methods(obj.methods),
            owner(nullptr)
        {}

        ClassMetadata(ClassMetadata&& obj) :
            type(obj.type),
            name(obj.name),
            offset(obj.offset),
            size(obj.size),
            fields(std::move(obj.fields)),
            properties(std::move(obj.properties)),
            methods(std::move(obj.methods)),
            owner(nullptr)
        {}

        ClassMetadata(const type_info& type, const static_string<64>& name, size_t offset, size_t size) :
            type(type),
            name(name),
            offset(offset),
            size(size),
            owner(nullptr)
        {}

        template <typename C, typename T>
        ClassMetadata& def_field(static_string<64> name, T C:: *member)
        {
            const type_info &type = typeid(T);
            size_t offset = reinterpret_cast<size_t>(&reinterpret_cast<const volatile char&>(((C*)0)->*member));
            size_t size = sizeof(T);
            this->fields.emplace_back(type, name, offset, size);
            return this->fields.back();
        }

        template <typename R = void, typename C, typename ...Args>
        MethodMetadata& def_method(static_string<64> name, R(C::*method)(Args...))
        {
            this->methods.emplace_back(name, method);
            return this->methods.back();
        }

        template <typename C, typename T>
        PropertyMetadata& def_property(static_string<64> name, T(C::*getter)(void), void(C::*setter)(T))
        {
            this->properties.emplace_back(name, getter, setter);
            return this->properties.back();
        }

        template <typename C, typename T>
        PropertyMetadata& def_property(static_string<64> name, T(C::*getter)(void), nullptr_t)
        {
            this->properties.emplace_back(name, getter, nullptr);
            return this->properties.back();
        }

        template <typename C, typename T>
        PropertyMetadata& def_property(static_string<64> name, nullptr_t, void(C::*setter)(T))
        {
            this->properties.emplace_back(name, nullptr, setter);
            return this->properties.back();
        }

        template <typename T, typename C>
        T get(C *instance, static_string<64> name)
        {
            for (auto& property : properties)
            {
                if (property.name == name)
                {
                    return reinterpret_cast<function<T()>&>(property.getter)(instance);
                }
            }
            for (auto& field : fields)
            {
                if (field.name == name)
                {
                    using byte = char;
                    void* ptr = reinterpret_cast<byte*>(instance) + field.offset;
                    return *reinterpret_cast<T*>(ptr);
                }
            }
            runtime_assert(false, format("{0} is not defined this object.", name.c_str()));
        }

        template <typename T, typename C>
        void set(C *instance, static_string<64> name, const T &value)
        {
            for (auto& property : properties)
            {
                if (property.name == name)
                {
                    reinterpret_cast<function<void(T)>&>(property.setter)(instance, value);
                    return;
                }
            }
            for (auto& field : fields)
            {
                if (field.name == name)
                {
                    using byte = char;
                    void* ptr = reinterpret_cast<byte*>(instance) + field.offset;
                    *reinterpret_cast<T*>(ptr) = value;
                    return;
                }
            }
            runtime_assert(false, format("{0} is not defined this object.", name.c_str()));
        }

        template <typename R = void, typename C, typename ...Args>
        R invoke(C *instance, static_string<64> name, Args ...args)
        {
            for (auto& method : methods)
            {
                if (method.name == name)
                {
                    return reinterpret_cast<function<R(Args...)>&>(method.method).invoke(instance, std::forward<Args>(args)...);
                }
            }
            runtime_assert(false, format("{0} is not defined this object.", name.c_str()));
        }
    };


    class dynamic
    {};
}
