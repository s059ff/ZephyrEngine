#pragma once

#include <Unknwn.h>

#include "assert.h"

namespace zephyr
{
    /// <summary>
    /// COM オブジェクトを管理するスマートポインタです。
    /// </summary>
    template <typename I> class com_ptr
    {
        using interface_t = IUnknown;

    public:

        /// <summary>
        /// デフォルトのコンストラクタです。
        /// </summary>
        com_ptr() = default;

        /// <summary>
        /// リソースをオブジェクトに格納します。
        /// </summary>
        explicit com_ptr(interface_t* p)
            : p(p)
        {
        }

        /// <summary>
        /// リソースを解放し、オブジェクトを破棄します。
        /// </summary>
        ~com_ptr()
        {
            this->reset();
        }

        /// <summary>
        /// このオブジェクトはコピーできません。
        /// </summary>
        com_ptr(com_ptr&) = delete;

        /// <summary>
        /// リソースの所有権を移動します。
        /// </summary>
        /// <param name="src">リソースの所有元オブジェクト。</param>
        com_ptr(com_ptr&& src)
            : p(src.p)
        {
            src.p = nullptr;
        }

        /// <summary>
        /// リソースを解放します。
        /// </summary>
        void operator =(nullptr_t)
        {
            this->reset();
        }

        /// <summary>
        /// このオブジェクトはコピーできません。
        /// </summary>
        void operator =(com_ptr&) = delete;

        /// <summary>
        /// リソースの所有権を移動します。
        /// </summary>
        /// <param name="src">リソースの所有元オブジェクト。</param>
        void operator =(com_ptr&& src)
        {
            this->reset(src.p);
            src.p = nullptr;
        }

        /// <summary>
        /// リソースへの生のポインタを取得します。
        /// </summary>
        I* const get() const
        {
            return reinterpret_cast<I*>(this->p);
        }

        /// <summary>
        /// 現在のリソースを解放し、新たにリソースを設定します。
        /// </summary>
        /// <param name="p">新しく所有するリソース。</param>
        void reset(interface_t* p)
        {
            if (this->p != p)
            {
                if (this->p != nullptr)
                {
                    this->p->Release();
                    this->p = nullptr;
                }
                this->p = p;
            }
        }

        /// <summary>
        /// リソースを解放します。
        /// </summary>
        void reset()
        {
            if (this->p != nullptr)
            {
                this->p->Release();
            }
            this->p = nullptr;
        }

        /// <summary>
        /// リソースを所有しているか調べます。
        /// </summary>
        bool available() const { return this->p != nullptr; }

        /// <summary>
        /// リソースを所有していないか調べます。
        /// </summary>
        bool expired() const { return this->p == nullptr; }

        /// <summary>
        /// リソースを主有するポインタのアドレスを取得します。
        /// </summary>
        I** operator& ()
        {
            assert(this->p == nullptr);
            return&reinterpret_cast<I*&>(this->p);
        }

        /// <summary>
        /// リソースのメソッドを呼び出します。
        /// </summary>
        I* operator-> () const
        {
            assert(this->available());
            return get();
        }

        /// <summary>
        /// リソースへの参照を取得します。
        /// </summary>
        I& operator* () const
        {
            assert(this->p != nullptr);
            return *reinterpret_cast<I*>(this->p);
        }
        
        /// <summary>
        /// リソースへの生のポインタを取得します。
        /// </summary>
        __declspec(property(get = get, put = reset)) I* ptr;

    private:

        interface_t* p = nullptr;
    };
}
