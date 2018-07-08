#pragma once

namespace zephyr
{
    namespace input
    {
        /// <summary>
        /// ボタンの状態を表します。
        /// </summary>
        enum class ButtonState
        {
            /// <summary>
            /// ボタンは離されています。
            /// </summary>
            Released,

            /// <summary>
            /// ボタンは押されています。
            /// </summary>
            Pressed,

            /// <summary>
            /// ボタンは今離されました。
            /// </summary>
            NowReleased,

            /// <summary>
            /// ボタンは今押されました。
            /// </summary>
            NowPressed
        };

        namespace
        {
            // ボタンの状態を取得する
            inline ButtonState getButtonState(bool now, bool prev)
            {
                if (now)
                {
                    return prev ? ButtonState::Pressed : ButtonState::NowPressed;
                }
                else
                {
                    return prev ? ButtonState::NowReleased : ButtonState::Released;
                }
            }
        }
    }
}
