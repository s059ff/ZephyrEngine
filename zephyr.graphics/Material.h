#pragma once

#include "Color.h"

namespace zephyr
{
    namespace graphics
    {
        /// <summary>
        /// �O���t�B�b�N�X���f���̍ގ���\���܂��B
        /// </summary>
        struct Material
        {
            /// <summary>
            /// ���̃N���X�̐V�����C���X�^���X�����������܂��B
            /// </summary>
            Material() :
                ambient(0, 0, 0, 1),
                diffuse(1, 1, 1, 1),
                specular(0, 0, 0, 1),
                power(0)
            {
            }

            /// <summary>
            /// �A���r�G���g �J���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Color ambient;

            /// <summary>
            /// �f�B�t���[�Y �J���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Color diffuse;

            /// <summary>
            /// �X�y�L�����[ �J���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            Color specular;

            /// <summary>
            /// �X�y�L�����[ �p���[���擾�܂��͐ݒ肵�܂��B
            /// </summary>
            float power;
        };
    }
}
