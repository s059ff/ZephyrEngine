#pragma once

#include "zephyr\com_ptr.h"

namespace zephyr
{
    namespace graphics
    {
        template <typename T> class Interface : public com_ptr<T>
        {
        protected:
            using base = com_ptr<T>;

        public:

            Interface() : base()
            {
            }

            Interface(T* p) : base(p)
            {
            }

            virtual void Release()
            {
                base::reset();
            }
        };
    }
}
