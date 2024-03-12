#pragma once

#include <Core>

#include "common.h"

namespace ZephyrSharp
{
    namespace AI
    {
        public ref class VectorXd : public INativeWrapper<Eigen::VectorXd>
        {
        public:

            VectorXd()
            {
            }

            VectorXd(const Eigen::VectorXd& native)
            {
                *Native = native;
            }

            VectorXd(... array<double>^ src)
            {
                int m = src->Length;
                Resize(m);
                for (int i = 0; i < m; i++)
                {
                    this->default[i] = src[i];
                }
            }

            void CopyFrom(VectorXd^ src)
            {
                (*Native) = (*src->Native);
            }

            void CopyTo(VectorXd^ src)
            {
                (*src->Native) = (*Native);
            }

            void Resize(int m)
            {
                Native->resize(m);
            }

        public:

            static VectorXd^ Zero(int m)
            {
                return gcnew VectorXd(Eigen::VectorXd::Zero(m));
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
