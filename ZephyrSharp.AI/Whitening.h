#pragma once

#include "common.h"
#include "MatrixXd.h"

namespace ZephyrSharp
{
    namespace AI
    {
        public ref class Whitening : public INativeWrapper<zephyr::ai::Whitening>
        {
        public:

            void Prepare(MatrixXd^ X)
            {
                Native->prepare(X->NativeRef);
            }

            MatrixXd^ Whiten(MatrixXd^ X)
            {
                MatrixXd^ dest = gcnew MatrixXd();
                *dest->Native = Native->whiten(X->NativeRef);
                return dest;
            }
        };
    }
}
