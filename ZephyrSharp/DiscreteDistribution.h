#pragma once

#include <random>

#include "common.h"
#include "INativeWrapper.h"

#undef min
#undef max

namespace ZephyrSharp
{
    /// <summary>
    /// 任意の離散確率分布を表します。
    /// </summary>
    public ref class DiscreteDistribution : INativeWrapper<std::discrete_distribution<int>>
    {
    public:

        /// <summary>
        /// 確率分布を作成します。
        /// </summary>
        /// <param name="probabilities">0, 1, ... の値が出現する確率を定義する配列。総和が 1 である必要はありません。</param> 
        DiscreteDistribution(array<float>^ probabilities)
        {
            pin_ptr<float> _begin = &probabilities[0];
            float* begin = _begin;
            float* end = begin + probabilities->Length;
            Native->operator=(std::discrete_distribution<int>(begin, end));
        }

        /// <summary>
        /// この確率分布から生成される乱数の最小値。
        /// </summary>
        property int Min
        {
            int get() { return Native->min(); }
        }

        /// <summary>
        /// この確率分布から生成される乱数の最大値。
        /// </summary>
        property int Max
        {
            int get() { return Native->max(); }
        }
    };
}
