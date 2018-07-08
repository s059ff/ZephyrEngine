#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �[�x�E�X�e���V���o�b�t�@ �X�e�[�g��\���܂��B
        /// </summary>
        public ref class DepthStencilState
            : public INativeWrapper<zephyr::graphics::d3d11::DepthStencilState>
        {
        public:

            /// <summary>
            /// �V�����u�����f�B���O �X�e�[�g���쐬���܂��B
            /// </summary>
            /// <param name="depthEnable">�[�x�o�b�t�@���g�p����ꍇ�� true�B</param> 
            /// <param name="stencilEnable">�X�e���V���o�b�t�@���g�p����ꍇ�� true�B</param> 
            /// <param name="depthWriteEnable">�[�x�o�b�t�@�ւ̏������݂�������ꍇ�� true�B</param> 
            void Create(bool depthEnable, bool stencilEnable, bool depthWriteEnable)
            {
                Native->Create(depthEnable, stencilEnable, depthWriteEnable);
            }
        };
    }
}
