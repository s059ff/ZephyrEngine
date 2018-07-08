#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �T���v���[ �X�e�[�g��\���܂��B
        /// </summary>
        public ref class SamplerState
            : public INativeWrapper<zephyr::graphics::dx11::SamplerState>
        {
        public:

            /// <summary>
            /// �T���v���[ �X�e�[�g���쐬���܂��B
            /// </summary>
            /// <param name="addressU">U ���W�̃A�h���b�V���O���[�h�B</param> 
            /// <param name="addressV">V ���W�̃A�h���b�V���O���[�h�B</param> 
            /// <param name="addressW">W ���W�̃A�h���b�V���O���[�h�B</param> 
            void Create(TextureAddressMode addressU, TextureAddressMode addressV, TextureAddressMode addressW)
            {
                Native->Create(
                    (zephyr::graphics::dx11::TextureAddressMode)addressU, 
                    (zephyr::graphics::dx11::TextureAddressMode)addressV, 
                    (zephyr::graphics::dx11::TextureAddressMode)addressW);
            }

            /// <summary>
            /// ��r�T���v���[ �X�e�[�g���쐬���܂��B
            /// </summary>
            void CreateComparator()
            {
                Native->CreateComparator();
            }
        };
    }
}
