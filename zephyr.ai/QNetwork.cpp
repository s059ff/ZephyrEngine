#include "QNetwork.h"

using namespace Eigen;

namespace zephyr
{
    namespace ai
    {
        static constexpr double alpha = 0.1;
        static constexpr double gamma = 0.9;

        QNetwork::QNetwork(int S, int A) : S(S), A(A), D(S + A), N(N)
        {
            network.attach(D, "linear", "dlinear");
            network.attach(16, "relu", "drelu");
            network.attach(1, "linear", "dlinear");
        }

        double QNetwork::value(const VectorXd& s, const VectorXd& a)
        {
            VectorXd x(D);
            x.block(0, 0, S, 1) = s;
            x.block(S, 0, A, 1) = a;

            return network.forward(x)(0, 0);
        }

        void QNetwork::update(const MatrixXd& s, const MatrixXd& a, const MatrixXd& s_, const MatrixXd& a_, const RowVectorXd& r)
        {
            MatrixXd X(D, N);
            X.block(0, 0, S, N) = s;
            X.block(S, 0, A, N) = a;

            MatrixXd X_(D, N);
            X_.block(0, 0, S, N) = s_;
            X_.block(S, 0, A, N) = a_;

            RowVectorXd Q__(N);
            RowVectorXd Q_ = network.forward(X_);
            RowVectorXd Q = network.forward(X);
            RowVectorXd DeltaQ = alpha * (r + gamma * Q_ - Q);
            Q__ = Q + DeltaQ;

            network.backward(Q__);
            network.update();

            dq = DeltaQ.sum() / N;
        }
    }
}
