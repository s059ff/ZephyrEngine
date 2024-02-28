#pragma once

#include "common.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "PixelShader.h"
#include "VertexLayout.h"
#include "BlendState.h"
#include "RatserizerState.h"
#include "DepthStencilState.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �O���t�B�b�N�X ���\�[�X�̍쐬���s���܂��B
        /// </summary>
        public ref class GraphicsDevice
            : public INativeSingletonWrapper<zephyr::graphics::dx11::GraphicsDevice>
        {
        public:

            /// <summary>
            /// �E�B���h�E���[�h�ŃV�X�e�������������܂��B
            /// </summary>
            /// <param name="window">�����_�����O���s�����C�� �E�B���h�E�B</param> 
            void Create(Window^ window)
            {
                Native->Create(*reinterpret_cast<zephyr::graphics::Window*>(window->NativePtr), false);
            }

            /// <summary>
            /// �E�B���h�E���[�h�ŃV�X�e�������������܂��B
            /// </summary>
            /// <param name="window">�����_�����O���s�����C�� �E�B���h�E�B</param> 
            /// <param name="fullscreen">�t���X�N���[���ɂ���ꍇ�� true �B</param> 
            void Create(Window^ window, bool fullscreen)
            {
                Native->Create(*reinterpret_cast<zephyr::graphics::Window*>(window->NativePtr), fullscreen);
            }

        public:

            /// <summary>
            /// ���̃N���X�̃V���O���g�� �C���X�^���X���擾���܂��B
            /// </summary>
            static GraphicsDevice^ Instance = gcnew GraphicsDevice();

        private:

            GraphicsDevice() {}
        };
    }
}
