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
        /// 同時に複数の再生を行うサウンド リソースです。
        /// </summary>
        public ref class OverlappedSoundBuffer
        {
        public:

            /// <summary>
            /// サウンドファイルを読み取って新しいサウンドバッファを作成します。
            /// </summary>
            /// <param name="path">サウンドファイルのパス。</param>
            /// <param name="capacity">同時に再生するサウンドの最大数。</param>
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
            /// サウンドバッファを解放します。
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
            /// サウンドを先頭から再生します。
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
                runtime_assert(false, "再生できる同時数を超えました。");
            }

        private:

            SoundBuffer^ original = gcnew SoundBuffer();

            List<SoundBuffer^>^ buffers;
        };
    }
}
