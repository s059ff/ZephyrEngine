#include <memory>

#include <Windows.h>
#include <dsound.h>
#include <mmsystem.h>

#include "zephyr\runtime_assert.h"
#include "zephyr.filesystem\File.h"
#include "zephyr.filesystem\Path.h"

#include "SoundDevice.h"
#include "SoundBuffer.h"

#define this (*this)

using namespace std;
using namespace zephyr::filesystem;

namespace zephyr
{
    namespace sound
    {
        SoundBuffer::~SoundBuffer()
        {
            this.Release();
        }

        void SoundBuffer::Create(SoundDevice& device, const string& path)
        {
            runtime_assert(File::Exists(path), "ファイルが存在しません。");
            runtime_assert(Path::GetExtension(path) == ".wav", "指定されたサウンドファイルは使用できません。");

            // Waveファイルオープン
            MMIOINFO mmioInfo;
            ZeroMemory(&mmioInfo, sizeof(MMIOINFO));
            HMMIO hMmio = mmioOpen((char*)path.c_str(),&mmioInfo, MMIO_READ);
            runtime_assert(hMmio != nullptr, "ファイルオープンに失敗しました。");

            // RIFFチャンク検索
            MMCKINFO riffChunk;
            riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
            if (mmioDescend(hMmio,&riffChunk, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false, "RIFFチャンクの検索に失敗しました。");
            }

            // フォーマットチャンク検索
            MMCKINFO formatChunk;
            formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
            if (mmioDescend(hMmio,&formatChunk,&riffChunk, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false, "フォーマットチャンクの検索に失敗しました。");
            }
            auto fmsize = formatChunk.cksize;

            // フォーマット取得
            WAVEFORMATEX wave_format;
            if (mmioRead(hMmio, reinterpret_cast<HPSTR>(&wave_format), fmsize) != fmsize)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false);
            }
            mmioAscend(hMmio,&formatChunk, 0);

            // データチャンク検索
            MMCKINFO dataChunk;
            dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
            if (mmioDescend(hMmio,&dataChunk,&riffChunk, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false, "データチャンクの検索に失敗しました。");
            }

            // データを読み取る
            unique_ptr<byte[]> data(new byte[dataChunk.cksize]);
            DWORD size = mmioRead(hMmio, reinterpret_cast<HPSTR>(data.get()), dataChunk.cksize);
            runtime_assert(size == dataChunk.cksize);

            // ハンドルクローズ
            mmioClose(hMmio, 0);

            // セカンダリバッファ設定
            DSBUFFERDESC desc;
            desc.dwSize = sizeof(DSBUFFERDESC);
            desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN;
            desc.dwBufferBytes = size;
            desc.dwReserved = 0;
            desc.lpwfxFormat =&wave_format;
            desc.guid3DAlgorithm = GUID_NULL;

            // セカンダリバッファ作成
            base::Create(device, desc, data.get());

            // サウンドの長さを取得する
            this.Duration = this.BufferSize / desc.lpwfxFormat->nAvgBytesPerSec;
        }

        void SoundBuffer::Create(SoundDevice& device, SoundBuffer& sound)
        {
            base::Create(device, sound);
        }

        void SoundBuffer::Release()
        {
            if (this.available())
            {
                this.Stop();
                this.reset();
            }
        }

        void SoundBuffer::Play()
        {
            this->SetCurrentPosition(0);
            this->Play(0, 0, 0);
            this.isLooping = false;
        }

        void SoundBuffer::LoopPlay()
        {
            this->SetCurrentPosition(0);
            this->Play(0, 0, DSBPLAY_LOOPING);
            this.isLooping = true;
        }

        void SoundBuffer::Stop()
        {
            this->Stop();
            this->SetCurrentPosition(0);
        }

        void SoundBuffer::Pause()
        {
            if (this.IsPlaying)
            {
                this->Stop();
            }
            else
            {
                this->Play(0, 0, this.isLooping ? DSBPLAY_LOOPING : 0);
            }
        }
    }
}
