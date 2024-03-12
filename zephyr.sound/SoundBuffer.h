#pragma once

#include "zephyr\property.h"
#include "zephyr\string.h"

#include "AbstractSoundBuffer.h"
#include "SoundDevice.h"

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// 全データをメモリに格納して再生を行うサウンド リソースです。
        /// </summary>
        class SoundBuffer : public AbstractSoundBuffer
        {
        private:
            using base = AbstractSoundBuffer;

        public:

            /// <summary>
            /// サウンドバッファを解放します。
            /// </summary>
            ~SoundBuffer();

            /// <summary>
            /// サウンドファイルを読み取って新しいサウンドバッファを作成します。
            /// </summary>
            /// <param name="device">サウンドデバイス。</param>
            /// <param name="path">サウンドファイルのパス。</param>
            void Create(SoundDevice& device, const string& path);

            /// <summary>
            /// ほかのサウンドバッファのデータを共有するサウンドバッファを作成します。
            /// </summary>
            /// <param name="device">サウンドデバイス。</param>
            /// <param name="buffer">データの共有先のサウンドバッファ。</param>
            void Create(SoundDevice& device, SoundBuffer& buffer);

            /// <summary>
            /// サウンドバッファを解放します。
            /// </summary>
            void Release();

            /// <summary>
            /// サウンドを先頭から再生します。
            /// </summary>
            void Play();

            /// <summary>
            /// サウンドを先頭からループ再生します。
            /// </summary>
            void LoopPlay();

            /// <summary>
            /// サウンドを停止し、再生位置を先頭に戻します。
            /// </summary>
            void Stop();

            /// <summary>
            /// サウンドを一時停止もしくは再開します。
            /// </summary>
            void Pause();

        public:

            /// <summary>
            /// サウンドの長さを秒単位で取得します。
            /// </summary>
            READWRITE_PROPERTY(int, Duration, { return this->duration; }, { this->duration = value; });

        private:

            // ループ再生中かどうか
            bool isLooping = false;

            // サウンドの長さ
            int duration;
        };
    }
}
