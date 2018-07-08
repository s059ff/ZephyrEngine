#pragma once

#include "common.h"
#include "Color.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ���̂̃}�e���A������\���܂��B
        /// </summary>
        public value struct Material
        {
            /// <summary>
            /// �A���r�G���g �J���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Color Ambient;

            /// <summary>
            /// �f�B�t���[�Y �J���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Color Diffuse;

            /// <summary>
            /// �X�y�L�����[ �J���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Color Specular;

            /// <summary>
            /// �X�y�L�����[ �p���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float Power;
        };
    }
}
