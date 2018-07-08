#include "Whitening.h"

using namespace Eigen;

namespace zephyr
{
    namespace ai
    {
        void Whitening::prepare(const MatrixXd& X)
        {
            const auto D = X.rows();
            const auto N = X.cols();

            mean = VectorXd::Zero(D);
            sigma = VectorXd::Zero(D);

            for (int j = 0; j < N; j++)
            {
                mean += X.col(j);
            }
            mean /= N;

            for (int i = 0; i < D; i++)
            {
                sigma(i) = sqrt(X.row(i).squaredNorm() / (N - 1));
            }
        }

        MatrixXd Whitening::whiten(const MatrixXd& X)
        {
            const auto D = X.rows();
            const auto N = X.cols();

            MatrixXd Y(D, N);

            for (int j = 0; j < N; j++)
            {
                Y.col(j) = X.col(j) - mean;
            }

            for (int i = 0; i < D; i++)
            {
                Y.row(i).array() /= sigma(i);
            }

            return Y;
        }
    }
}
