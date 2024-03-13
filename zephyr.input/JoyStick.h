#pragma once

#include "zephyr\array.h"
#include "zephyr\string.h"

#include "Interface.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        /// <summary>
        /// ジョイスティックコントローラを表します。
        /// </summary>
        class JoyStick : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// ジョイスティックのボタンを表します。
            /// </summary>
            enum class ButtonCode
            {
                Button1,
                Button2,
                Button3,
                Button4,
                Button5,
                Button6,
                Button7,
                Button8,
                Button9,
                Button10,
                Button11,
                Button12,
                Button13,
                Button14,
                Button15,
                Button16,
                Button17,
                Button18,
                Button19,
                Button20,
                Button21,
                Button22,
                Button23,
                Button24,
                Button25,
                Button26,
                Button27,
                Button28,
                Button29,
                Button30,
                Button31,
                Button32,
            };

            /// <summary>
            /// ジョイスティックのハットスイッチを表します。
            /// </summary>
            enum class HatSwitchCode
            {
                Left,
                Right,
                Up,
                Down
            };

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
            int GetButtonState(ButtonCode code) const;

            /// <summary>
            /// ハットスイッチの状態を取得します。
            /// </summary>
            /// <param name="code">ハットスイッチコード。</param>
            int GetHatSwitchState(HatSwitchCode code) const;

            /// <summary>
            /// デバイスが接続されているか調べます。
            /// </summary>
            bool IsConnected() const;

        public:

            /// <summary>
            /// アナログスティック第 1 軸の値を取得します。
            /// </summary>
            const array<double, 2>& Axis1 = this->axis1;

            /// <summary>
            /// アナログスティック第 2 軸の値を取得します。
            /// </summary>
            const array<double, 2>& Axis2 = this->axis2;

            /// <summary>
            /// アナログスティック第 1 軸のX値を取得します。
            /// </summary>
            const double& Axis1X = this->axis1[0];

            /// <summary>
            /// アナログスティック第 1 軸のY値を取得します。
            /// </summary>
            const double& Axis1Y = this->axis1[1];

            /// <summary>
            /// アナログスティック第 2 軸のX値を取得します。
            /// </summary>
            const double& Axis2X = this->axis2[0];

            /// <summary>
            /// アナログスティック第 2 軸のY値を取得します。
            /// </summary>
            const double& Axis2Y = this->axis2[1];

            /// <summary>
            /// アナログスティックのデッドゾーンの大きさを 0 から 1 の範囲で指定します。
            /// </summary>
            double DeadZone;

            /// <summary>
            /// プロダクト名を取得します。
            /// </summary>
            const string& ProductName = this->product_name;

        private:

            // 作成する
            void Create();

            // リセットする
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // ボタン数
            enum { ButtonCount = 32 };

            // ハットスイッチ数
            enum { HatSwitchCount = 4 };

            // ボタンの状態 (未加工)
            array<byte, ButtonCount> raw_button_state, raw_button_state_prev;

            // ボタンの状態 (加工済み)
            array<int, ButtonCount> button_state;

            // ハットスイッチの状態 (未加工)
            array<bool, HatSwitchCount> raw_hatswitch_state, raw_hatswitch_state_prev;

            // ハットスイッチの状態 (加工済み)
            array<int, HatSwitchCount> hatswitch_state;

            // アナログスティック (1軸)
            array<double, 2> axis1;

            // アナログスティック (2軸)
            array<double, 2> axis2;

            // プロダクト名
            string product_name;
        };
    }
}
