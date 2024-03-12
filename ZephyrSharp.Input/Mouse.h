#pragma once

#include "common.h"
#include "ButtonState.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// マウスデバイスを表します。
        /// </summary>
        public ref class Mouse
            : public INativeWrapper<zephyr::input::Mouse>
        {
        public:

            /// <summary>
            /// デバイスの状態を更新します。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update()
            {
                Native->Update();
            }

        public:

            /// <summary>
            /// マウスのクライアント座標系での X 座標を取得します。
            /// </summary>
            property int X { int get() { return Native->X; } };

            /// <summary>
            /// マウスのクライアント座標系での Y 座標を取得します。
            /// </summary>
            property int Y { int get() { return Native->Y; } };

            /// <summary>
            /// マウスの X 方向の移動量を取得します。
            /// </summary>
            property int MovementX { int get() { return Native->MovementX; } };

            /// <summary>
            /// マウスの Y 方向の移動量を取得します。
            /// </summary>
            property int MovementY { int get() { return Native->MovementY; } };

            /// <summary>
            /// マウスの Z 方向の移動量を取得します。
            /// </summary>
            property int MovementZ { int get() { return Native->MovementZ; } };

            /// <summary>
            /// マウスの左ボタンの状態を取得します。
            /// </summary>
            property ButtonState Left { ButtonState get() { return (ButtonState)Native->Left; } };

            /// <summary>
            /// マウスの右ボタンの状態を取得します。
            /// </summary>
            property ButtonState Right { ButtonState get() { return (ButtonState)Native->Right; } };

            /// <summary>
            /// マウスの右ボタンの状態を取得します。
            /// </summary>
            property ButtonState Center { ButtonState get() { return (ButtonState)Native->Center; } };

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            property bool IsConnected { bool get() { return Native->IsConnected; } }
        };
    }
}
