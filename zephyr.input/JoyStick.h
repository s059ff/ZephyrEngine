#pragma once

#include "zephyr\array.h"
#include "zephyr\property.h"

#include "Interface.h"
#include "ButtonCode.h"
#include "ButtonState.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        enum class ButtonState;

        /// <summary>
        /// ジョイスティックコントローラを表します。
        /// </summary>
        class JoyStick : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// このクラスの新しいインスタンスを初期化します。
            /// </summary>
            JoyStick() = default;

            /// <summary>
            /// インスタンスを破棄します。
            /// </summary>
            ~JoyStick();

            /// <summary>
            /// デバイスの状態を更新します。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update();

            /// <summary>
            /// ボタンの状態を取得します。
            /// </summary>
            /// <param name="code">ボタンコード。</param>
            ButtonState GetButtonState(ButtonCode code) const;

			/// <summary>
			/// ボタンの長押し時間を取得します。
			/// </summary>
			/// <param name="code">ボタンコード。</param>
			/// <returns>ボタンが押されて続けているフレーム数。</returns>
			int GetPressTimeLength(ButtonCode code) const;

            /// <summary>
            /// ボタンの状態を取得します。
            /// </summary>
            ButtonState operator [](ButtonCode code) const
            {
                return this->GetButtonState(code);
            }

        public:

            /// <summary>
            /// アナログスティック第 1 軸の X 軸の値を取得します。
            /// </summary>
            const double& AxisX = this->axisX;

            /// <summary>
            /// アナログスティック第 1 軸の Y 軸の値を取得します。
            /// </summary>
            const double& AxisY = this->axisY;

            /// <summary>
            /// アナログスティック第 2 軸の X 軸の値を取得します。
            /// </summary>
            const double& SubAxisX = this->subAxisX;

            /// <summary>
            /// アナログスティック第 2 軸の Y 軸の値を取得します。
            /// </summary>
            const double& SubAxisY = this->subAxisY;

            /// <summary>
            /// POV スイッチの左方向のボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(ButtonState, Left, { return getButtonState(this->povLeft, this->prevPovLeft); });

            /// <summary>
            /// POV スイッチの右方向のボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(ButtonState, Right, { return getButtonState(this->povRight, this->prevPovRight); });

            /// <summary>
            /// POV スイッチの上方向のボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(ButtonState, Up, { return getButtonState(this->povUp, this->prevPovUp); });

            /// <summary>
            /// POV スイッチの下方向のボタンの状態を取得します。
            /// </summary>
            READONLY_PROPERTY(ButtonState, Down, { return getButtonState(this->povDown, this->prevPovDown); });

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            __declspec(property(get = isConnected)) bool IsConnected;

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            bool isConnected() const;

            /// <summary>
            /// アナログスティックのデッドゾーンの大きさを 0 から 1 の範囲で指定します。
            /// </summary>
            double DeadZone;

        private:

            // 作成する
            void Create();

            // リセットする
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // ボタン数
            enum { ButtonCount = 32 };

            // 現在のボタンの状態
            array<byte, ButtonCount> buttonState;

            // 直前のボタンの状態
            array<byte, ButtonCount> prevButtonState;

			// ボタンが押されている合計時間
			array<int, ButtonCount> pressTimeLength;

            // 現在のPOVスイッチの状態
            bool povLeft, povRight, povUp, povDown;

            // 直前のPOVスイッチの状態
            bool prevPovLeft, prevPovRight, prevPovUp, prevPovDown;

            // アナログスティック
            double axisX, axisY;

            // サブアナログスティック
            double subAxisX, subAxisY;
        };
    }
}
