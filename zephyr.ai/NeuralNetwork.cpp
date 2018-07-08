#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "zephyr\runtime_assert.h"

#include "NeuralNetwork.h"

#define this (*this)

using namespace Eigen;
using namespace std;

namespace zephyr
{
    namespace ai
    {
        static constexpr double PI = 3.14159265359;
        static constexpr double PI2 = PI * 2;

        static double linear(double x) { return x; };
        static double dlinear(double x) { return 1.0; };

        static double relu(double x) { return (0.0 < x) ? x : 0.0; };
        static double drelu(double x) { return (0.0 < x) ? 1.0 : 0.0; };

        static double tanh(double x) { return (exp(x) - exp(-x)) / (exp(x) + exp(-x)); };
        static double dtanh(double x)
        {
            double t = tanh(x);
            return 1 - t * t;
        };

        static double gauss(double x) { return exp(-x * x / 2) / sqrt(PI2); }
        static double dgauss(double x) { return -x * exp(-x * x / 2) / sqrt(PI2); }

        static double sigmoid(double x) { return 1 / (1 + exp(-x)); }
        static double dsigmoid(double x) { double sigmoid_ = sigmoid(x); return (1 - sigmoid_) * sigmoid_; }

        NeuralNetwork::NeuralNetwork() {}

        NeuralNetwork::~NeuralNetwork()
        {
            auto layer = begin;

            while (layer != nullptr)
            {
                auto next = layer->next;
                delete layer;
                layer = next;
                depth--;
            }

            assert(depth == 0);
        }

        double(*functions(const char* _funcname))(double)
        {
            string funcname = _funcname;
            if (funcname == "linear")
                return linear;
            if (funcname == "dlinear")
                return dlinear;
            if (funcname == "relu")
                return relu;
            if (funcname == "drelu")
                return drelu;
            if (funcname == "tanh")
                return tanh;
            if (funcname == "dtanh")
                return dtanh;
            if (funcname == "gauss")
                return gauss;
            if (funcname == "dgauss")
                return dgauss;
            if (funcname == "sigmoid")
                return sigmoid;
            if (funcname == "dsigmoid")
                return dsigmoid;
            runtime_assert(false, "Not supported function.");
            return nullptr;
        };

        void NeuralNetwork::attach(int length, const char* fname, const char* dfname)
        {
            depth++;

            if (begin == nullptr)
            {
                Layer* layer = new Layer();
                layer->back = nullptr;
                layer->next = nullptr;
                layer->J = length;
                //layer->Z = MatrixXd::Zero(layer->J, N);
                layer->f = functions(fname);
                layer->df = functions(dfname);
                strcpy_s(layer->fname, fname);
                strcpy_s(layer->dfname, dfname);

                begin = layer;
                end = layer;
            }
            else
            {
                Layer* layer = new Layer();
                end->next = layer;

                auto back = end;
                int J = length;
                int I = back->J;
                layer->J = length;
                layer->back = back;
                layer->next = nullptr;
                //layer->U = MatrixXd::Zero(J, N);
                //layer->Z = MatrixXd::Zero(J, N);
                layer->W = MatrixXd::Random(J, I) * 0.1;
                layer->B = VectorXd::Random(J) * 0.1;
                //layer->Δ = MatrixXd::Zero(J, N);
                layer->dW = MatrixXd::Zero(J, I);
                layer->db = VectorXd::Zero(J);
                layer->f = functions(fname);
                layer->df = functions(dfname);
                strcpy_s(layer->fname, fname);
                strcpy_s(layer->dfname, dfname);

                end = layer;
            }
        }

        void NeuralNetwork::train(const MatrixXd& X, const MatrixXd& D)
        {
            assert(depth > 2);

            this.forward(X);
            this.backward(D);
            this.update();
        }

        double NeuralNetwork::_get_loss() const
        {
            const auto N = input.cols();
            return end->Δ.unaryExpr([](double x) { return x * x; }).sum() * 0.5 / N;
        }

        MatrixXd NeuralNetwork::forward(const MatrixXd& X)
        {
            const auto N = X.cols();

            begin->Z = X;

            Layer* layer = begin->next;
            while (layer != nullptr)
            {
                auto& X = layer->back->Z;
                layer->U = layer->W * X + layer->B * RowVectorXd::Ones(N);
                layer->Z = layer->U.unaryExpr(layer->f);

                layer = layer->next;
            }
            return end->Z;
        }

        void NeuralNetwork::backward(const MatrixXd& D)
        {
            end->Δ = end->Z - D;

            Layer* layer = end->back;
            while (layer != begin)
            {
                Layer* next = layer->next;
                layer->Δ = layer->U.unaryExpr(layer->df).array() * (next->W.transpose() * next->Δ).array();

                layer = layer->back;
            }
        }

        void NeuralNetwork::update()
        {
            const auto N = input.cols();

            Layer* layer = begin->next;
            while (layer != nullptr)
            {
                Layer* back = layer->back;
                layer->W -= ε / N * layer->Δ * back->Z.transpose();
                layer->B -= ε / N * layer->Δ.rowwise().sum();

                layer = layer->next;
            }
        }

        using byte = unsigned char;

        struct LayerMetadata
        {
            int D = 0;
            char fname[16];
            char dfname[16];
            int data_offset_W = 0;
            int data_offset_B = 0;
        };

        struct NetworkMetadata
        {
            int datasize = 0;
            LayerMetadata layers[16];
        };

        static constexpr char Version[64] = "2017.03.24";

        void NeuralNetwork::load(const char* path)
        {
            ifstream ifs(path, ios::binary);
            runtime_assert(ifs.good());

            // バージョン情報を読み込む
            char version[64];
            ifs.read(version, sizeof(version));
            runtime_assert(string(version) == Version);

            // メタデータを読み込む
            NetworkMetadata meta;
            ifs.read((char*)&meta, sizeof(NetworkMetadata));
            for (int i = 0; i < 16; i++)
            {
                LayerMetadata md_layer = meta.layers[i];
                if (md_layer.D == 0)
                    break;
                this.attach(md_layer.D, md_layer.fname, md_layer.dfname);
            }

            // パラメータデータを復元する
            unique_ptr<byte[]> data(new byte[meta.datasize]);

            ifs.read((char*)data.get(), meta.datasize);
            Layer* layer = this.begin;
            for (int i = 0; i < 16; i++)
            {
                LayerMetadata md_layer = meta.layers[i];
                if (md_layer.D == 0)
                    break;
                if (layer->W.size() > 0)
                    memcpy(layer->W.data(), data.get() + md_layer.data_offset_W, sizeof(double) * layer->W.size());
                if (layer->B.size() > 0)
                    memcpy(layer->B.data(), data.get() + md_layer.data_offset_B, sizeof(double) * layer->B.size());
                layer = layer->next;
            }
        }

        void NeuralNetwork::save(const char* path)
        {
            ofstream ofs(path, ios::binary | ios::trunc);
            runtime_assert(ofs.good());

            // バージョン情報を書き込む
            ofs.write(Version, sizeof(Version));

            // メタデータを設定する
            NetworkMetadata meta;
            meta.datasize = 0;

            Layer* layer = this.begin;
            for (int i = 0; i < 16; i++)
            {
                LayerMetadata md_layer;
                md_layer.D = layer->J;
                strcpy_s(md_layer.fname, layer->fname);
                strcpy_s(md_layer.dfname, layer->dfname);
                md_layer.data_offset_W = meta.datasize;
                meta.datasize += sizeof(double) * layer->W.size();
                md_layer.data_offset_B = meta.datasize;
                meta.datasize += sizeof(double) * layer->B.size();
                meta.layers[i] = md_layer;
                if (layer == this.end)
                    break;
                layer = layer->next;
            }

            // パラメータデータを設定する
            unique_ptr<byte[]> data(new byte[meta.datasize]);
            layer = this.begin;
            for (int i = 0; i < 16; i++)
            {
                LayerMetadata md_layer = meta.layers[i];
                if (layer->W.size() > 0)
                    memcpy(data.get() + md_layer.data_offset_W, layer->W.data(), sizeof(double) * layer->W.size());
                if (layer->B.size() > 0)
                    memcpy(data.get() + md_layer.data_offset_B, layer->B.data(), sizeof(double) * layer->B.size());
                if (layer == this.end)
                    break;
                layer = layer->next;
            }

            // メタデータを書き込む
            ofs.write((char*)&meta, sizeof(NetworkMetadata));

            // パラメータを書き込む
            ofs.write((char*)data.get(), meta.datasize);
        }
    }
}
