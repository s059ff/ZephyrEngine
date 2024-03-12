#pragma once

#include "common.h"

namespace ZephyrSharp
{
    namespace Sound
    {
        /// <summary>
        /// サウンドシステムを統括します。
        /// </summary>
        public ref class SoundDevice
            : public INativeWrapper<zephyr::sound::SoundDevice>
        {
        public:

            /// <summary>
            /// デバイスを作成し、サウンドシステムを起動にします。
            /// </summary>
            /// <param name="hWindow">アプリケーションのウィンドウハンドル。</param>
            void Create(handle hWindow)
            {
                Native->Create(hWindow);
            }

            /// <summary>
            /// デバイスを作成し、サウンドシステムを起動にします。
            /// </summary>
            /// <param name="hWindow">アプリケーションのウィンドウハンドル。</param>
            void Create(unsigned long long hWindow)
            {
                Native->Create((handle)hWindow);
            }

            /// <summary>
            /// デバイスを解放、サウンドシステムを終了します。
            /// </summary>
            void Release()
            {
                Native->Release();
            }

        public:

            static SoundDevice^ Instance = gcnew SoundDevice();
        };
    }
}
