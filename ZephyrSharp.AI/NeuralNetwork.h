#pragma once

#include "common.h"
#include "MatrixXd.h"

namespace ZephyrSharp
{
    namespace AI
    {
        public ref class NeuralNetwork : public INativeWrapper<zephyr::ai::NeuralNetwork>
        {
        public:

            void Attach(int length, System::String^ fname, System::String^ dfname)
            {
                Native->attach(length, to_string(fname).c_str(), to_string(dfname).c_str());
            }

            void Train(MatrixXd^ X, MatrixXd^ D)
            {
                Native->train(X->NativeRef, D->NativeRef);
            }

            MatrixXd^ Forward(MatrixXd^ X)
            {
                MatrixXd^ dest = gcnew MatrixXd();
                *dest->Native = Native->forward(X->NativeRef);
                return dest;
            }

            void Backward(MatrixXd^ D)
            {
                Native->backward(D->NativeRef);
            }

            void Update()
            {
                Native->update();
            }

            void Load(System::String^ path)
            {
                Native->load(to_string(path).c_str());
            }

            void Save(System::String^ path)
            {
                Native->save(to_string(path).c_str());
            }

        public:

            property MatrixXd^ Input
            {
                MatrixXd^ get()
                {
                    MatrixXd^ dest = gcnew MatrixXd();
                    *dest->Native = Native->input;
                    return dest;
                }
            }

            property MatrixXd^ Output
            {
                MatrixXd^ get()
                {
                    MatrixXd^ dest = gcnew MatrixXd();
                    *dest->Native = Native->output;
                    return dest;
                }
            }

            property double Loss
            {
                double get()
                {
                    return Native->loss;
                }
            }

            property double É√
            {
                double get() { return Native->É√; }

                void set(double value) { Native->É√ = value; }
            }
        };
    }
}
