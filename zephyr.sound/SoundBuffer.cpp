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
            runtime_assert(File::Exists(path), "�t�@�C�������݂��܂���B");
            runtime_assert(Path::GetExtension(path) == ".wav", "�w�肳�ꂽ�T�E���h�t�@�C���͎g�p�ł��܂���B");

            // Wave�t�@�C���I�[�v��
            MMIOINFO mmioInfo;
            ZeroMemory(&mmioInfo, sizeof(MMIOINFO));
            HMMIO hMmio = mmioOpen((char*)path.c_str(),&mmioInfo, MMIO_READ);
            runtime_assert(hMmio != nullptr, "�t�@�C���I�[�v���Ɏ��s���܂����B");

            // RIFF�`�����N����
            MMCKINFO riffChunk;
            riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
            if (mmioDescend(hMmio,&riffChunk, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false, "RIFF�`�����N�̌����Ɏ��s���܂����B");
            }

            // �t�H�[�}�b�g�`�����N����
            MMCKINFO formatChunk;
            formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
            if (mmioDescend(hMmio,&formatChunk,&riffChunk, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false, "�t�H�[�}�b�g�`�����N�̌����Ɏ��s���܂����B");
            }
            auto fmsize = formatChunk.cksize;

            // �t�H�[�}�b�g�擾
            WAVEFORMATEX wave_format;
            if (mmioRead(hMmio, reinterpret_cast<HPSTR>(&wave_format), fmsize) != fmsize)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false);
            }
            mmioAscend(hMmio,&formatChunk, 0);

            // �f�[�^�`�����N����
            MMCKINFO dataChunk;
            dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
            if (mmioDescend(hMmio,&dataChunk,&riffChunk, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
            {
                mmioClose(hMmio, 0);
                runtime_assert(false, "�f�[�^�`�����N�̌����Ɏ��s���܂����B");
            }

            // �f�[�^��ǂݎ��
            unique_ptr<byte[]> data(new byte[dataChunk.cksize]);
            DWORD size = mmioRead(hMmio, reinterpret_cast<HPSTR>(data.get()), dataChunk.cksize);
            runtime_assert(size == dataChunk.cksize);

            // �n���h���N���[�Y
            mmioClose(hMmio, 0);

            // �Z�J���_���o�b�t�@�ݒ�
            DSBUFFERDESC desc;
            desc.dwSize = sizeof(DSBUFFERDESC);
            desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN;
            desc.dwBufferBytes = size;
            desc.dwReserved = 0;
            desc.lpwfxFormat =&wave_format;
            desc.guid3DAlgorithm = GUID_NULL;

            // �Z�J���_���o�b�t�@�쐬
            base::Create(device, desc, data.get());

            // �T�E���h�̒������擾����
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
