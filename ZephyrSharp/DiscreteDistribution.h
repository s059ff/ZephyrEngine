#pragma once

#include <random>

#include "common.h"
#include "INativeWrapper.h"

#undef min
#undef max

namespace ZephyrSharp
{
    /// <summary>
    /// �C�ӂ̗��U�m�����z��\���܂��B
    /// </summary>
    public ref class DiscreteDistribution : INativeWrapper<std::discrete_distribution<int>>
    {
    public:

        /// <summary>
        /// �m�����z���쐬���܂��B
        /// </summary>
        /// <param name="probabilities">0, 1, ... �̒l���o������m�����`����z��B���a�� 1 �ł���K�v�͂���܂���B</param> 
        DiscreteDistribution(array<float>^ probabilities)
        {
            pin_ptr<float> _begin = &probabilities[0];
            float* begin = _begin;
            float* end = begin + probabilities->Length;
            Native->operator=(std::discrete_distribution<int>(begin, end));
        }

        /// <summary>
        /// ���̊m�����z���琶������闐���̍ŏ��l�B
        /// </summary>
        property int Min
        {
            int get() { return Native->min(); }
        }

        /// <summary>
        /// ���̊m�����z���琶������闐���̍ő�l�B
        /// </summary>
        property int Max
        {
            int get() { return Native->max(); }
        }
    };
}
