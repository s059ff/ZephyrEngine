#pragma once

#include "zephyr\type.h"

#include "Interface.h"

struct IDirectSound;

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// サウンドシステムを統括します。
        /// </summary>
        class SoundDevice : public Interface<IDirectSound>
        {
        public:

            /// <summary>
            /// デバイスを作成し、サウンドシステムを起動にします。
            /// </summary>
            void Create(handle hWindow);

            /// <summary>
            /// デバイスを解放、サウンドシステムを終了します。
            /// </summary>
            void Release();
        };
    }
}
