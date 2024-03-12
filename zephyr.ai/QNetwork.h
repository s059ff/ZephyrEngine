#pragma once

#include <Core>

#include "zephyr\property.h"
#include "NeuralNetwork.h"

namespace zephyr
{
    namespace ai
    {
        class QNetwork
        {
            using MatrixXd = Eigen::MatrixXd;
            using VectorXd = Eigen::VectorXd;
            using RowVectorXd = Eigen::RowVectorXd;

        public:

            QNetwork(int S, int A);

            double value(const VectorXd& s, const VectorXd& a);

            void update(const MatrixXd& s, const MatrixXd& a, const MatrixXd& s_, const MatrixXd& a_, const RowVectorXd& r);

        public:

            READONLY_PROPERTY(double, loss, const{ return network.loss; });

            READONLY_PROPERTY(double, delta, const{ return dq; });

        private:

            NeuralNetwork network;

            const int S;

            const int A;

            const int D;

            const int N;

            double dq;
        };
    }
}
