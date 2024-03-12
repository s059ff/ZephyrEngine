#pragma once

#include "common.h"

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
            /// マウスのボタンを表します。
            /// </summary>
            enum class ButtonCode
            {
                Left = (int)zephyr::input::Mouse::ButtonCode::Left,
                Right = (int)zephyr::input::Mouse::ButtonCode::Right,
                Center = (int)zephyr::input::Mouse::ButtonCode::Center
            };

        public:

            /// <summary>
            /// デバイスの状態を更新します。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update()
            {
                Native->Update();
            }

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            bool IsConnected()
            {
                return Native->IsConnected();
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
            property int Left { int get() { return Native->Left; } };

            /// <summary>
            /// マウスの右ボタンの状態を取得します。
            /// </summary>
            property int Right { int get() { return Native->Right; } };

            /// <summary>
            /// マウスの右ボタンの状態を取得します。
            /// </summary>
            property int Center { int get() { return Native->Center; } };
        };
    }
}
