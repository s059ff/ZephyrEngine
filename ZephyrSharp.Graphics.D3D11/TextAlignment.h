#pragma once

namespace ZephyrSharp
{
    namespace Graphics
    {
        /// <summary>
        /// テキストの揃え方法を表します。
        /// </summary>
        [System::FlagsAttribute]
        public enum class TextAlignment
        {
            /// <summary>
            /// テキストの中心が原点に位置することを示す。
            /// </summary>
            Center = 1,

            /// <summary>
            /// テキストの左端が原点に位置することを示す。
            /// </summary>
            Left = 2,

            /// <summary>
            /// テキストの右端が原点に位置することを示す。
            /// </summary>
            Right = 4,

            /// <summary>
            /// テキストの上端が原点に位置することを示す。
            /// </summary>
            Top = 8,

            /// <summary>
            /// テキストの下端が原点に位置することを示す。
            /// </summary>
            Bottom = 16
        };
    }
}
