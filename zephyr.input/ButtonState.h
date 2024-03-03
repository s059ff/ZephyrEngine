#pragma once

namespace zephyr
{
    namespace input
    {
        /// <summary>
        /// �{�^���̏�Ԃ�\���܂��B
        /// </summary>
        enum class ButtonState
        {
            /// <summary>
            /// �{�^���͗�����Ă��܂��B
            /// </summary>
            Released,

            /// <summary>
            /// �{�^���͉�����Ă��܂��B
            /// </summary>
            Pressed,

            /// <summary>
            /// �{�^���͍�������܂����B
            /// </summary>
            NowReleased,

            /// <summary>
            /// �{�^���͍�������܂����B
            /// </summary>
            NowPressed
        };

        namespace
        {
            // �{�^���̏�Ԃ��擾����
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
