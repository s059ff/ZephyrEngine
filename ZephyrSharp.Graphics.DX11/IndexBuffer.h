#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �C���f�b�N�X�o�b�t�@ ���\�[�X��\���܂��B
        /// </summary>
        public ref class IndexBuffer
            : public INativeWrapper<zephyr::graphics::dx11::IndexBuffer>
        {
        public:

            /// <summary>
            /// �ÓI�ȋ�̃C���f�b�N�X�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <typeparam name="count">�C���f�b�N�X�f�[�^���B</typeparam>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(int count, Accessibility access)
            {
                Native->Create<int>(count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// �����l���w�肵�ăC���f�b�N�X�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="source">�C���f�b�N�X�f�[�^�B</param>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(array<int>^ source, Accessibility access)
            {
                int count = source->Length;
                int stride = sizeof(int);
                pin_ptr<int> ptr = &source[0];
                Native->Create(ptr, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// �����l���w�肵�ăC���f�b�N�X�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="source">���_�f�[�^�B</param>
            /// <param name="count">���_�̐��B</param>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(const void* source, int count, Accessibility access)
            {
                int stride = sizeof(int);
                Native->Create(source, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// �o�b�t�@����C���f�b�N�X�f�[�^��ǂݎ��܂��B�C���f�b�N�X�o�b�t�@�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="index">�ǂݎ���f�[�^�̃C���f�b�N�X�B</param>
            int Read(int index)
            {
                return Native->Read<int>(index);
            }

            /// <summary>
            /// �C���f�b�N�X�f�[�^���o�b�t�@�ɏ������݂܂��B�C���f�b�N�X�o�b�t�@�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="index">�������ݐ�̃o�b�t�@�ɂ�����C���f�b�N�X�B</param>
            /// <param name="value">�������܂��C���f�b�N�X�f�[�^�B</param>
            void Write(int index, int value)
            {
                Native->Write<int>(index, value);
            }

            /// <summary>
            /// ���\�[�X�����b�N���āA�ǂݏ������\�ȏ�Ԃɂ��܂��B
            /// </summary>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Lock(Accessibility access)
            {
                Native->Lock((zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// ���\�[�X���A�����b�N���āA�`��\�ȏ�Ԃɂ��܂��B
            /// </summary>
            void Unlock()
            {
                Native->Unlock();
            }

        public:

            /// <summary>
            /// �������̒��_�̃o�C�g�T�C�Y���擾���܂��B
            /// </summary>
            property int Stride { int get() { return Native->stride; } }

            /// <summary>
            /// ���_�o�b�t�@�Ɋi�[����Ă��钸�_�̐����擾���܂��B
            /// </summary>
            property int Count { int get() { return Native->count; } }
        };
    }
}
