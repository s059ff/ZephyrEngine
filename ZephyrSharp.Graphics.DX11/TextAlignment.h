#pragma once

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// �e�L�X�g�̑������@��\���܂��B
        /// </summary>
        [System::FlagsAttribute]
        public enum class TextAlignment
        {
            /// <summary>
            /// �e�L�X�g�̒��S�����_�Ɉʒu���邱�Ƃ������B
            /// </summary>
            Center = 1,

            /// <summary>
            /// �e�L�X�g�̍��[�����_�Ɉʒu���邱�Ƃ������B
            /// </summary>
            Left = 2,

            /// <summary>
            /// �e�L�X�g�̉E�[�����_�Ɉʒu���邱�Ƃ������B
            /// </summary>
            Right = 4,

            /// <summary>
            /// �e�L�X�g�̏�[�����_�Ɉʒu���邱�Ƃ������B
            /// </summary>
            Top = 8,

            /// <summary>
            /// �e�L�X�g�̉��[�����_�Ɉʒu���邱�Ƃ������B
            /// </summary>
            Bottom = 16
        };
    }
}
