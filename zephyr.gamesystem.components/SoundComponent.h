#pragma once

#include "zephyr\property.h"
#include "zephyr.sound\SoundBuffer.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// 3D サウンドを鳴らします。
            /// </summary>
            class SoundComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// コンポーネントを初期化します。
                /// </summary>
                /// <param name="device">サウンドデバイス。</param> 
                /// <param name="buffer">サウンドバッファ。</param> 
                SoundComponent(sound::SoundDevice& device, sound::SoundBuffer& buffer)
                {
                    this->Sound.Create(device, buffer);
                    this->VolumeFactor = 1;
                }

                /// <summary>
                /// コンポーネントを初期化します。
                /// </summary>
                /// <param name="device">サウンドデバイス。</param> 
                /// <param name="buffer">サウンドバッファ。</param> 
                /// <param name="play">true の場合、すぐに再生する。</param> 
                SoundComponent(sound::SoundDevice& device, sound::SoundBuffer& buffer, bool play)
                    : SoundComponent(device, buffer)
                {
                    if (play)
                        this->Sound.Play();
                }

                /// <summary>
                /// サウンドを再生します。
                /// </summary>
                void Play()
                {
                    this->Sound.Play();
                }

                /// <summary>
                /// サウンドをループ再生します。
                /// </summary>
                void LoopPlay()
                {
                    this->Sound.LoopPlay();
                }

                /// <summary>
                /// サウンドを取得または設定します。
                /// </summary>
                sound::SoundBuffer Sound;

                /// <summary>
                /// 音量を調整します。
                /// </summary>
                double VolumeFactor;

                /// <summary>
                /// 周波数を取得します。
                /// </summary>
                READONLY_PROPERTY(unsigned long, Frequency, { return Sound.Frequency; });

                    /// <summary>
                    /// 音量を取得します。
                    /// </summary>
                READONLY_PROPERTY(double, Volume, { return Sound.Volume; });

                /// <summary>
                /// パンを取得します。
                /// </summary>
                READONLY_PROPERTY(double, Pan, { return Sound.Pan; });

            public:

                virtual void ReceiveMessage(const string& message, void* params[]) override;

                virtual void OnDestroy() override;

            private:

                void Update();
            };
        }
    }
}
