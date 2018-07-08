#pragma once

#include "zephyr\property.h"

#include "Interface.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        enum class ButtonState;

        /// <summary>
        /// マウスデバイスを表します。
        /// </summary>
        class Mouse : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// このクラスの新しいインスタンスを初期化します。
            /// </summary>
            Mouse() = default;

            /// <summary>
            /// インスタンスを破棄します。
            /// </summary>
            ~Mouse();

            /// <summary>
            /// デバイスの状態を更新します。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update();

        public:

            /// <summary>
            /// マウスのスクリーン座標系での X 座標を取得します。
            /// </summary>
            READONLY_PROPERTY(int, X, { return this->mouseX; });

            /// <summary>
            /// マウスのスクリーン座標系での Y 座標を取得します。
            /// </summary>
            READONLY_PROPERTY(int, Y, { return this->mouseY; });

            /// <summary>
            /// マウスの X 方向の移動量を取得します。
            /// </summary>
            READONLY_PROPERTY(int, MovementX, { return this->moveX; });

            /// <summary>
            /// マウスの Y 方向の移動量を取得します。
            /// </summary>
            READONLY_PROPERTY(int, MovementY, { return this->moveY; });

            /// <summary>
            /// マウスの Z 方向の移動量を取得します。
            /// </summary>
            READONLY_PROPERTY(int, MovementZ, { return this->moveZ; });

            /// <summary>
            /// マウスの左ボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(ButtonState, Left, ;);

            /// <summary>
            /// マウスの右ボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(ButtonState, Right, ;);

            /// <summary>
            /// マウスの中央ボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(ButtonState, Center, ;);

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            __declspec(property(get = isConnected)) bool IsConnected;

            /// <summary>
            /// マウスが接続されているか調べます。
            /// </summary>
            bool isConnected();

        private:

            // 初期化する
            void Create();

            // リセットする
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // マウスの位置
            long mouseX, mouseY;

            // マウスの移動量
            long moveX, moveY, moveZ;

            // ボタンの状態
            bool left, right, center;

            // 前フレームのボタンの状態
            bool prevLeft, prevRight, prevCenter;
        };
    }
}
