#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// インデックスバッファ リソースを表します。
        /// </summary>
        public ref class IndexBuffer
            : public INativeWrapper<zephyr::graphics::dx11::IndexBuffer>
        {
        public:

            /// <summary>
            /// 静的な空のインデックスバッファを作成します。
            /// </summary>
            /// <typeparam name="count">インデックスデータ数。</typeparam>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(int count, Accessibility access)
            {
                Native->Create<int>(count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// 初期値を指定してインデックスバッファを作成します。
            /// </summary>
            /// <param name="source">インデックスデータ。</param>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(array<int>^ source, Accessibility access)
            {
                int count = source->Length;
                int stride = sizeof(int);
                pin_ptr<int> ptr = &source[0];
                Native->Create(ptr, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// 初期値を指定してインデックスバッファを作成します。
            /// </summary>
            /// <param name="source">頂点データ。</param>
            /// <param name="count">頂点の数。</param>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(const void* source, int count, Accessibility access)
            {
                int stride = sizeof(int);
                Native->Create(source, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// バッファからインデックスデータを読み取ります。インデックスバッファがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="index">読み取り先データのインデックス。</param>
            int Read(int index)
            {
                return Native->Read<int>(index);
            }

            /// <summary>
            /// インデックスデータをバッファに書き込みます。インデックスバッファがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="index">書き込み先のバッファにおけるインデックス。</param>
            /// <param name="value">書き込まれるインデックスデータ。</param>
            void Write(int index, int value)
            {
                Native->Write<int>(index, value);
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
