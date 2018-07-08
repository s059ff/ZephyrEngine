#pragma once

#include "zephyr\string.h"

#include "AbstractSoundBuffer.h"
#include "SoundDevice.h"

struct OggVorbis_File;

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// 再生と読み出しを同時に行うサウンド リソースです。
        /// </summary>
        class StreamingSoundBuffer : public AbstractSoundBuffer
        {
        private:
            using base = AbstractSoundBuffer;

        public:

            /// <summary>
            /// このクラスの新しいインスタンスを初期化します。
            /// </summary>
            StreamingSoundBuffer();

            /// <summary>
            /// インスタンスを破棄します。
            /// </summary>
            ~StreamingSoundBuffer();

            /// <summary>
            /// サウンドファイルを開いて、サウンドを再生可能な状態にします。
            /// </summary>
            /// <param name="device">サウンドデバイス。</param>
            /// <param name="path">サウンドファイルのパス。</param>
            void Create(SoundDevice& device, const string& path);

            /// <summary>
            /// サウンドデータを破棄し、サウンドファイルを閉じます。
            /// </summary>
            void Close();

            /// <summary>
            /// 秒単位で再生位置を変更します。
            /// </summary>
            /// <param name="time">再生位置。</param>
            void Seek(int time);

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

            /// <summary>
            /// 再生状況に応じて、サウンドをメモリに読み込みます。このメソッドは毎フレーム呼び出す必要があります。
            /// </summary>
            void Update();

        private:

            // oggファイル
            OggVorbis_File* oggFile;

            // ファイルを開いているか
            bool isOpened;

            // ループ再生を行っているか
            bool isLooping;

            // 書き込み先ブロック
            enum class Block { First, Second } next;
        };
    }
}
