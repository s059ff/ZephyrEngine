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
        /// �����_�����O���s���܂��B
        /// </summary>
        public ref class GraphicsDeviceContext
            : public INativeSingletonWrapper<zephyr::graphics::dx11::GraphicsDeviceContext>
        {
        public:

            /// <summary>
            /// �p�C�v���C���Ɋ֘A�t�����Ă��邷�ׂẴ��\�[�X���A���o�C���h���܂��B
            /// </summary>
            void UnbindAllResources()
            {
                Native->UnbindAllResources();
            }

            /// <summary>
            /// �o�b�N�o�b�t�@���N���A���܂��B
            /// </summary>
            /// <param name="color">�N���A����F�B</param> 
            void Clear(Color color)
            {
                Native->Clear(reinterpret_cast<zephyr::graphics::Color&>(color));
            }

            /// <summary>
            /// �o�b�N�o�b�t�@���N���A���܂��B
            /// </summary>
            /// <param name="color">�N���A����F�B</param> 
            void Clear(ColorCode color)
            {
                Native->Clear(reinterpret_cast<zephyr::graphics::ColorCode&>(color));
            }

            /// <summary>
            /// �����_�����O�Ɏg�p����o�[�e�b�N�X �V�F�[�_��ݒ肵�܂��B
            /// </summary>
            /// <param name="shader">�o�[�e�b�N�X �V�F�[�_�B</param> 
            void SetVertexShader(VertexShader^ shader)
            {
                Native->SetVertexShader(shader->NativeRef);
            }

            /// <summary>
            /// �����_�����O�Ɏg�p����W�I���g�� �V�F�[�_��ݒ肵�܂��B
            /// </summary>
            /// <param name="shader">�W�I���g�� �V�F�[�_�B</param> 
            void SetGeometryShader(GeometryShader^ shader)
            {
                Native->SetGeometryShader(shader->NativeRef);
            }

            /// <summary>
            /// �����_�����O�Ɏg�p����s�N�Z�� �V�F�[�_��ݒ肵�܂��B
            /// </summary>
            /// <param name="shader">�s�N�Z�� �V�F�[�_�B</param> 
            void SetPixelShader(PixelShader^ shader)
            {
                Native->SetPixelShader(shader->NativeRef);
            }

            /// <summary>
            /// �����_�����O�Ɏg�p����o�[�e�b�N�X �o�b�t�@��ݒ肵�܂��B
            /// </summary>
            /// <param name="buffer">���_�o�b�t�@�B</param> 
            /// <param name="slot">�X���b�g�ԍ��B</param> 
            generic <typename V> where V : value class void SetVertexBuffer(VertexBuffer<V>^ buffer, int slot)
            {
                Native->SetVertexBuffer(buffer->NativeRef, slot);
            }

            /// <summary>
            /// �����_�����O�Ɏg�p����C���f�b�N�X �o�b�t�@��ݒ肵�܂��B
            /// </summary>
            /// <param name="buffer">���_�o�b�t�@�B</param> 
            void SetIndexBuffer(IndexBuffer^ buffer)
            {
                Native->SetIndexBuffer(buffer->NativeRef);
            }

            /// <summary>
            /// �����_�����O�Ɏg�p����C���X�^���X �o�b�t�@��ݒ肵�܂��B
            /// </summary>
            /// <param name="buffer">�C���X�^���X �o�b�t�@�B</param> 
            /// <param name="slot">�X���b�g�ԍ��B</param> 
            generic <typename I> where I : value class void SetInstanceBuffer(InstanceBuffer<I>^ buffer, int slot)
            {
                Native->SetInstanceBuffer(buffer->NativeRef, slot);
            }

            /// <summary>
            /// ���_�o�b�t�@�̃��C�A�E�g��ݒ肵�܂��B
            /// </summary>
            /// <param name="layout">���_���C�A�E�g�B</param> 
            void SetVertexLayout(VertexLayout^ layout)
            {
                Native->SetVertexLayout(layout->NativeRef);
            }

            /// <summary>
            /// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�̏��Ԃ̋K������ݒ肵�܂��B
            /// </summary>
            /// <param name="topology">���_�f�[�^ �g�|���W�[�B</param> 
            void SetPrimitiveTopology(PrimitiveTopology topology)
            {
                Native->SetPrimitiveTopology((zephyr::graphics::dx11::PrimitiveTopology)topology);
            }

            /// <summary>
            /// �u�����f�B���O �X�e�[�g�������_�����O �p�C�v���C���ɓK�p���܂��B
            /// </summary>
            /// <param name="state">�u�����f�B���O �X�e�[�g�B</param> 
            void SetBlendState(BlendState^ state)
            {
                Native->SetBlendState(state->NativeRef);
            }

            /// <summary>
            /// ���X�^���C�U �X�e�[�g�������_�����O �p�C�v���C���ɓK�p���܂��B
            /// </summary>
            /// <param name="state">���X�^���C�U �X�e�[�g�B</param> 
            void SetRasterizerState(RasterizerState^ state)
            {
                Native->SetRasterizerState(state->NativeRef);
            }

            /// <summary>
            /// �[�x�E�X�e���V�� �X�e�[�g�������_�����O �p�C�v���C���ɓK�p���܂��B
            /// </summary>
            /// <param name="state">�[�x�E�X�e���V�� �X�e�[�g�B</param> 
            void SetDepthStencilState(DepthStencilState^ state)
            {
                Native->SetDepthStencilState(state->NativeRef);
            }

            /// <summary>
            /// �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@��ݒ肵�܂��B
            /// </summary>
            /// <param name="target">�����_�����O�^�[�Q�b�g �e�N�X�`���B</param> 
            /// <param name="depth">�[�x�o�b�t�@ �e�N�X�`���B</param> 
            void SetRenderTargetAndDepthStencil(Texture2D^ target, Texture2D^ depth)
            {
                if ((target != nullptr) && (depth != nullptr))
                {
                    Native->SetRenderTargetAndDepthStencil(target->TargetView->NativeRef, depth->DepthView->NativeRef);
                }
                else
                {
                    if (target != nullptr)
                    {
                        Native->SetRenderTargetAndDepthStencil(target->TargetView->NativeRef, nullptr);
                    }
                    else if (depth != nullptr)
                    {
                        Native->SetRenderTargetAndDepthStencil(nullptr, depth->DepthView->NativeRef);
                    }
                }
            }

            /// <summary>
            /// �����_�����O�^�[�Q�b�g�Ɛ[�x�o�b�t�@���f�t�H���g�ɐݒ肵�܂��B
            /// </summary>
            void ResetRenderTargetAndDepthStencil()
            {
                Native->ResetRenderTargetAndDepthStencil();
            }

            /// <summary>
            /// �r���[�|�[�g�ϊ��s���ݒ肵�܂��B
            /// </summary>
            /// <param name="width">�r���[�|�[�g���B</param> 
            /// <param name="height">�r���[�|�[�g�����B</param> 
            void SetViewport(int width, int height)
            {
                Native->SetViewport(width, height);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@���g�p�����ɁA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="vertexCount">�����_�����O�Ɏg�p����钸�_�̐��B</param> 
            void Draw(int vertexCount)
            {
                Native->Draw(vertexCount);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@���g�p�����ɁA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="vertexCount">�����_�����O�Ɏg�p����钸�_�̐��B</param> 
            /// <param name="startVertexLocation">�����_�����O�Ɏg�p����钸�_�̊J�n�ʒu�B</param> 
            void Draw(int vertexCount, int startVertexLocation)
            {
                Native->Draw(vertexCount, startVertexLocation);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="indexCount">�����_�����O�Ɏg�p�����C���f�b�N�X�̐��B</param> 
            void DrawIndexed(int indexCount)
            {
                Native->DrawIndexed(indexCount);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="indexCount">�����_�����O�Ɏg�p�����C���f�b�N�X�̐��B</param> 
            /// <param name="startIndexLocation">�����_�����O�Ɏg�p�����C���f�b�N�X�̊J�n�ʒu�B</param> 
            void DrawIndexed(int indexCount, int startIndexLocation)
            {
                Native->DrawIndexed(indexCount, startIndexLocation);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="indexCount">�����_�����O�Ɏg�p�����C���f�b�N�X�̐��B</param> 
            /// <param name="startIndexLocation">�����_�����O�Ɏg�p�����C���f�b�N�X�̊J�n�ʒu�B</param> 
            /// <param name="baseVertexLocation">�C���f�b�N�X�̒l�ƁA���ۂ̒��_�f�[�^�ԍ��Ƃ̃I�t�Z�b�g�B</param> 
            void DrawIndexed(int indexCount, int startIndexLocation, int baseVertexLocation)
            {
                Native->DrawIndexed(indexCount, startIndexLocation, baseVertexLocation);
            }

            /// <summary>
            /// �C���X�^���X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="vertexCountPerInstance">�����_�����O�Ɏg�p����� 1 �C���X�^���X������̒��_�̐��B</param> 
            /// <param name="instanceCount">�����_�����O�Ɏg�p�����C���X�^���X�̐��B</param> 
            void DrawInstanced(int vertexCountPerInstance, int instanceCount)
            {
                Native->DrawInstanced(vertexCountPerInstance, instanceCount);
            }

            /// <summary>
            /// �C���X�^���X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="vertexCountPerInstance">�����_�����O�Ɏg�p����� 1 �C���X�^���X������̒��_�̐��B</param> 
            /// <param name="instanceCount">�����_�����O�Ɏg�p�����C���X�^���X�̐��B</param> 
            /// <param name="startVertexLocation">�����_�����O�Ɏg�p����钸�_�̊J�n�ʒu�B</param> 
            void DrawInstanced(int vertexCountPerInstance, int instanceCount, int startVertexLocation)
            {
                Native->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation);
            }

            /// <summary>
            /// �C���X�^���X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="vertexCountPerInstance">�����_�����O�Ɏg�p����� 1 �C���X�^���X������̒��_�̐��B</param> 
            /// <param name="instanceCount">�����_�����O�Ɏg�p�����C���X�^���X�̐��B</param> 
            /// <param name="startVertexLocation">�����_�����O�Ɏg�p����钸�_�̊J�n�ʒu�B</param> 
            /// <param name="startInstanceLocation">�����_�����O�Ɏg�p�����C���X�^���X�̊J�n�ʒu�B</param> 
            void DrawInstanced(int vertexCountPerInstance, int instanceCount, int startVertexLocation, int startInstanceLocation)
            {
                Native->DrawInstanced(vertexCountPerInstance, instanceCount, startVertexLocation, startInstanceLocation);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@�ƃC���X�^���X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="indexCountPerInstance">�����_�����O�Ɏg�p����� 1 �C���X�^���X������̃C���f�b�N�X�̐��B</param> 
            /// <param name="instanceCount">�����_�����O�Ɏg�p�����C���X�^���X�̐��B</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@�ƃC���X�^���X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="indexCountPerInstance">�����_�����O�Ɏg�p����� 1 �C���X�^���X������̃C���f�b�N�X�̐��B</param> 
            /// <param name="instanceCount">�����_�����O�Ɏg�p�����C���X�^���X�̐��B</param> 
            /// <param name="startIndexLocation">�����_�����O�Ɏg�p�����C���f�b�N�X�̊J�n�ʒu�B</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@�ƃC���X�^���X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="indexCountPerInstance">�����_�����O�Ɏg�p����� 1 �C���X�^���X������̃C���f�b�N�X�̐��B</param> 
            /// <param name="instanceCount">�����_�����O�Ɏg�p�����C���X�^���X�̐��B</param> 
            /// <param name="startIndexLocation">�����_�����O�Ɏg�p�����C���f�b�N�X�̊J�n�ʒu�B</param> 
            /// <param name="baseVertexLocation">�C���f�b�N�X�̒l�ƁA���ۂ̒��_�f�[�^�ԍ��Ƃ̃I�t�Z�b�g�B</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation);
            }

            /// <summary>
            /// �C���f�b�N�X�o�b�t�@�ƃC���X�^���X�o�b�t�@���g�p���āA�����_�����O�����s���܂��B
            /// </summary>
            /// <param name="indexCountPerInstance">�����_�����O�Ɏg�p����� 1 �C���X�^���X������̃C���f�b�N�X�̐��B</param> 
            /// <param name="instanceCount">�����_�����O�Ɏg�p�����C���X�^���X�̐��B</param> 
            /// <param name="startIndexLocation">�����_�����O�Ɏg�p�����C���f�b�N�X�̊J�n�ʒu�B</param> 
            /// <param name="baseVertexLocation">�C���f�b�N�X�̒l�ƁA���ۂ̒��_�f�[�^�ԍ��Ƃ̃I�t�Z�b�g�B</param> 
            /// <param name="startInstanceLocation">�����_�����O�Ɏg�p�����C���X�^���X�̊J�n�ʒu�B</param> 
            void DrawIndexedInstanced(int indexCountPerInstance, int instanceCount, int startIndexLocation, int baseVertexLocation, int startInstanceLocation)
            {
                Native->DrawIndexedInstanced(indexCountPerInstance, instanceCount, startIndexLocation, baseVertexLocation, startInstanceLocation);
            }

            /// <summary>
            /// �X���b�v�`�F�C�����������āA�o�b�t�@����ʂɕ\�����܂��B
            /// </summary>
            void Present()
            {
                Native->Present();
            }

        public:

            /// <summary>
            /// ���̃N���X�̃V���O���g�� �C���X�^���X���擾���܂��B
            /// </summary>
            static GraphicsDeviceContext^ Instance = gcnew GraphicsDeviceContext();

        private:

            GraphicsDeviceContext() {}
        };
    }
}
