#pragma once

#include "common.h"
#include "SoundDevice.h"

namespace ZephyrSharp
{
    namespace Sound
    {
        /// <summary>
        /// 再生と読み出しを同時に行うサウンド リソースです。
        /// </summary>
        public ref class StreamingSoundBuffer
            : public INativeWrapper<zephyr::sound::StreamingSoundBuffer>
        {
        public:

            /// <summary>
            /// サウンドファイルを開いて、サウンドを再生可能な状態にします。
            /// </summary>
            /// <param name="path">サウンドファイルのパス。</param>
            void Create(String^ path)
            {
                Native->Create(SoundDevice::Instance->NativeRef, to_string(path).c_str());
            }

            /// <summary>
            /// サウンドデータを破棄し、サウンドファイルを閉じます。
            /// </summary>
            void Close()
            {
                Native->Close();
            }

            /// <summary>
            /// 秒単位で再生位置を変更します。
            /// </summary>
            /// <param name="time">再生位置。</param>
            void Seek(int time)
            {
                Native->Seek(time);
            }

            /// <summary>
            /// サウンドを先頭から再生します。
            /// </summary>
            void Play()
            {
                Native->Play();
            }

            /// <summary>
            /// サウンドを先頭からループ再生します。
            /// </summary>
            void LoopPlay()
            {
                Native->LoopPlay();
            }

            /// <summary>
            /// サウンドを停止し、再生位置を先頭に戻します。
            /// </summary>
            void Stop()
            {
                Native->Stop();
            }

            /// <summary>
            /// サウンドを一時停止もしくは再開します。
            /// </summary>
            void Pause()
            {
                Native->Pause();
            }

            /// <summary>
            /// 再生状況に応じて、サウンドをメモリに読み込みます。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update()
            {
                Native->Update();
            }
        };
    }
}
