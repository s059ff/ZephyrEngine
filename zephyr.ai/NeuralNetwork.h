#pragma once

#include <Core>

#include "zephyr\assert.h"
#include "zephyr\property.h"

namespace zephyr
{
    namespace ai
    {
        class NeuralNetwork
        {
            using MatrixXd = Eigen::MatrixXd;
            using VectorXd = Eigen::VectorXd;
            
        public:

            NeuralNetwork();

            ~NeuralNetwork();

            void attach(int length, const char* fname, const char* dfname);

            void train(const MatrixXd& X, const MatrixXd& D);

            MatrixXd forward(const MatrixXd& X);

            void backward(const MatrixXd& D);

            void update();

            void load(const char* path);

            void save(const char* path);

        public:

            READONLY_PROPERTY(MatrixXd, input, const{ return begin->Z; });

            READONLY_PROPERTY(MatrixXd, output, const{ return end->Z; });

            READONLY_PROPERTY(double, loss, const;);

        public:

            double É√ = 0.01f;

        private:

            class Layer
            {
            public:

                MatrixXd U;

                MatrixXd Z;

                MatrixXd W;

                VectorXd B;

                MatrixXd É¢;

                MatrixXd dW;

                MatrixXd db;

                int J;

                Layer* next;

                Layer* back;

                double(*f)(double);

                double(*df)(double);

                char fname[16];

                char dfname[16];
            };

            int depth = 0;

            Layer* begin = nullptr;

            Layer* end = nullptr;
        };
    }
}
