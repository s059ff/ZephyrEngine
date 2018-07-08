#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �V�F�[�_�̒萔�o�b�t�@�ƃv���O�������Ȃ��C���^�[�t�F�[�X�ł��B
        /// </summary>
        public ref class ConstantBuffer
            : public INativeWrapper<zephyr::graphics::d3d11::ConstantBuffer>
        {
        public:

            /// <summary>
            /// �V�F�[�_�̒萔�o�b�t�@�Ɠ����f�[�^�\�������\���̂��w�肵�āA�C���^�[�t�F�[�X���쐬���܂��B
            /// </summary>
            /// <typeparam name="T">�萔�o�b�t�@�̃f�[�^�^�B</typeparam> 
            /// <param name="source">�萔�o�b�t�@�̏����l�B</param> 
            generic <typename T> where T : value struct void Create(T source)
            {
                this->Create(static_cast<const void*>(&source), sizeof(T));
            }

            /// <summary>
            /// �V�F�[�_�̒萔�o�b�t�@�Ɠ����f�[�^�\�������z����w�肵�āA�C���^�[�t�F�[�X���쐬���܂��B
            /// </summary>
            /// <typeparam name="T">�萔�o�b�t�@�̃f�[�^�z��̌^�B</typeparam> 
            /// <param name="source">�萔�o�b�t�@�̏����l�B</param> 
            generic <typename T> where T : value struct void Create(array<T>^ source)
            {
                pin_ptr<T> ptr = &source[0];
                this->Create(static_cast<const void*>(ptr), sizeof(T) * source->Length);
            }

            /// <summary>
            /// �萔�o�b�t�@�̃o�C�g�T�C�Y���w�肵�āA�C���^�[�t�F�[�X���쐬���܂��B
            /// </summary>
            /// <param name="size">�萔�o�b�t�@�̃o�C�g�T�C�Y�B</param> 
            void Create(int size)
            {
                Native->Create(size);
            }

            /// <summary>
            /// �萔�o�b�t�@�̃o�C�g�T�C�Y�Ə����l���w�肵�āA�C���^�[�t�F�[�X���쐬���܂��B
            /// </summary>
            /// <param name="size">�萔�o�b�t�@�̃o�C�g�T�C�Y�B</param> 
            /// <param name="source">�萔�o�b�t�@�̏����l�B</param> 
            void Create(const void* source, int size)
            {
                Native->Create(source, size);
            }

            /// <summary>
            /// �萔�o�b�t�@���w�肵���l�ōX�V���܂��B
            /// </summary>
            /// <typeparam name="T">�萔�o�b�t�@�̃f�[�^�^�B</typeparam> 
            /// <param name="source">�萔�o�b�t�@�̍X�V�l�B</param> 
            generic <typename T> where T : value struct void Update(T source)
            {
                this->Update(static_cast<const void*>(&source));
            }

            /// <summary>
            /// �萔�o�b�t�@���w�肵���l�ōX�V���܂��B
            /// </summary>
            /// <typeparam name="T">�萔�o�b�t�@�̃f�[�^�z��̌^�B</typeparam> 
            /// <param name="source">�萔�o�b�t�@�̍X�V�l�B</param> 
            generic <typename T> where T : value struct void Update(array<T>^ source)
            {
                pin_ptr<T> ptr = &source[0];
                this->Update(static_cast<const void*>(ptr));
            }

            /// <summary>
            /// �萔�o�b�t�@���w�肵���l�ōX�V���܂��B
            /// </summary>
            /// <param name="source">�萔�o�b�t�@�̍X�V�l�������|�C���^�B</param> 
            void Update(const void* source)
            {
                Native->Update(static_cast<const void*>(source));
            }
        };
    }
}
