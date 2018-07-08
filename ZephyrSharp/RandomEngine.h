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
    /// ����������ł��B
    /// </summary>
    public ref class RandomEngine : public INativeWrapper<std::mt19937_64>
    {
    public:

        RandomEngine()
        {
            NativeRef.seed(std::random_device()());
        }

        /// <summary>
        /// ��l�����𐶐����܂��B
        /// </summary>
        /// <param name="distribution">��l�����̊m�����z�B</param> 
        float Random(UniformDistribution^ distribution)
        {
            return distribution->NativeRef(NativeRef);
        }

        /// <summary>
        /// ���K���z�ɏ]�������𐶐����܂��B
        /// </summary>
        /// <param name="distribution">���K���z�B</param> 
        float Random(NormalDistribution^ distribution)
        {
            return distribution->NativeRef(NativeRef);
        }

        /// <summary>
        /// �C�ӂ̊m�����z�ɏ]�������𐶐����܂��B
        /// </summary>
        /// <param name="distribution">�C�ӂ̊m�����z�B</param>
        int Random(DiscreteDistribution^ distribution)
        {
            return distribution->NativeRef(NativeRef);
        }
    };
}
