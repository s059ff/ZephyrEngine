#pragma once

#include "common.h"
#include "Enums.h"
#include "ShaderResourceView.h"
#include "RenderTargetView.h"
#include "DepthStencilView.h"

using namespace System;

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �e�N�X�`�� ���\�[�X��\���܂��B
        /// </summary>
        public ref class Texture2D
            : public INativeWrapper<zephyr::graphics::d3d11::Texture2D>
        {
        public:

            virtual ~Texture2D()
            {
                this->!Texture2D();
            }

            !Texture2D()
            {
                if (ResourceView != nullptr)
                {
                    delete ResourceView;
                    ResourceView = nullptr;
                }

                if (TargetView != nullptr)
                {
                    delete TargetView;
                    TargetView = nullptr;
                }

                if (DepthView != nullptr)
                {
                    delete DepthView;
                    DepthView = nullptr;
                }
            }

            /// <summary>
            /// �V������̃e�N�X�`�� ���\�[�X���쐬���܂��B
            /// </summary>
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            /// <param name="format">�e�N�Z���̃f�[�^�^�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Create(int width, int height, Format format, Accessibility access)
            {
                Native->Create(
                    width,
                    height,
                    (zephyr::graphics::d3d11::Format)format,
                    (zephyr::graphics::d3d11::Accessibility)access,
                    zephyr::graphics::d3d11::BufferBindFlags::ShaderResource);
                this->ResourceView->Native->Create(this->NativeRef);
            }

            /// <summary>
            /// �V�����e�N�X�`�� ���\�[�X���쐬���ď��������܂��B
            /// </summary>
            /// <param name="source">�e�N�X�`���̏����l�B</param> 
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            /// <param name="format">�e�N�Z���̃f�[�^�^�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            generic <typename T> where T : value struct
                void Create(array<T>^ source, int width, int height, Format format, Accessibility access)
            {
                pin_ptr<T> ptr = &source[0];
                this->Create(ptr, width, height, format, access);
            }

            /// <summary>
            /// �摜�t�@�C������e�N�X�`�� ���\�[�X���쐬���܂��B
            /// </summary>
            /// <param name="path">�t�@�C���p�X�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Create(String^ path, Accessibility access);

            /// <summary>
            /// �V�����e�N�X�`�� ���\�[�X���쐬���ď��������܂��B
            /// </summary>
            /// <param name="source">�e�N�X�`���̏����l�B</param> 
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            /// <param name="format">�e�N�Z���̃f�[�^�^�B</param> 
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Create(const void* source, int width, int height, Format format, Accessibility access)
            {
                Native->Create(
                    source,
                    width,
                    height,
                    (zephyr::graphics::d3d11::Format)format,
                    (zephyr::graphics::d3d11::Accessibility)access,
                    zephyr::graphics::d3d11::BufferBindFlags::ShaderResource);
                this->ResourceView->Native->Create(this->NativeRef);
            }

            /// <summary>
            /// �[�x�}�b�v �e�N�X�`�����쐬���܂��B
            /// </summary>
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            void CreateDepthMap(int width, int height)
            {
                Native->CreateDepthMap(width, height);
                this->ResourceView->Native->CreateDepthMapView(this->NativeRef);
                this->DepthView->Native->CreateDepthMapView(this->NativeRef);
            }

            /// <summary>
            /// �[�x�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="width">�e�N�X�`���̕��B</param> 
            /// <param name="height">�e�N�X�`���̍����B</param> 
            void CreateDepthStencil(int width, int height)
            {
                Native->CreateDepthStencil(width, height);
                this->DepthView->Native->Create(this->NativeRef);
            }

            /// <summary>
            /// ���\�[�X�����b�N���� CPU ���珑�����߂��Ԃɂ��܂��B
            /// </summary>
            /// <param name="access">���\�[�X�̃A�N�Z�X�\���B</param> 
            void Lock(Accessibility access)
            {
                Native->Lock((zephyr::graphics::d3d11::Accessibility)access);
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

            /// <summary>
            /// �V�����e�N�X�`�� ���\�[�X�����ׂď��������܂��B���\�[�X�����b�N����Ă��Ȃ��ꍇ�A���̃��\�b�h�͎��s���܂��B
            /// </summary>
            /// <param name="source">�㏑������l�B</param> 
            generic <typename T> where T : value struct void Write(array<T>^ source)
            {
                assert(sizeof(T) == Stride);
                assert(Native->width * Native->height == source->Length);

                pin_ptr<T> ptr = &source[0];
                memcpy(Native->locked_ptr, ptr, source->Length * sizeof(T));
            }

            /// <summary>
            /// �e�N�X�`���ɕ������������݂܂��B�T�C�Y�͕����ɍ��킹�ĕύX����܂��B
            /// </summary>
            /// <param name="font">�������ޕ����̃t�H���g�B</param> 
            /// <param name="charactor">�������ޕ����B</param> 
            void Print(Font^ font, wchar_t charactor)
            {
                Native->Print(*reinterpret_cast<zephyr::graphics::Font*>(font->NativePtr), charactor);
                this->ResourceView->Native->Create(this->NativeRef);
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

            RenderTargetView^ TargetView = gcnew RenderTargetView();

            DepthStencilView^ DepthView = gcnew DepthStencilView();
        };
    }
}
