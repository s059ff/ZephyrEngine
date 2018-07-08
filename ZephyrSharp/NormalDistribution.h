#pragma once

#include <random>

#include "common.h"
#include "INativeWrapper.h"

namespace ZephyrSharp
{
    /// <summary>
    /// 正規分布を表します。
    /// </summary>
    public ref class NormalDistribution : INativeWrapper<std::normal_distribution<float>>
    {
    public:

        /// <summary>
        /// 標準正規分布を作成します。
        /// </summary>
        NormalDistribution()
        {
            Native->param(std::normal_distribution<float>::param_type(0, 1));
        }

        /// <summary>
        /// 正規分布を作成します。
        /// </summary>
        /// <param name="mean">分布の平均。</param> 
        /// <param name="variance">分布の分散。</param> 
        NormalDistribution(float mean, float variance)
        {
            Native->param(std::normal_distribution<float>::param_type(mean, variance));
        }

        /// <summary>
        /// 分布の平均を取得または設定します。
        /// </summary>
        property float Mean
        {
            float get() { return Native->mean(); }
            void set(float value) { Native->param(std::normal_distribution<float>::param_type(value, Native->sigma())); }
        }

        /// <summary>
        /// 分布の分散を取得または設定します。
        /// </summary>
        property float Variance
        {
            float get() { return Native->sigma(); }
            void set(float value) { Native->param(std::normal_distribution<float>::param_type(Native->mean(), value)); }
        }
    };
}
