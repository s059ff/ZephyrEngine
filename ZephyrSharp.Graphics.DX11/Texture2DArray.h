#pragma once

#include "common.h"
#include "Enums.h"
#include "ShaderResourceView.h"

using namespace System;

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �e�N�X�`�� ���\�[�X��\���܂��B
        /// </summary>
        public ref class Texture2DArray
            : public INativeWrapper<zephyr::graphics::dx11::Texture2DArray>
        {
        public:

            virtual ~Texture2DArray()
            {
                this->!Texture2DArray();
            }

            !Texture2DArray()
            {
                if (ResourceView != nullptr)
                {
                    delete ResourceView;
                    ResourceView = nullptr;
                }
            }

            /// <summary>
            /// �V������̃e�N�X�`�� ���\�[�X���쐬���܂��B
            /// </summary>
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            /// <param name="count">�e�N�X�`���̐��B</param> 
            /// <param name="format">�e�N�Z���̃f�[�^�^�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Create(int width, int height, int count, Format format, Accessibility access)
            {
                Native->Create(
                    width,
                    height,
                    count,
                    (zephyr::graphics::dx11::Format)format,
                    (zephyr::graphics::dx11::Accessibility)access,
                    zephyr::graphics::dx11::BufferBindFlags::ShaderResource);
                this->ResourceView->Native->Create(this->NativeRef);
            }

            /// <summary>
            /// �V�����e�N�X�`�� ���\�[�X���쐬���ď��������܂��B
            /// </summary>
            /// <param name="source">�e�N�X�`���̏����l�B</param> 
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            /// <param name="count">�e�N�X�`���̐��B</param> 
            /// <param name="format">�e�N�Z���̃f�[�^�^�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            generic <typename T> where T : value struct
                void Create(array<T>^ source, int width, int height, int count, Format format, Accessibility access)
            {
                pin_ptr<T> ptr = &source[0];
                this->Create(ptr, width, height, count, format, access);
            }

            /// <summary>
            /// �V�����e�N�X�`�� ���\�[�X���쐬���ď��������܂��B
            /// </summary>
            /// <param name="source">�e�N�X�`���̏����l�B</param> 
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            /// <param name="count">�e�N�X�`���̐��B</param> 
            /// <param name="format">�e�N�Z���̃f�[�^�^�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Create(const void* source, int width, int height, int count, Format format, Accessibility access)
            {
                Native->Create(
                    source,
                    width,
                    height,
                    count,
                    (zephyr::graphics::dx11::Format)format,
                    (zephyr::graphics::dx11::Accessibility)access,
                    zephyr::graphics::dx11::BufferBindFlags::ShaderResource);
                this->ResourceView->Native->Create(this->NativeRef);
            }

            /// <summary>
            /// �摜�t�@�C������e�N�X�`�� ���\�[�X���쐬���܂��B
            /// </summary>
            /// <param name="path">.dds �`���t�@�C���p�X�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Create(String^ path, Accessibility access);

            /// <summary>
            /// �摜�t�@�C������e�N�X�`�� ���\�[�X���쐬���܂��B
            /// </summary>
            /// <param name="paths">.dds �`���t�@�C���p�X�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Create(array<String^>^ paths, Accessibility access);

            /// <summary>
            /// �摜�t�@�C������L���[�u �e�N�X�`�� ���\�[�X���쐬���܂��B
            /// </summary>
            /// <param name="path">.dds �`���t�@�C���p�X�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void CreateCubeMap(String^ path, Accessibility access);

            /// <summary>
            /// �V�����L���[�u �e�N�X�`�� ���\�[�X���쐬���ď��������܂��B
            /// </summary>
            /// <param name="source">�e�N�X�`���̏����l�B</param> 
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            /// <param name="format">�e�N�Z���̃f�[�^�^�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void CreateCubeMap(const void* source, int width, int height, Format format, Accessibility access)
            {
                Native->CreateCubeMap(
                    source,
                    width,
                    height,
                    (zephyr::graphics::dx11::Format)format,
                    (zephyr::graphics::dx11::Accessibility)access,
                    zephyr::graphics::dx11::BufferBindFlags::ShaderResource);
                this->ResourceView->Native->Create(this->NativeRef);
            }

            /// <summary>
            /// ���\�[�X�����b�N���� CPU ���珑�����߂��Ԃɂ��܂��B
            /// </summary>
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            /// <param name="index">���b�N����e�N�X�`���̃C���f�b�N�X�B</param> 
            void Lock(Accessibility access, int index)
            {
                Native->Lock((zephyr::graphics::dx11::Accessibility)access, index);
            }

            /// <summary>
            /// ���\�[�X���A�����b�N���܂��B
            /// </summary>
            void Unlock()
            {
                Native->Unlock();
            }

            /// <summary>
            /// �e�N�Z���f�[�^��ǂݎ��܂��B���\�[�X�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="x">�ǂݎ��e�N�Z���� X ���W�B</param> 
            /// <param name="y">�ǂݎ��e�N�Z���� Y ���W�B</param> 
            generic <typename T> T Read(int x, int y)
            {
                assert(sizeof(T) == Stride);

                T value;
                memcpy(&value, Native->Access(x, y), sizeof(T));

                return value;
            }

            /// <summary>
            /// �e�N�Z���f�[�^���������݂܂��B���\�[�X�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="x">�������ݐ�e�N�Z���� X ���W�B</param> 
            /// <param name="y">�������ݐ�e�N�Z���� Y ���W�B</param> 
            generic <typename T> void Write(int x, int y, T value)
            {
                assert(sizeof(T) == Stride);

                memcpy(Native->Access(x, y), &value, sizeof(T));
            }

        public:

            /// <summary>
            /// �e�N�X�`���̕����擾���܂��B
            /// </summary>
            property int Width
            {
                int get() { return Native->width; }
            }

            /// <summary>
            /// �e�N�X�`���̍������擾���܂��B
            /// </summary>
            property int Height
            {
                int get() { return Native->height; }
            }

            /// <summary>
            /// �e�N�X�`���̐����擾���܂��B
            /// </summary>
            property int Length
            {
                int get() { return Native->length; }
            }

            /// <summary>
            /// �e�N�Z���T�C�Y���擾���܂��B
            /// </summary>
            property int Stride
            {
                int get() { return Native->stride; }
            }

            /// <summary>
            /// ���b�N���ꂽ���\�[�X�̃������A�h���X���擾���܂��B
            /// </summary>
            property void* LockedPtr
            {
                void* get()
                {
                    return Native->locked_ptr;
                }
            }

        internal:

            ShaderResourceView^ ResourceView = gcnew ShaderResourceView();
        };
    }
}
