#pragma once

#include "zephyr\array.h"
#include "zephyr\property.h"

#include "Interface.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        enum class ButtonState;
        enum class KeyCode;

        /// <summary>
        /// キーボードデバイスを表します。
        /// </summary>
        class Keyboard : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// このクラスの新しいインスタンスを初期化します。
            /// </summary>
            Keyboard() = default;

            /// <summary>
            /// インスタンスを破棄します。
            /// </summary>
            ~Keyboard();

            /// <summary>
            /// デバイスの状態を更新します。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update();

            /// <summary>
            /// キーの状態を取得します。
            /// </summary>
            /// <param name="key">キーコード。</param>
            /// <returns>キーの状態。</returns>
            ButtonState GetKeyState(KeyCode key);

            /// <summary>
            /// キーの状態を取得します。
            /// </summary>
            ButtonState operator [](KeyCode key)
            {
                return this->GetKeyState(key);
            }

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            READONLY_PROPERTY(bool, IsConnected, { return true; });

        private:

            // 初期化する
            void Create();

            // リセットする
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // キーの数
            enum { KeyCount = 256 };

            // 前回のキーボードの状態
            array<byte, KeyCount> prevKeyState;

            // キーボードの状態
            array<byte, KeyCount> keyState;
        };
    }
}
