#pragma once

#include <Core>

namespace zephyr
{
    namespace ai
    {
        class Whitening
        {
            using MatrixXd = Eigen::MatrixXd;
            using VectorXd = Eigen::VectorXd;

        private:

            VectorXd mean;
            VectorXd sigma;

        public:

            void prepare(const MatrixXd& X);

            MatrixXd whiten(const MatrixXd& X);
        };
    }
}
