#pragma once

#include "common.h"
#include "SoundDevice.h"
#include "SoundBuffer.h"

using namespace System::Collections::Generic;

namespace ZephyrSharp
{
    namespace Sound
    {
        /// <summary>
        /// �����ɕ����̍Đ����s���T�E���h ���\�[�X�ł��B
        /// </summary>
        public ref class OverlappedSoundBuffer
        {
        public:

            /// <summary>
            /// �T�E���h�t�@�C����ǂݎ���ĐV�����T�E���h�o�b�t�@���쐬���܂��B
            /// </summary>
            /// <param name="path">�T�E���h�t�@�C���̃p�X�B</param>
            /// <param name="capacity">�����ɍĐ�����T�E���h�̍ő吔�B</param>
            void Create(String^ path, int capacity)
            {
                original->Create(path);
                buffers = gcnew List<SoundBuffer^>(capacity);
                for (int i = 0; i < capacity; i++)
                {
                    SoundBuffer^ newSound = gcnew SoundBuffer();
                    newSound->Create(original);
                    newSound->Stop();
                    buffers->Add(newSound);
                }
            }

            /// <summary>
            /// �T�E���h�o�b�t�@��������܂��B
            /// </summary>
            void Release()
            {
                for each (auto buffer in buffers)
                {
                    buffer->Release();
                }
                original->Release();
            }

            /// <summary>
            /// �T�E���h��擪����Đ����܂��B
            /// </summary>
            void Play()
            {
                for each (auto buffer in buffers)
                {
                    if (buffer->Stopped)
                    {
                        buffer->Play();
                        return;
                    }
                }
                runtime_assert(false, "�Đ��ł��铯�����𒴂��܂����B");
            }

        private:

            SoundBuffer^ original = gcnew SoundBuffer();

            List<SoundBuffer^>^ buffers;
        };
    }
}
