#pragma once

#include "common.h"

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
            /// ジョイスティックのボタンを表します。
            /// </summary>
            enum class ButtonCode
            {
                Button1 = (int)zephyr::input::JoyStick::ButtonCode::Button1,
                Button2 = (int)zephyr::input::JoyStick::ButtonCode::Button2,
                Button3 = (int)zephyr::input::JoyStick::ButtonCode::Button3,
                Button4 = (int)zephyr::input::JoyStick::ButtonCode::Button4,
                Button5 = (int)zephyr::input::JoyStick::ButtonCode::Button5,
                Button6 = (int)zephyr::input::JoyStick::ButtonCode::Button6,
                Button7 = (int)zephyr::input::JoyStick::ButtonCode::Button7,
                Button8 = (int)zephyr::input::JoyStick::ButtonCode::Button8,
                Button9 = (int)zephyr::input::JoyStick::ButtonCode::Button9,
                Button10 = (int)zephyr::input::JoyStick::ButtonCode::Button10,
                Button11 = (int)zephyr::input::JoyStick::ButtonCode::Button11,
                Button12 = (int)zephyr::input::JoyStick::ButtonCode::Button12,
                Button13 = (int)zephyr::input::JoyStick::ButtonCode::Button13,
                Button14 = (int)zephyr::input::JoyStick::ButtonCode::Button14,
                Button15 = (int)zephyr::input::JoyStick::ButtonCode::Button15,
                Button16 = (int)zephyr::input::JoyStick::ButtonCode::Button16,
                Button17 = (int)zephyr::input::JoyStick::ButtonCode::Button17,
                Button18 = (int)zephyr::input::JoyStick::ButtonCode::Button18,
                Button19 = (int)zephyr::input::JoyStick::ButtonCode::Button19,
                Button20 = (int)zephyr::input::JoyStick::ButtonCode::Button20,
                Button21 = (int)zephyr::input::JoyStick::ButtonCode::Button21,
                Button22 = (int)zephyr::input::JoyStick::ButtonCode::Button22,
                Button23 = (int)zephyr::input::JoyStick::ButtonCode::Button23,
                Button24 = (int)zephyr::input::JoyStick::ButtonCode::Button24,
                Button25 = (int)zephyr::input::JoyStick::ButtonCode::Button25,
                Button26 = (int)zephyr::input::JoyStick::ButtonCode::Button26,
                Button27 = (int)zephyr::input::JoyStick::ButtonCode::Button27,
                Button28 = (int)zephyr::input::JoyStick::ButtonCode::Button28,
                Button29 = (int)zephyr::input::JoyStick::ButtonCode::Button29,
                Button30 = (int)zephyr::input::JoyStick::ButtonCode::Button30,
                Button31 = (int)zephyr::input::JoyStick::ButtonCode::Button31,
                Button32 = (int)zephyr::input::JoyStick::ButtonCode::Button32
            };

            /// <summary>
            /// ジョイスティックのハットスイッチを表します。
            /// </summary>
            enum class HatSwitchCode
            {
                Left = (int)zephyr::input::JoyStick::HatSwitchCode::Left,
                Right = (int)zephyr::input::JoyStick::HatSwitchCode::Right,
                Up = (int)zephyr::input::JoyStick::HatSwitchCode::Up,
                Down = (int)zephyr::input::JoyStick::HatSwitchCode::Down
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
            /// ボタンの状態を取得します。
            /// </summary>
            /// <param name="code">ボタンコード。</param>
            int GetButtonState(ButtonCode code)
            {
                return Native->GetButtonState((zephyr::input::JoyStick::ButtonCode)code);
            }

            /// <summary>
            /// ハットスイッチの状態を取得します。
            /// </summary>
            /// <param name="code">ハットスイッチコード。</param>
            int GetHatSwitchState(HatSwitchCode code)
            {
                return Native->GetHatSwitchState((zephyr::input::JoyStick::HatSwitchCode)code);
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
            /// アナログスティック第 1 軸の値を取得します。
            /// </summary>
            property System::Tuple<double, double>^ Axis1
            {
                System::Tuple<double, double>^ get()
                {
                    return gcnew System::Tuple<double, double>(Native->Axis1[0], Native->Axis1[1]);
                }
            }

            /// <summary>
            /// アナログスティック第 1 軸の X 軸の値を取得します。
            /// </summary>
            property double Axis1X { double get() { return Native->Axis1X; } }

            /// <summary>
            /// アナログスティック第 1 軸の Y 軸の値を取得します。
            /// </summary>
            property double Axis1Y { double get() { return Native->Axis1Y; } }

            /// <summary>
            /// アナログスティック第 2 軸の値を取得します。
            /// </summary>
            property System::Tuple<double, double>^ Axis2
            {
                System::Tuple<double, double>^ get()
                {
                    return gcnew System::Tuple<double, double>(Native->Axis2[0], Native->Axis2[1]);
                }
            }

            /// <summary>
            /// アナログスティック第 2 軸の X 軸の値を取得します。
            /// </summary>
            property double Axis2X { double get() { return Native->Axis2X; } }

            /// <summary>
            /// アナログスティック第 2 軸の Y 軸の値を取得します。
            /// </summary>
            property double Axis2Y { double get() { return Native->Axis2Y; } }

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
