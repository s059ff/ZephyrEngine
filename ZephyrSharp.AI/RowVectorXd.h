#pragma once

#include <Core>

#include "common.h"

namespace ZephyrSharp
{
    namespace AI
    {
        public ref class RowVectorXd : public INativeWrapper<Eigen::RowVectorXd>
        {
        public:

            RowVectorXd()
            {
            }

            RowVectorXd(const Eigen::RowVectorXd& native)
            {
                *Native = native;
            }

            RowVectorXd(... array<double>^ src)
            {
                int n = src->Length;
                Resize(n);
                for (int i = 0; i < n; i++)
                {
                    this->default[i] = src[i];
                }
            }

            void CopyFrom(RowVectorXd^ src)
            {
                (*Native) = (*src->Native);
            }

            void CopyTo(RowVectorXd^ src)
            {
                (*src->Native) = (*Native);
            }

            void Resize(int m)
            {
                Native->resize(m);
            }

        public:

            static RowVectorXd^ Zero(int m)
            {
                return gcnew RowVectorXd(Eigen::RowVectorXd::Zero(m));
            }

        public:

            property double default[int]
            {
                double get(int i) { return NativeRef(i); }

                void set(int i, double value) { NativeRef(i) = value; }
            }
        };
    }
}
