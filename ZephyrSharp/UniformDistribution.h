#pragma once

#include <random>

#include "common.h"
#include "INativeWrapper.h"

#undef min
#undef max

namespace ZephyrSharp
{
    /// <summary>
    /// ��l���z��\���܂��B
    /// </summary>
    public ref class UniformDistribution : INativeWrapper<std::uniform_real_distribution<float>>
    {
    public:

        /// <summary>
        /// �m�����z���쐬���܂��B
        /// </summary>
        /// <param name="min">�����̍ŏ��l�B</param> 
        /// <param name="max">�����̍ő�l�B</param> 
        UniformDistribution(float min, float max)
        {
            Native->param(std::uniform_real_distribution<float>::param_type(min, max));
        }

        /// <summary>
        /// �����̍ŏ��l���擾�܂��͐ݒ肵�܂��B
        /// </summary>
        property float Min
        {
            float get() { return Native->min(); }
            void set(float value) { Native->param(std::uniform_real_distribution<float>::param_type(value, Native->max())); }
        }

        /// <summary>
        /// �����̍ő�l���擾�܂��͐ݒ肵�܂��B
        /// </summary>
        property float Max
        {
            float get() { return Native->max(); }
            void set(float value) { Native->param(std::uniform_real_distribution<float>::param_type(Native->min(), value)); }
        }
    };
}
