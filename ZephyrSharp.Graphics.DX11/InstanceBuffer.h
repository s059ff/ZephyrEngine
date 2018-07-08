#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �C���X�^���X�o�b�t�@ ���\�[�X��\���܂��B
        /// </summary>
        generic <typename I> where I : value struct
            public ref class InstanceBuffer
            : public INativeWrapper<zephyr::graphics::dx11::InstanceBuffer>
        {
        public:

            /// <summary>
            /// ��̃C���X�^���X�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="count">�C���X�^���X���B</param>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(int count, Accessibility access)
            {
                Native->Create(sizeof(I), count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// �����l���w�肵�ăC���X�^���X�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="source">�C���X�^���X�f�[�^�B</param>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(array<I>^ source, Accessibility access)
            {
                int count = source->Length;
                int stride = sizeof(I);
                pin_ptr<I> ptr = &source[0];
                Native->Create(ptr, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// ��̃C���X�^���X�f�[�^��ǂݎ��܂��B�C���X�^���X�o�b�t�@�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="index">�C���X�^���X�̃C���f�b�N�X�B</param>
            I Read(int index)
            {
                I v;
                memcpy(&v, Native->Access(index), sizeof(I));
                return v;
            }

            /// <summary>
            /// ��̃C���X�^���X�f�[�^���������݂܂��B�C���X�^���X�o�b�t�@�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="index">�C���X�^���X�̃C���f�b�N�X�B</param>
            /// <param name="value">�C���X�^���X�f�[�^�B</param>
            void Write(int index, I value)
            {
                memcpy(Native->Access(index), &value, sizeof(I));
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
            /// �������̃C���X�^���X�̃o�C�g�T�C�Y���擾���܂��B
            /// </summary>
            property int Stride { int get() { return Native->stride; } }

            /// <summary>
            /// �C���X�^���X�o�b�t�@�Ɋi�[����Ă���C���X�^���X�̐����擾���܂��B
            /// </summary>
            property int Count { int get() { return Native->count; } }
        };
    }
}
