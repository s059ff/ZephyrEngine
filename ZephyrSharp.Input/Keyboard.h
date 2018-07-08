#pragma once

#include "common.h"
#include "ButtonState.h"
#include "KeyCode.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// キーボードデバイスを表します。
        /// </summary>
        public ref class Keyboard : public INativeWrapper<zephyr::input::Keyboard>
        {
        public:

            /// <summary>
            /// デバイスの状態を更新します。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update()
            {
                Native->Update();
            }

            /// <summary>
            /// キーの状態を取得します。
            /// </summary>
            /// <param name="key">キーコード。</param>
            /// <returns>キーの状態。</returns>
            ButtonState GetKeyState(KeyCode key)
            {
                return (ButtonState)Native->GetKeyState((zephyr::input::KeyCode)key);
            }

            /// <summary>
            /// キーの状態を取得します。
            /// </summary>
            property ButtonState default [KeyCode]
            {
                ButtonState get(KeyCode key) { return this->GetKeyState(key); }
            }

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            property bool IsConnected { bool get() { return Native->IsConnected; } };
        };
    }
}
