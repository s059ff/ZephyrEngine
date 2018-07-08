#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Input
    {
        /// <summary>
        /// �{�^���̏�Ԃ�\���܂��B
        /// </summary>
        public enum class ButtonState
        {
            /// <summary>
            /// �{�^���͗�����Ă��܂��B
            /// </summary>
            Released = (int)zephyr::input::ButtonState::Released,

            /// <summary>
            /// �{�^���͉�����Ă��܂��B
            /// </summary>
            Pressed = (int)zephyr::input::ButtonState::Pressed,

            /// <summary>
            /// �{�^���͍�������܂����B
            /// </summary>
            NowReleased = (int)zephyr::input::ButtonState::NowReleased,

            /// <summary>
            /// �{�^���͍�������܂����B
            /// </summary>
            NowPressed = (int)zephyr::input::ButtonState::NowPressed
        };
    }
}
