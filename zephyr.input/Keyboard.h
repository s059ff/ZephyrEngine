#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include "zephyr\array.h"
#include "zephyr\property.h"

#include "Interface.h"

struct IDirectInputDevice8A;

namespace zephyr
{
    namespace input
    {
        /// <summary>
        /// キーボードデバイスを表します。
        /// </summary>
        class Keyboard : public Interface<IDirectInputDevice8A>
        {
        public:

            /// <summary>
            /// キーボードのボタンを表します。
            /// </summary>
            enum class KeyCode
            {
                A = DIK_A,
                B = DIK_B,
                C = DIK_C,
                D = DIK_D,
                E = DIK_E,
                F = DIK_F,
                G = DIK_G,
                H = DIK_H,
                I = DIK_I,
                J = DIK_J,
                K = DIK_K,
                L = DIK_L,
                M = DIK_M,
                N = DIK_N,
                O = DIK_O,
                P = DIK_P,
                Q = DIK_Q,
                R = DIK_R,
                S = DIK_S,
                T = DIK_T,
                U = DIK_U,
                V = DIK_V,
                W = DIK_W,
                X = DIK_X,
                Y = DIK_Y,
                Z = DIK_Z,
                F1 = DIK_F1,
                F2 = DIK_F2,
                F3 = DIK_F3,
                F4 = DIK_F4,
                F5 = DIK_F5,
                F6 = DIK_F6,
                F7 = DIK_F7,
                F8 = DIK_F8,
                F9 = DIK_F9,
                F10 = DIK_F10,
                F11 = DIK_F11,
                F12 = DIK_F12,
                Left = DIK_LEFT,
                Right = DIK_RIGHT,
                Up = DIK_UP,
                Down = DIK_DOWN,
                Escape = DIK_ESCAPE,
                Tab = DIK_TAB,
                LeftShift = DIK_LSHIFT,
                RightShift = DIK_RSHIFT,
                LeftCtrl = DIK_LCONTROL,
                RightCtrl = DIK_RCONTROL,
                LeftAlt = DIK_LALT,
                RightAlt = DIK_RALT,
                Space = DIK_SPACE,
                Enter = DIK_RETURN,
                BackSpace = DIK_BACKSPACE,
            };

        public:

            /// <summary>
            /// このクラスの新しいインスタンスを初期化します。
            /// </summary>
            Keyboard() = default;

            /// <summary>
            /// インスタンスを破棄します。
            /// </summary>
            ~Keyboard();

            /// <summary>
            /// デバイスの状態を更新します。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update();

            /// <summary>
            /// キーの状態を取得します。
            /// </summary>
            /// <param name="code">キーコード。</param>
            /// <returns>キーの状態。</returns>
            int GetKeyState(KeyCode code) const;

            /// <summary>
            /// デバイスが接続されているか調べます。
            /// </summary>
            bool IsConnected() const;

        private:

            // 初期化する
            void Create();

            // リセットする
            void Reset(IDirectInputDevice8A* ptr = nullptr);

        private:

            // キーの数
            enum { KeyCount = 256 };

            // キーボードの状態 (未加工)
            array<byte, KeyCount> raw_key_state, raw_key_state_prev;

            // キーボードの状態 (加工済み)
            array<int, KeyCount> key_state;
        };
    }
}
