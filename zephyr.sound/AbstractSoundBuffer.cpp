#include <cmath>

#include <dsound.h>

#include "AbstractSoundBuffer.h"
#include "SoundDevice.h"

#define this (*this)

namespace zephyr
{
    namespace sound
    {
        void AbstractSoundBuffer::ResetPan()
        {
            this.Pan = 0;
        }

        void AbstractSoundBuffer::ResetFrequency()
        {
            this->SetFrequency(DSBFREQUENCY_ORIGINAL);
        }

        void AbstractSoundBuffer::ResetVolume()
        {
            this->SetVolume(DSBVOLUME_MAX);
        }

        bool AbstractSoundBuffer::_get_IsPlaying() const
        {
            DWORD status = 0;
            this->GetStatus(&status);
            return status& DSBSTATUS_LOOPING || status& DSBSTATUS_PLAYING;
        }

        bool AbstractSoundBuffer::_get_IsStopped() const
        {
            return !this.IsPlaying;
        }

        unsigned long AbstractSoundBuffer::_get_Frequency() const
        {
            DWORD frequency = 0;
            this->GetFrequency(&frequency);
            return frequency;
        }

        void AbstractSoundBuffer::_set_Frequency(DWORD frequency)
        {
            HRESULT result = this->SetFrequency(frequency);
            assert(SUCCEEDED(result));
        }

        static long convertVolume(double volume)
        {
            assert(volume >= 0 && volume <= 1);

            if (volume >= 1)
            {
                return DSBVOLUME_MAX;
            }
            else if (volume <= 0)
            {
                return DSBVOLUME_MIN;
            }
            else
            {
                return (long)(log2(volume) * 1000);
            }
        }

        static double convertVolume(long volume)
        {
            return pow(2, (double)volume / 1000.0);
        }

        double AbstractSoundBuffer::_get_Volume() const
        {
            long volume = 0;
            this->GetVolume(&volume);
            return convertVolume(volume);
        }

        void AbstractSoundBuffer::_set_Volume(double volume)
        {
            this->SetVolume(convertVolume(volume));
        }

        double AbstractSoundBuffer::_get_Pan() const
        {
            long pan = 0;
            this->GetPan(&pan);
            double value = convertVolume(abs(pan));
            return (pan > 0) ? value : -value;
        }

        void AbstractSoundBuffer::_set_Pan(double value)
        {
            long pan = convertVolume(1.0 - abs(value));
            this->SetPan((value > 0) ? pan : -pan);
        }

        void AbstractSoundBuffer::Create(SoundDevice& device, _DSBUFFERDESC desc)
        {
            // セカンダリバッファ作成
            com_ptr<IDirectSoundBuffer> ptmpBuf;
            auto result = device->CreateSoundBuffer(&desc, &ptmpBuf, nullptr);
            assert(SUCCEEDED(result));
            IDirectSoundBuffer* buffer = nullptr;
            ptmpBuf->QueryInterface(IID_IDirectSoundBuffer, (void**)(&buffer));
            this.reset(buffer);

            assert(this.available());

            this.originalFrequency = this.Frequency;
            this.bufferSize = desc.dwBufferBytes;
            //this.Duration = this.BufferSize / desc.lpwfxFormat->nAvgBytesPerSec;
            this.Pan = 0.0;
            this.Volume = 1.0;
        }

        void AbstractSoundBuffer::Create(SoundDevice& device, _DSBUFFERDESC desc, const byte* data)
        {
            this.Create(device, desc);

            // セカンダリバッファにWaveデータを書き込む
            void* buffer = nullptr;
            DWORD size = 0;
            auto result = this->Lock(0, 0, &buffer, &size, nullptr, nullptr, DSBLOCK_ENTIREBUFFER);
            assert(SUCCEEDED(result));
            memcpy(buffer, data, size);
            this->Unlock(buffer, size, nullptr, 0);
        }

        void AbstractSoundBuffer::Create(SoundDevice& device, AbstractSoundBuffer& buffer)
        {
            IDirectSoundBuffer* src = buffer.ptr;
            IDirectSoundBuffer* dest = nullptr;
            auto result = device->DuplicateSoundBuffer(src, &dest);
            assert(SUCCEEDED(result));
            this.ptr = dest;

            this.originalFrequency = buffer.OriginalFrequency;
            this.bufferSize = buffer.BufferSize;
            //this.Duration = buffer->Duration;
            this.Pan = 0.0;
            this.Volume = 1.0;
        }
    }
}
