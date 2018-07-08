#pragma once

#include "common.h"
#include "Enums.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// インスタンスバッファ リソースを表します。
        /// </summary>
        generic <typename I> where I : value struct
            public ref class InstanceBuffer
            : public INativeWrapper<zephyr::graphics::dx11::InstanceBuffer>
        {
        public:

            /// <summary>
            /// 空のインスタンスバッファを作成します。
            /// </summary>
            /// <param name="count">インスタンス数。</param>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(int count, Accessibility access)
            {
                Native->Create(sizeof(I), count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// 初期値を指定してインスタンスバッファを作成します。
            /// </summary>
            /// <param name="source">インスタンスデータ。</param>
            /// <param name="access">リソースのアクセシビリティ。</param>
            void Create(array<I>^ source, Accessibility access)
            {
                int count = source->Length;
                int stride = sizeof(I);
                pin_ptr<I> ptr = &source[0];
                Native->Create(ptr, stride, count, (zephyr::graphics::dx11::Accessibility)access);
            }

            /// <summary>
            /// 一つのインスタンスデータを読み取ります。インスタンスバッファがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="index">インスタンスのインデックス。</param>
            I Read(int index)
            {
                I v;
                memcpy(&v, Native->Access(index), sizeof(I));
                return v;
            }

            /// <summary>
            /// 一つのインスタンスデータを書き込みます。インスタンスバッファがロックされていない場合、このメソッドは失敗します。
            /// </summary>
            /// <param name="index">インスタンスのインデックス。</param>
            /// <param name="value">インスタンスデータ。</param>
            void Write(int index, I value)
            {
                memcpy(Native->Access(index), &value, sizeof(I));
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
            /// 一つ当たりのインスタンスのバイトサイズを取得します。
            /// </summary>
            property int Stride { int get() { return Native->stride; } }

            /// <summary>
            /// インスタンスバッファに格納されているインスタンスの数を取得します。
            /// </summary>
            property int Count { int get() { return Native->count; } }
        };
    }
}
