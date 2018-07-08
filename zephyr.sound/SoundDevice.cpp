#include <dsound.h>

#include "SoundDevice.h"

#define this (*this)

namespace zephyr
{
    namespace sound
    {
        void SoundDevice::Create(handle hWindow)
        {
            IDirectSound* sound = nullptr;
            DirectSoundCreate(nullptr,&sound, nullptr);
            this.reset(sound);
            HRESULT res = this->SetCooperativeLevel((HWND)hWindow, DSSCL_NORMAL);
            assert(SUCCEEDED(res));
        }

        void SoundDevice::Release()
        {
            this.reset();
        }
    }
}
