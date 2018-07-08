#pragma once

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

namespace zephyr
{
    namespace input
    {
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
    }
}
