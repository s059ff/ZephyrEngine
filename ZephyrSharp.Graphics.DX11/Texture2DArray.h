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
        /// テクスチャ リソースを表します。
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
            /// 新しく空のテクスチャ リソースを作成します。
            /// </summary>
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            /// <param name="count">テクスチャの数。</param> 
            /// <param name="format">テクセルのデータ型。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
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
            /// 新しくテクスチャ リソースを作成して初期化します。
            /// </summary>
            /// <param name="source">テクスチャの初期値。</param> 
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            /// <param name="count">テクスチャの数。</param> 
            /// <param name="format">テクセルのデータ型。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
            generic <typename T> where T : value struct
                void Create(array<T>^ source, int width, int height, int count, Format format, Accessibility access)
            {
                pin_ptr<T> ptr = &source[0];
                this->Create(ptr, width, height, count, format, access);
            }

            /// <summary>
            /// 新しくテクスチャ リソースを作成して初期化します。
            /// </summary>
            /// <param name="source">テクスチャの初期値。</param> 
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            /// <param name="count">テクスチャの数。</param> 
            /// <param name="format">テクセルのデータ型。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
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
            /// 画像ファイルからテクスチャ リソースを作成します。
            /// </summary>
            /// <param name="path">.dds 形式ファイルパス。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
            void Create(String^ path, Accessibility access);

            /// <summary>
            /// 画像ファイルからテクスチャ リソースを作成します。
            /// </summary>
            /// <param name="paths">.dds 形式ファイルパス。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
            void Create(array<String^>^ paths, Accessibility access);

            /// <summary>
            /// 画像ファイルからキューブ テクスチャ リソースを作成します。
            /// </summary>
            /// <param name="path">.dds 形式ファイルパス。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
            void CreateCubeMap(String^ path, Accessibility access);

            /// <summary>
            /// 新しくキューブ テクスチャ リソースを作成して初期化します。
            /// </summary>
            /// <param name="source">テクスチャの初期値。</param> 
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            /// <param name="format">テクセルのデータ型。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
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
            /// リソースをロックして CPU から書き込める状態にします。
            /// </summary>
            /// <param name="access">リソースのアクセス可能性。</param> 
            /// <param name="index">ロックするテクスチャのインデックス。</param> 
            void Lock(Accessibility access, int index)
            {
                Native->Lock((zephyr::graphics::dx11::Accessibility)access, index);
            }

            /// <summary>
            /// リソースをアンロックします。
            /// </summary>
            void Unlock()
            {
                Native->Unlock();
            }

            /// <summary>
            /// テクセルデータを読み取ります。リソースがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="x">読み取るテクセルの X 座標。</param> 
            /// <param name="y">読み取るテクセルの Y 座標。</param> 
            generic <typename T> T Read(int x, int y)
            {
                assert(sizeof(T) == Stride);

                T value;
                memcpy(&value, Native->Access(x, y), sizeof(T));

                return value;
            }

            /// <summary>
            /// テクセルデータを書き込みます。リソースがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="x">書きこみ先テクセルの X 座標。</param> 
            /// <param name="y">書きこみ先テクセルの Y 座標。</param> 
            generic <typename T> void Write(int x, int y, T value)
            {
                assert(sizeof(T) == Stride);

                memcpy(Native->Access(x, y), &value, sizeof(T));
            }

        public:

            /// <summary>
            /// テクスチャの幅を取得します。
            /// </summary>
            property int Width
            {
                int get() { return Native->width; }
            }

            /// <summary>
            /// テクスチャの高さを取得します。
            /// </summary>
            property int Height
            {
                int get() { return Native->height; }
            }

            /// <summary>
            /// テクスチャの数を取得します。
            /// </summary>
            property int Length
            {
                int get() { return Native->length; }
            }

            /// <summary>
            /// テクセルサイズを取得します。
            /// </summary>
            property int Stride
            {
                int get() { return Native->stride; }
            }

            /// <summary>
            /// ロックされたリソースのメモリアドレスを取得します。
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
