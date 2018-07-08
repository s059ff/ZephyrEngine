#pragma once

#include <Core>

#include "common.h"
#include "VectorXd.h"
#include "RowVectorXd.h"

namespace ZephyrSharp
{
    namespace AI
    {
        public ref class MatrixXd : public INativeWrapper<Eigen::MatrixXd>
        {
        public:

            MatrixXd()
            {
            }

            MatrixXd(const Eigen::MatrixXd& native)
            {
                *Native = native;
            }

            MatrixXd(array<double, 2>^ src)
            {
                int m = src->GetLength(0);
                int n = src->GetLength(1);
                Resize(m, n);
                for (int i = 0; i < m; i++)
                {
                    for (int j = 0; j < n; j++)
                    {
                        this->default[i, j] = src[i, j];
                    }
                }
            }

            void CopyFrom(MatrixXd^ src)
            {
                (*Native) = (*src->Native);
            }

            void CopyTo(MatrixXd^ src)
            {
                (*src->Native) = (*Native);
            }

            void Resize(int m, int n)
            {
                Native->resize(m, n);
            }

            RowVectorXd^ Row(int m)
            {
                RowVectorXd^ dest = gcnew RowVectorXd();
                *dest->Native = Native->row(m);
                return dest;
            }

            VectorXd^ Col(int n)
            {
                VectorXd^ dest = gcnew VectorXd();
                *dest->Native = Native->col(n);
                return dest;
            }

            MatrixXd^ Block(int startRow, int startCol, int rows, int cols)
            {
                return gcnew MatrixXd(Native->block(startRow, startCol, rows, cols));
            }

        public:

            static MatrixXd^ Zero(int m, int n)
            {
                return gcnew MatrixXd(Eigen::MatrixXd::Zero(m, n));
            }

            static MatrixXd^ Ones(int m, int n)
            {
                return gcnew MatrixXd(Eigen::MatrixXd::Ones(m, n));
            }

            static MatrixXd^ Constant(int m, int n, double value)
            {
                return gcnew MatrixXd(Eigen::MatrixXd::Constant(m, n, value));
            }

        public:

            property double default[int, int]
            {
                double get(int i, int j) { return NativeRef(i, j); }

                void set(int i, int j, double value) { NativeRef(i, j) = value; }
            }
        };
    }
}
