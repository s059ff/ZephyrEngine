#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �u�����f�B���O �X�e�[�g��\���܂��B
        /// </summary>
        public ref class BlendState 
            : public INativeWrapper<zephyr::graphics::dx11::BlendState>
        {
        public:

            /// <summary>
            /// �u�����h�����Ȃ��u�����f�B���O �X�e�[�g���쐬���܂��B
            /// </summary>
            /// <param name="operation">( BlendOperation::None �ɂ��邱�� )</param> 
            void Create(BlendOperation operation)
            {
                Native->Create((zephyr::graphics::dx11::BlendOperation)operation);
            }

            /// <summary>
            /// �V�����u�����f�B���O �X�e�[�g���쐬���܂��B
            /// </summary>
            /// <param name="operation">���Z���@�B</param> 
            /// <param name="srcFactor">�s�N�Z�� �V�F�[�_���o�͂����F���ɑ΂���W���B</param> 
            /// <param name="destFactor">�����_�����O �^�[�Q�b�g����ǂݎ�����F���ɑ΂���W���B</param> 
            void Create(BlendOperation operation, BlendFactor srcFactor, BlendFactor destFactor)
            {
                Native->Create(
                    (zephyr::graphics::dx11::BlendOperation)operation,
                    (zephyr::graphics::dx11::BlendFactor)srcFactor,
                    (zephyr::graphics::dx11::BlendFactor)destFactor);
            }
        };
    }
}
