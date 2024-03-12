#pragma once

#include "common.h"

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
            /// キーボードのボタンを表します。
            /// </summary>
            enum class KeyCode
            {
                A = (int)zephyr::input::Keyboard::KeyCode::A,
                B = (int)zephyr::input::Keyboard::KeyCode::B,
                C = (int)zephyr::input::Keyboard::KeyCode::C,
                D = (int)zephyr::input::Keyboard::KeyCode::D,
                E = (int)zephyr::input::Keyboard::KeyCode::E,
                F = (int)zephyr::input::Keyboard::KeyCode::F,
                G = (int)zephyr::input::Keyboard::KeyCode::G,
                H = (int)zephyr::input::Keyboard::KeyCode::H,
                I = (int)zephyr::input::Keyboard::KeyCode::I,
                J = (int)zephyr::input::Keyboard::KeyCode::J,
                K = (int)zephyr::input::Keyboard::KeyCode::K,
                L = (int)zephyr::input::Keyboard::KeyCode::L,
                M = (int)zephyr::input::Keyboard::KeyCode::M,
                N = (int)zephyr::input::Keyboard::KeyCode::N,
                O = (int)zephyr::input::Keyboard::KeyCode::O,
                P = (int)zephyr::input::Keyboard::KeyCode::P,
                Q = (int)zephyr::input::Keyboard::KeyCode::Q,
                R = (int)zephyr::input::Keyboard::KeyCode::R,
                S = (int)zephyr::input::Keyboard::KeyCode::S,
                T = (int)zephyr::input::Keyboard::KeyCode::T,
                U = (int)zephyr::input::Keyboard::KeyCode::U,
                V = (int)zephyr::input::Keyboard::KeyCode::V,
                W = (int)zephyr::input::Keyboard::KeyCode::W,
                X = (int)zephyr::input::Keyboard::KeyCode::X,
                Y = (int)zephyr::input::Keyboard::KeyCode::Y,
                Z = (int)zephyr::input::Keyboard::KeyCode::Z,
                F1 = (int)zephyr::input::Keyboard::KeyCode::F1,
                F2 = (int)zephyr::input::Keyboard::KeyCode::F2,
                F3 = (int)zephyr::input::Keyboard::KeyCode::F3,
                F4 = (int)zephyr::input::Keyboard::KeyCode::F4,
                F5 = (int)zephyr::input::Keyboard::KeyCode::F5,
                F6 = (int)zephyr::input::Keyboard::KeyCode::F6,
                F7 = (int)zephyr::input::Keyboard::KeyCode::F7,
                F8 = (int)zephyr::input::Keyboard::KeyCode::F8,
                F9 = (int)zephyr::input::Keyboard::KeyCode::F9,
                Left = (int)zephyr::input::Keyboard::KeyCode::Left,
                Right = (int)zephyr::input::Keyboard::KeyCode::Right,
                Up = (int)zephyr::input::Keyboard::KeyCode::Up,
                Down = (int)zephyr::input::Keyboard::KeyCode::Down,
                Escape = (int)zephyr::input::Keyboard::KeyCode::Escape,
                Tab = (int)zephyr::input::Keyboard::KeyCode::Tab,
                LeftShift = (int)zephyr::input::Keyboard::KeyCode::LeftShift,
                RightShift = (int)zephyr::input::Keyboard::KeyCode::RightShift,
                LeftCtrl = (int)zephyr::input::Keyboard::KeyCode::LeftCtrl,
                RightCtrl = (int)zephyr::input::Keyboard::KeyCode::RightCtrl,
                LeftAlt = (int)zephyr::input::Keyboard::KeyCode::LeftAlt,
                RightAlt = (int)zephyr::input::Keyboard::KeyCode::RightAlt,
                Space = (int)zephyr::input::Keyboard::KeyCode::Space,
                Enter = (int)zephyr::input::Keyboard::KeyCode::Enter,
                BackSpace = (int)zephyr::input::Keyboard::KeyCode::BackSpace,
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
            /// キーの状態を取得します。
            /// </summary>
            /// <param name="code">キーコード。</param>
            /// <returns>キーの状態。</returns>
            int GetKeyState(KeyCode code)
            {
                return Native->GetKeyState((zephyr::input::Keyboard::KeyCode)code);
            }

            /// <summary>
            /// コントローラが接続されているか調べます。
            /// </summary>
            bool IsConnected()
            {
                return Native->IsConnected();
            }
        };
    }
}
