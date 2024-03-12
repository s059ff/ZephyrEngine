#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// シェーダの定数バッファとプログラムをつなぐインターフェースです。
        /// </summary>
        public ref class ConstantBuffer
            : public INativeWrapper<zephyr::graphics::dx11::ConstantBuffer>
        {
        public:

            /// <summary>
            /// シェーダの定数バッファと同じデータ構造を持つ構造体を指定して、インターフェースを作成します。
            /// </summary>
            /// <typeparam name="T">定数バッファのデータ型。</typeparam> 
            /// <param name="source">定数バッファの初期値。</param> 
            generic <typename T> where T : value struct void Create(T source)
            {
                this->Create(static_cast<const void*>(&source), sizeof(T));
            }

            /// <summary>
            /// シェーダの定数バッファと同じデータ構造を持つ配列を指定して、インターフェースを作成します。
            /// </summary>
            /// <typeparam name="T">定数バッファのデータ配列の型。</typeparam> 
            /// <param name="source">定数バッファの初期値。</param> 
            generic <typename T> where T : value struct void Create(array<T>^ source)
            {
                pin_ptr<T> ptr = &source[0];
                this->Create(static_cast<const void*>(ptr), sizeof(T) * source->Length);
            }

            /// <summary>
            /// 定数バッファのバイトサイズを指定して、インターフェースを作成します。
            /// </summary>
            /// <param name="size">定数バッファのバイトサイズ。</param> 
            void Create(int size)
            {
                Native->Create(size);
            }

            /// <summary>
            /// 定数バッファのバイトサイズと初期値を指定して、インターフェースを作成します。
            /// </summary>
            /// <param name="size">定数バッファのバイトサイズ。</param> 
            /// <param name="source">定数バッファの初期値。</param> 
            void Create(const void* source, int size)
            {
                Native->Create(source, size);
            }

            /// <summary>
            /// 定数バッファを指定した値で更新します。
            /// </summary>
            /// <typeparam name="T">定数バッファのデータ型。</typeparam> 
            /// <param name="source">定数バッファの更新値。</param> 
            generic <typename T> where T : value struct void Update(T source)
            {
                this->Update(static_cast<const void*>(&source));
            }

            /// <summary>
            /// 定数バッファを指定した値で更新します。
            /// </summary>
            /// <typeparam name="T">定数バッファのデータ配列の型。</typeparam> 
            /// <param name="source">定数バッファの更新値。</param> 
            generic <typename T> where T : value struct void Update(array<T>^ source)
            {
                pin_ptr<T> ptr = &source[0];
                this->Update(static_cast<const void*>(ptr));
            }

            /// <summary>
            /// 定数バッファを指定した値で更新します。
            /// </summary>
            /// <param name="source">定数バッファの更新値を示すポインタ。</param> 
            void Update(const void* source)
            {
                Native->Update(static_cast<const void*>(source));
            }
        };
    }
}
