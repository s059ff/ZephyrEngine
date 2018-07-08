#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// ���_�o�b�t�@ ���\�[�X��\���܂��B
        /// </summary>
        generic <typename V> where V : value struct
            public ref class VertexBuffer
            : public INativeWrapper<zephyr::graphics::dx11::VertexBuffer>
        {
        public:

            /// <summary>
            /// ��̒��_�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="count">���_���B</param>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(int count, Accessibility access)
            {
                Native->Create(sizeof(V), count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// �����l���w�肵�Ē��_�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="source">���_�f�[�^�B</param>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(array<V>^ source, Accessibility access)
            {
                int count = source->Length;
                int stride = sizeof(V);
                pin_ptr<V> ptr = &source[0];
                Native->Create(ptr, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// �����l���w�肵�Ē��_�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="source">���_�f�[�^�B</param>
            /// <param name="count">���_�̐��B</param>
            /// <param name="access">���\�[�X�̃A�N�Z�V�r���e�B�B</param>
            void Create(const void* source, int count, Accessibility access)
            {
                int stride = sizeof(V);
                Native->Create(source, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// ��̒��_�f�[�^��ǂݎ��܂��B���_�o�b�t�@�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="index">���_�̃C���f�b�N�X�B</param>
            V Read(int index)
            {
                V v;
                memcpy(&v, Native->Access(index), sizeof(V));
                return v;
            }

            /// <summary>
            /// ��̒��_�f�[�^���������݂܂��B���_�o�b�t�@�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="index">���_�̃C���f�b�N�X�B</param>
            /// <param name="value">���_�f�[�^�B</param>
            void Write(int index, V value)
            {
                memcpy(Native->Access(index), &value, sizeof(V));
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
