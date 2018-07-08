#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// 頂点バッファ リソースを表します。
        /// </summary>
        generic <typename V> where V : value struct
            public ref class VertexBuffer
            : public INativeWrapper<zephyr::graphics::dx11::VertexBuffer>
        {
        public:

            /// <summary>
            /// 空の頂点バッファを作成します。
            /// </summary>
            /// <param name="count">頂点数。</param>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(int count, Accessibility access)
            {
                Native->Create(sizeof(V), count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// 初期値を指定して頂点バッファを作成します。
            /// </summary>
            /// <param name="source">頂点データ。</param>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(array<V>^ source, Accessibility access)
            {
                int count = source->Length;
                int stride = sizeof(V);
                pin_ptr<V> ptr = &source[0];
                Native->Create(ptr, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// 初期値を指定して頂点バッファを作成します。
            /// </summary>
            /// <param name="source">頂点データ。</param>
            /// <param name="count">頂点の数。</param>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(const void* source, int count, Accessibility access)
            {
                int stride = sizeof(V);
                Native->Create(source, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// 一つの頂点データを読み取ります。頂点バッファがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="index">頂点のインデックス。</param>
            V Read(int index)
            {
                V v;
                memcpy(&v, Native->Access(index), sizeof(V));
                return v;
            }

            /// <summary>
            /// 一つの頂点データを書き込みます。頂点バッファがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="index">頂点のインデックス。</param>
            /// <param name="value">頂点データ。</param>
            void Write(int index, V value)
            {
                memcpy(Native->Access(index), &value, sizeof(V));
            }

            /// <summary>
            /// リソースをロックして、読み書きが可能な状態にします。
            /// </summary>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Lock(Accessibility access)
            {
                Native->Lock((zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// リソースをアンロックして、描画可能な状態にします。
            /// </summary>
            void Unlock()
            {
                Native->Unlock();
            }

        public:

            /// <summary>
            /// 一つ当たりの頂点のバイトサイズを取得します。
            /// </summary>
            property int Stride { int get() { return Native->stride; } }

            /// <summary>
            /// 頂点バッファに格納されている頂点の数を取得します。
            /// </summary>
            property int Count { int get() { return Native->count; } }
        };
    }
}
