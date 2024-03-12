#pragma once

#include "zephyr\property.h"
#include "zephyr\type.h"

#include "Interface.h"
#include "SoundDevice.h"

struct IDirectSoundBuffer;
struct _DSBUFFERDESC;

namespace zephyr
{
    namespace sound
    {
        /// <summary>
        /// サウンド リソースの基底クラスです。
        /// </summary>
        class AbstractSoundBuffer : public Interface<IDirectSoundBuffer>
        {
        public:

            /// <summary>
            /// パンをリセットします。
            /// </summary>
            void ResetPan();

            /// <summary>
            /// サンプリング周波数をリセットします。
            /// </summary>
            void ResetFrequency();

            /// <summary>
            /// ボリュームをリセットします。
            /// </summary>
            void ResetVolume();

            /// <summary>
            /// サウンドがを再生中か調べます。
            /// </summary>
            READONLY_PROPERTY(bool, IsPlaying, const;);

            /// <summary>
            /// サウンドが停止中か調べます。
            /// </summary>
            READONLY_PROPERTY(bool, IsStopped, const;);

            /// <summary>
            /// サンプリング周波数を Hz 単位で取得または設定します。
            /// </summary>
            READWRITE_PROPERTY(unsigned long, Frequency, const;, ;);

            /// <summary>
            /// 音量を 0 ～ 1 の範囲で取得または設定します。 0 のとき最小、 1 のとき最大を表します。
            /// </summary>
            READWRITE_PROPERTY(double, Volume, const; , ;);

            /// <summary>
            /// パンを -1 ～ +1 の範囲で取得または設定します。 -1 のとき左側のスピーカーからのみ音が鳴り、 +1 のとき右側のスピーカーからのみ音が鳴ります。
            /// </summary>
            READWRITE_PROPERTY(double, Pan, const;, ;);

            /// <summary>
            /// 原音のサンプリング周波数を取得します。
            /// </summary>
            READONLY_PROPERTY(unsigned long, OriginalFrequency, const{ return this->originalFrequency; });

            // 空のサウンドバッファを生成する
            void Create(SoundDevice& device, _DSBUFFERDESC desc);

            // サウンドバッファを生成する
            void Create(SoundDevice& device, _DSBUFFERDESC desc, const byte* data);

            // 別のサウンドバッファを共有する
            void Create(SoundDevice& device, AbstractSoundBuffer& buffer);

            // バッファサイズ
            READONLY_PROPERTY(int, BufferSize, { return this->bufferSize; });

        private:

            // 原音の周波数
            unsigned long originalFrequency;

            // バッファサイズ
            int bufferSize;
        };
    }
}
