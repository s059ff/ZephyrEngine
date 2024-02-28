#include <dsound.h>

#include <vorbis/vorbisfile.h>

#include "zephyr.filesystem\File.h"
#include "zephyr.filesystem\Path.h"
#include "StreamingSoundBuffer.h"

#define this (*this)

using namespace std;
using namespace zephyr::filesystem;

using base = zephyr::sound::AbstractSoundBuffer;

namespace zephyr
{
    namespace sound
    {
        // ファイルからループしないoggサウンドデータを読み取る
        static void read_ogg(byte* dest, OggVorbis_File* oggFile, int length)
        {
            ZeroMemory(dest, length);

            bool eof = false;
            int bitstream = 0;

            while (length > 0)
            {
                long readLength = ov_read(oggFile, (char*)dest, length, 0, sizeof(WORD), 1, &bitstream);
                dest += readLength;
                length -= readLength;

                // ファイルの終端に達したとき
                if (readLength == 0)
                {
                    eof = true;
                    break;
                }
            }

            //return eof;
        }

        // ファイルからループするoggサウンドデータを読み取る
        static void read_loop_ogg(byte* dest, OggVorbis_File* oggFile, int length)
        {
            ZeroMemory(dest, length);

            int bitstream = 0;

            while (length > 0)
            {
                long readLength = ov_read(oggFile, (char*)dest, length, 0, sizeof(WORD), 1, &bitstream);
                dest += readLength;
                length -= readLength;

                // ファイルの終端に達したとき
                if (readLength == 0)
                {
                    ov_time_seek(oggFile, 0.0);
                }
            }
        }

        StreamingSoundBuffer::StreamingSoundBuffer()
        {
            this.oggFile = new OggVorbis_File();
        }

        StreamingSoundBuffer::~StreamingSoundBuffer()
        {
            this.Close();
            delete this.oggFile;
        }

        void StreamingSoundBuffer::Create(SoundDevice& device, const string& path)
        {
            this.Close();

            if (!File::Exists(path))
            {
                throw runtime_error("ファイルが存在しません。");
            }
            if (Path::GetExtension(path) != ".ogg")
            {
                throw runtime_error("指定されたサウンドファイルは使用できません。");
            }

            if (ov_fopen(path.c_str(), this.oggFile) != 0)
            {
                throw runtime_error("ファイルのオープンに失敗しました。");
            }

            vorbis_info* info = ov_info(this.oggFile, -1);

            // WAVE情報
            WAVEFORMATEX waveFormat;
            waveFormat.wFormatTag = WAVE_FORMAT_PCM;
            waveFormat.nChannels = info->channels;
            waveFormat.nSamplesPerSec = info->rate;
            waveFormat.wBitsPerSample = 16;
            waveFormat.nBlockAlign = info->channels * 16 / 8;
            waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
            waveFormat.cbSize = 0;

            // DirectSoundBuffer情報
            DSBUFFERDESC desc;
            desc.dwSize = sizeof(DSBUFFERDESC);
            desc.dwFlags = 0;
            desc.dwBufferBytes = waveFormat.nAvgBytesPerSec * 1;
            desc.dwReserved = 0;
            desc.lpwfxFormat = &waveFormat;
            desc.guid3DAlgorithm = GUID_NULL;

            // セカンダリバッファ作成
            base::Create(device, desc);

            // 先頭のデータを読み込む
            void* buffer = nullptr;
            DWORD bytes = 0;
            if (SUCCEEDED(this->Lock(0, this.BufferSize / 2, &buffer, &bytes, nullptr, nullptr, 0)))
            {
                assert(bytes == this.BufferSize / 2);
                read_loop_ogg((byte*)buffer, this.oggFile, bytes);
                this->Unlock(buffer, bytes, nullptr, 0);
            }
            this.next = Block::Second;
            this.isOpened = true;
        }

        void StreamingSoundBuffer::Close()
        {
            if (this.isOpened)
            {
                ov_clear(this.oggFile);
                this.isOpened = false;
            }
            base::reset();
        }

        void StreamingSoundBuffer::Update()
        {
            auto read_func = this.isLooping ? read_loop_ogg : read_ogg;

            DWORD position = 0;
            this->GetCurrentPosition(&position, nullptr);

            if ((this.next == Block::First && (int)position >= this.BufferSize / 2) || (this.next == Block::Second && (int)position < this.BufferSize / 2))
            {
                void* buffer = nullptr;
                DWORD bytes = 0;
                DWORD offset = (this.next == Block::First) ? 0 : this.BufferSize / 2;
                if (SUCCEEDED(this->Lock(offset, this.BufferSize / 2, &buffer, &bytes, nullptr, nullptr, 0)))
                {
                    assert(bytes == this.BufferSize / 2);
                    read_func((byte*)buffer, this.oggFile, bytes);
                    this->Unlock(buffer, bytes, nullptr, 0);
                }
                this.next = (this.next == Block::First) ? Block::Second : Block::First;
            }
        }

        void StreamingSoundBuffer::Seek(int time)
        {
            ov_time_seek(oggFile, time);

            void* buffer = nullptr;
            DWORD bytes = 0;
            if (SUCCEEDED(this->Lock(0, this.BufferSize / 2, &buffer, &bytes, nullptr, nullptr, 0)))
            {
                assert(bytes == this.BufferSize / 2);
                read_loop_ogg((byte*)buffer, this.oggFile, bytes);
                this->Unlock(buffer, bytes, nullptr, 0);
            }
            this.next = Block::Second;

            this->SetCurrentPosition(0);
        }

        void StreamingSoundBuffer::Play()
        {
            this.isLooping = false;
            this->SetCurrentPosition(0);
            this->Play(0, 0, DSBPLAY_LOOPING);
        }

        void StreamingSoundBuffer::LoopPlay()
        {
            this.isLooping = true;
            this->SetCurrentPosition(0);
            this->Play(0, 0, DSBPLAY_LOOPING);
        }

        void StreamingSoundBuffer::Stop()
        {
            this->Stop();
            this->SetCurrentPosition(0);
        }

        void StreamingSoundBuffer::Pause()
        {
            if (this.IsPlaying)
            {
                this->Stop();
            }
            else
            {
                this->Play(0, 0, DSBPLAY_LOOPING);
            }
        }
    }
}
