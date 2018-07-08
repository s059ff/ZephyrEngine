#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ���X�^���C�U�[ �X�e�[�g��\���܂��B
        /// </summary>
        public ref class RasterizerState
            : public INativeWrapper<zephyr::graphics::d3d11::RasterizerState>
        {
        public:

            /// <summary>
            /// ���X�^���C�U�[ �X�e�[�g���쐬���܂��B
            /// </summary>
            /// <param name="cullMode">�J�����O�̐ݒ�B</param> 
            /// <param name="fillMode">�h��Ԃ��̈�̐ݒ�B</param> 
            void Create(CullMode cullMode, FillMode fillMode)
            {
                Native->Create((zephyr::graphics::d3d11::CullMode)cullMode, (zephyr::graphics::d3d11::FillMode)fillMode);
            }
        };
    }
}
