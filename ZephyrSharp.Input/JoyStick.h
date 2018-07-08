#pragma once

#include "common.h"
#include "ButtonState.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// ジョイスティックコントローラを表します。
        /// </summary>
        public ref class JoyStick
            : public INativeWrapper<zephyr::input::JoyStick>
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
            /// ボタンの状態を取得します。
            /// </summary>
            /// <param name="id">ボタンの ID 。</param>
            ButtonState GetButtonState(int id)
            {
                return (ButtonState)Native->GetButtonState(id);
            }

            /// <summary>
            /// ボタンの状態を取得します。
            /// </summary>
            property ButtonState default[int]
            {
                ButtonState get(int id) { return this->GetButtonState(id); }
            }

        public:

            /// <summary>
            /// アナログスティック第 1 軸の X 軸の値を取得します。
            /// </summary>
            property double AxisX { double get() { return Native->AxisX; } }

            /// <summary>
            /// アナログスティック第 1 軸の Y 軸の値を取得します。
            /// </summary>
            property double AxisY { double get() { return Native->AxisY; } }

            /// <summary>
            /// アナログスティック第 2 軸の X 軸の値を取得します。
            /// </summary>
            property double SubAxisX { double get() { return Native->SubAxisX; } }

            /// <summary>
            /// アナログスティック第 2 軸の Y 軸の値を取得します。
            /// </summary>
            property double SubAxisY { double get() { return Native->SubAxisY; } }

            /// <summary>
            /// POV スイッチの左方向のボタンの状態を取得します。
            /// </summary>
            property ButtonState Left { ButtonState get() { return (ButtonState)Native->Left; } }

            /// <summary>
            /// POV スイッチの右方向のボタンの状態を取得します。
            /// </summary>
            property ButtonState Right { ButtonState get() { return (ButtonState)Native->Right; } }

            /// <summary>
            /// POV スイッチの上方向のボタンの状態を取得します。
            /// </summary>
            property ButtonState Up { ButtonState get() { return (ButtonState)Native->Up; } }

            /// <summary>
            /// POV スイッチの下方向のボタンの状態を取得します。
            /// </summary>
            property ButtonState Down { ButtonState get() { return (ButtonState)Native->Down; } }

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            property bool IsConnected { bool get() { return Native->IsConnected; } }

            /// <summary>
            /// アナログスティックのデッドゾーンの大きさを 0 から 1 の範囲で指定します。
            /// </summary>
            property double DeadZone
            {
                double get() { return Native->DeadZone; }
                void set(double value) { Native->DeadZone = value; }
            }
        };
    }
}
