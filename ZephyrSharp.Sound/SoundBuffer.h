#pragma once

#include "common.h"
#include "SoundDevice.h"

namespace ZephyrSharp
{
    namespace Sound
    {
        /// <summary>
        /// 全データをメモリに格納して再生を行うサウンド リソースです。
        /// </summary>
        public ref class SoundBuffer
            : public INativeWrapper<zephyr::sound::SoundBuffer>
        {
        public:

            /// <summary>
            /// サウンドファイルを読み取って新しいサウンドバッファを作成します。
            /// </summary>
            /// <param name="path">サウンドファイルのパス。</param>
            void Create(String^ path)
            {
                Native->Create(SoundDevice::Instance->NativeRef, to_string(path).c_str());
            }

            /// <summary>
            /// ほかのサウンドバッファのデータを共有するサウンドバッファを作成します。
            /// </summary>
            /// <param name="buffer">データの共有先のサウンドバッファ。</param>
            void Create(SoundBuffer^ buffer)
            {
                Native->Create(SoundDevice::Instance->NativeRef, buffer->NativeRef);
            }

            /// <summary>
            /// サウンドバッファを解放します。
            /// </summary>
            void Release()
            {
                Native->Release();
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
            /// パンをリセットします。
            /// </summary>
            void ResetPan()
            {
                Native->ResetPan();
            }

            /// <summary>
            /// サンプリング周波数をリセットします。
            /// </summary>
            void ResetFrequency()
            {
                Native->ResetFrequency();
            }

            /// <summary>
            /// ボリュームをリセットします。
            /// </summary>
            void ResetVolume()
            {
                Native->ResetVolume();
            }

            /// <summary>
            /// サウンドがを再生中か調べます。
            /// </summary>
            property bool Playing { bool get() { return Native->IsPlaying; } }

            /// <summary>
            /// サウンドが停止中か調べます。
            /// </summary>
            property bool Stopped { bool get() { return Native->IsStopped; }}

            /// <summary>
            /// サンプリング周波数を Hz 単位で取得または設定します。
            /// </summary>
            property unsigned long Frequency
            {
                unsigned long get() { return Native->Frequency; }

                void set(unsigned long value) { Native->Frequency = value; }
            }

            /// <summary>
            /// 音量を 0 〜 1 の範囲で取得または設定します。 0 のとき最小、 1 のとき最大を表します。
            /// </summary>
            property double Volume 
            {
                double get() { return Native->Volume; }
            
                void set(double value) { Native->Volume = value; }
            }

            /// <summary>
            /// パンを -1 〜 +1 の範囲で取得または設定します。 -1 のとき左側のスピーカーからのみ音が鳴り、 +1 のとき右側のスピーカーからのみ音が鳴ります。
            /// </summary>
            property double Pan 
            {
                double get() { return Native->Pan; }

                void set(double value) { Native->Pan = value; }
            }

            /// <summary>
            /// 原音のサンプリング周波数を取得します。
            /// </summary>
            property unsigned long OriginalFrequency
            {
                unsigned long get() { return Native->OriginalFrequency; }
            }

        public:

            /// <summary>
            /// サウンドの長さを秒単位で取得します。
            /// </summary>
            property int Duration
            {
                int get() { return Native->Duration; }
                void set(int value) { Native->Duration = value; }
            }
        };
    }
}
