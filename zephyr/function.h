#pragma once

#include "shared_ptr.h"

namespace zephyr
{
    template <typename> class function;

    template <typename return_type, typename ...argument_types>
    class function<return_type(argument_types...)>
    {
    private:
        struct abstract_holder
        {
            virtual ~abstract_holder() {}

            virtual return_type invoke(argument_types ...args) = 0;
        };

        struct function_holder : public abstract_holder
        {
            virtual ~function_holder()
            {
                this->function = nullptr;
            }

            virtual return_type invoke(argument_types ...args)
            {
                return (*this->function)(std::forward<argument_types>(args)...);
            }

            return_type(*function)(argument_types...);
        };

        template <typename lambda_type>
        struct lambda_function_holder : public abstract_holder
        {
            virtual ~lambda_function_holder<lambda_type>()
            {
                this->lambda = nullptr;
            }

            virtual return_type invoke(argument_types ...args)
            {
                return (*this->lambda)(std::forward<argument_types>(args)...);
            }

            const lambda_type *lambda;
        };

        template <typename class_type>
        struct method_holder : public abstract_holder
        {
            virtual ~method_holder<class_type>()
            {
                this->method = nullptr;
                this->instance = nullptr;
            }

            virtual return_type invoke(argument_types ...args)
            {
                return ((*this->instance).*this->method)(std::forward<argument_types>(args)...);
            }

            return_type(class_type::*method)(argument_types...);

            class_type *instance;
        };

        std::shared_ptr<abstract_holder> holder = nullptr;

    public:

        function() = default;

        function(return_type(*function)(argument_types ...))
        {
            operator= (function);
        }

        template <typename class_type>
        function(return_type(class_type::*method)(argument_types ...))
        {
            operator= (method);
        }

        template <typename lambda_type>
        function(const lambda_type &lambda)
        {
            operator= (lambda);
        }

        ~function()
        {
            holder.reset();
        }

        void operator =(return_type(*function)(argument_types ...))
        {
            holder.reset(new function_holder());
            ((function_holder*)holder.get())->function = function;
        }

        template <typename lambda_type>
        void operator =(const lambda_type &lambda)
        {
            holder.reset(new lambda_function_holder<lambda_type>());
            ((lambda_function_holder<lambda_type>*)holder.get())->lambda = &lambda;
        }

        template <typename class_type>
        void operator =(return_type(class_type::*method)(argument_types ...))
        {
            holder.reset(new method_holder<class_type>());
            ((method_holder<class_type>*)holder.get())->method = method;
        }

        template <typename class_type>
        void instance(class_type *_this)
        {
            dynamic_cast<method_holder<class_type>*>(holder.get())->instance = _this;
        }

        return_type invoke(argument_types ...args)
        {
            runtime_assert(holder.get() != nullptr);
            return holder->invoke(std::forward<argument_types>(args)...);
        }

        template <typename class_type>
        return_type invoke(class_type *instance, argument_types ...args)
        {
            runtime_assert(holder.get() != nullptr);
            dynamic_cast<method_holder<class_type>*>(holder.get())->instance = instance;
            return holder->invoke(std::forward<argument_types>(args)...);
        }

        return_type operator() (argument_types ...args)
        {
            return invoke(std::forward<argument_types>(args)...);
        }

        template <typename class_type>
        return_type operator() (class_type *instance, argument_types ...args)
        {
            return invoke(instance, std::forward<argument_types>(args)...);
        }

        bool executable() const
        {
            return this->holder.get() != nullptr;
        }
    };
}
