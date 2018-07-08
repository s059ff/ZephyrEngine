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
        /// テクスチャ リソースを表します。
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
            /// 新しく空のテクスチャ リソースを作成します。
            /// </summary>
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            /// <param name="format">テクセルのデータ型。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
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
            /// 新しくテクスチャ リソースを作成して初期化します。
            /// </summary>
            /// <param name="source">テクスチャの初期値。</param> 
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            /// <param name="format">テクセルのデータ型。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
            generic <typename T> where T : value struct
                void Create(array<T>^ source, int width, int height, Format format, Accessibility access)
            {
                pin_ptr<T> ptr = &source[0];
                this->Create(ptr, width, height, format, access);
            }

            /// <summary>
            /// 画像ファイルからテクスチャ リソースを作成します。
            /// </summary>
            /// <param name="path">ファイルパス。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
            void Create(String^ path, Accessibility access);

            /// <summary>
            /// 新しくテクスチャ リソースを作成して初期化します。
            /// </summary>
            /// <param name="source">テクスチャの初期値。</param> 
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            /// <param name="format">テクセルのデータ型。</param> 
            /// <param name="access">リソースのアクセス可能性。</param> 
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
            /// 深度マップ テクスチャを作成します。
            /// </summary>
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            void CreateDepthMap(int width, int height)
            {
                Native->CreateDepthMap(width, height);
                this->ResourceView->Native->CreateDepthMapView(this->NativeRef);
                this->DepthView->Native->CreateDepthMapView(this->NativeRef);
            }

            /// <summary>
            /// 深度バッファを作成します。
            /// </summary>
            /// <param name="width">テクスチャの幅。</param> 
            /// <param name="height">テクスチャの高さ。</param> 
            void CreateDepthStencil(int width, int height)
            {
                Native->CreateDepthStencil(width, height);
                this->DepthView->Native->Create(this->NativeRef);
            }

            /// <summary>
            /// リソースをロックして CPU から書き込める状態にします。
            /// </summary>
            /// <param name="access">リソースのアクセス可能性。</param> 
            void Lock(Accessibility access)
            {
                Native->Lock((zephyr::graphics::d3d11::Accessibility)access);
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

            /// <summary>
            /// 新しくテクスチャ リソースをすべて書き換えます。リソースがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="source">上書きする値。</param> 
            generic <typename T> where T : value struct void Write(array<T>^ source)
            {
                assert(sizeof(T) == Stride);
                assert(Native->width * Native->height == source->Length);

                pin_ptr<T> ptr = &source[0];
                memcpy(Native->locked_ptr, ptr, source->Length * sizeof(T));
            }

            /// <summary>
            /// テクスチャに文字を書きこみます。サイズは文字に合わせて変更されます。
            /// </summary>
            /// <param name="font">書きこむ文字のフォント。</param> 
            /// <param name="charactor">書きこむ文字。</param> 
            void Print(Font^ font, wchar_t charactor)
            {
                Native->Print(*reinterpret_cast<zephyr::graphics::Font*>(font->NativePtr), charactor);
                this->ResourceView->Native->Create(this->NativeRef);
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

            RenderTargetView^ TargetView = gcnew RenderTargetView();

            DepthStencilView^ DepthView = gcnew DepthStencilView();
        };
    }
}
