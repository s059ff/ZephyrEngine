#pragma once

#include "common.h"
#include "MatrixXd.h"
#include "VectorXd.h"
#include "RowVectorXd.h"

namespace ZephyrSharp
{
    namespace AI
    {
        public ref class QNetwork : public INativeWrapper<zephyr::ai::QNetwork>
        {
        public:

            QNetwork(int S, int A) : INativeWrapper<zephyr::ai::QNetwork>(S, A) {}

            double Value(VectorXd^ s, VectorXd^ a)
            {
                return Native->value(s->NativeRef, a->NativeRef);
            }

            void Update(MatrixXd^ s, MatrixXd^ a, MatrixXd^ s_, MatrixXd^ a_, RowVectorXd^ r)
            {
                Native->update(s->NativeRef, a->NativeRef, s_->NativeRef, a_->NativeRef, r->NativeRef);
            }

        public:

            property double Loss {double get() { return Native->loss; }}

            property double Delta {double get() { return Native->delta; }}
        };
    }
}
