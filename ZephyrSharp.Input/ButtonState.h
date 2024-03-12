#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// ボタンの状態を表します。
        /// </summary>
        public enum class ButtonState
        {
            /// <summary>
            /// ボタンは離されています。
            /// </summary>
            Released = (int)zephyr::input::ButtonState::Released,

            /// <summary>
            /// ボタンは押されています。
            /// </summary>
            Pressed = (int)zephyr::input::ButtonState::Pressed,

            /// <summary>
            /// ボタンは今離されました。
            /// </summary>
            NowReleased = (int)zephyr::input::ButtonState::NowReleased,

            /// <summary>
            /// ボタンは今押されました。
            /// </summary>
            NowPressed = (int)zephyr::input::ButtonState::NowPressed
        };
    }
}
