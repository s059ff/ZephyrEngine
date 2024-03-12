#pragma once

#include "zephyr\com_ptr.h"

struct IDirectInput8A;

namespace zephyr
{
    namespace input
    {
        template <typename T> class Interface : public com_ptr<T>
        {
        protected:
            using base = com_ptr<T>;

        public:
            virtual void Release()
            {
                base::reset();
            }
        };
    }
}
