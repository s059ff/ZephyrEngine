#pragma once

#include "zephyr\array.h"
#include "zephyr\property.h"

#include "Interface.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        /// <summary>
        /// マウスデバイスを表します。
        /// </summary>
        class Mouse : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// マウスのボタンを表します。
            /// </summary>
            enum class ButtonCode
            {
                Left = 0,
                Right = 1,
                Center = 2
            };

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

            /// <summary>
            /// デバイスが接続されているか調べます。
            /// </summary>
            bool IsConnected() const;

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
            READONLY_PROPERTY(int, Left, { return this->button_state[(int)ButtonCode::Left]; });

            /// <summary>
            /// マウスの右ボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(int, Right, { return this->button_state[(int)ButtonCode::Right]; });

            /// <summary>
            /// マウスの中央ボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(int, Center, { return this->button_state[(int)ButtonCode::Center]; });

        private:

            // 初期化する
            void Create();

            // リセットする
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // ボタン数
            enum { ButtonCount = 3 };

            // マウスの位置
            long mouseX, mouseY;

            // マウスの移動量
            long moveX, moveY, moveZ;

            // ボタンの状態 (未加工)
            array<byte, ButtonCount> raw_button_state, raw_button_state_prev;

            // ボタンの状態 (加工済み)
            array<int, ButtonCount> button_state;
        };
    }
}
