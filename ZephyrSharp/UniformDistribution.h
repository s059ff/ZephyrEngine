#pragma once

#include <random>

#include "common.h"
#include "INativeWrapper.h"

#undef min
#undef max

namespace ZephyrSharp
{
    /// <summary>
    /// 一様分布を表します。
    /// </summary>
    public ref class UniformDistribution : INativeWrapper<std::uniform_real_distribution<float>>
    {
    public:

        /// <summary>
        /// 確率分布を作成します。
        /// </summary>
        /// <param name="min">乱数の最小値。</param> 
        /// <param name="max">乱数の最大値。</param> 
        UniformDistribution(float min, float max)
        {
            Native->param(std::uniform_real_distribution<float>::param_type(min, max));
        }

        /// <summary>
        /// 乱数の最小値を取得または設定します。
        /// </summary>
        property float Min
        {
            float get() { return Native->min(); }
            void set(float value) { Native->param(std::uniform_real_distribution<float>::param_type(value, Native->max())); }
        }

        /// <summary>
        /// 乱数の最大値を取得または設定します。
        /// </summary>
        property float Max
        {
            float get() { return Native->max(); }
            void set(float value) { Native->param(std::uniform_real_distribution<float>::param_type(Native->min(), value)); }
        }
    };
}
