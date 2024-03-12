#pragma once

#include <random>

#include "common.h"
#include "UniformDistribution.h"
#include "NormalDistribution.h"
#include "DiscreteDistribution.h"
#include "INativeWrapper.h"

namespace ZephyrSharp
{
    /// <summary>
    /// 乱数生成器です。
    /// </summary>
    public ref class RandomEngine : public INativeWrapper<std::mt19937_64>
    {
    public:

        RandomEngine()
        {
            NativeRef.seed(std::random_device()());
        }

        /// <summary>
        /// 一様乱数を生成します。
        /// </summary>
        /// <param name="distribution">一様乱数の確率分布。</param> 
        float Random(UniformDistribution^ distribution)
        {
            return distribution->NativeRef(NativeRef);
        }

        /// <summary>
        /// 正規分布に従う乱数を生成します。
        /// </summary>
        /// <param name="distribution">正規分布。</param> 
        float Random(NormalDistribution^ distribution)
        {
            return distribution->NativeRef(NativeRef);
        }

        /// <summary>
        /// 任意の確率分布に従う乱数を生成します。
        /// </summary>
        /// <param name="distribution">任意の確率分布。</param>
        int Random(DiscreteDistribution^ distribution)
        {
            return distribution->NativeRef(NativeRef);
        }
    };
}
