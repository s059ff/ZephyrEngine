#pragma once

#include <random>

#include "common.h"
#include "INativeWrapper.h"

namespace ZephyrSharp
{
    /// <summary>
    /// ���K���z��\���܂��B
    /// </summary>
    public ref class NormalDistribution : INativeWrapper<std::normal_distribution<float>>
    {
    public:

        /// <summary>
        /// �W�����K���z���쐬���܂��B
        /// </summary>
        NormalDistribution()
        {
            Native->param(std::normal_distribution<float>::param_type(0, 1));
        }

        /// <summary>
        /// ���K���z���쐬���܂��B
        /// </summary>
        /// <param name="mean">���z�̕��ρB</param> 
        /// <param name="variance">���z�̕��U�B</param> 
        NormalDistribution(float mean, float variance)
        {
            Native->param(std::normal_distribution<float>::param_type(mean, variance));
        }

        /// <summary>
        /// ���z�̕��ς��擾�܂��͐ݒ肵�܂��B
        /// </summary>
        property float Mean
        {
            float get() { return Native->mean(); }
            void set(float value) { Native->param(std::normal_distribution<float>::param_type(value, Native->sigma())); }
        }

        /// <summary>
        /// ���z�̕��U���擾�܂��͐ݒ肵�܂��B
        /// </summary>
        property float Variance
        {
            float get() { return Native->sigma(); }
            void set(float value) { Native->param(std::normal_distribution<float>::param_type(Native->mean(), value)); }
        }
    };
}
