#pragma once

using namespace ZephyrSharp::Linalg;
using namespace ZephyrSharp::Sound;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 3D サウンドを鳴らします。
            /// </summary>
            public ref class SoundComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// コンポーネントを初期化します。
                /// </summary>
                /// <param name="buffer">サウンドバッファ。</param> 
                SoundComponent(SoundBuffer^ buffer)
                {
                    Sound = gcnew SoundBuffer();
                    Sound->Create(buffer);
                    this->VolumeFactor = 1;
                }

                /// <summary>
                /// コンポーネントを初期化します。
                /// </summary>
                /// <param name="buffer">サウンドバッファ。</param> 
                /// <param name="play">true の場合、すぐに再生する。</param> 
                SoundComponent(SoundBuffer^ buffer, bool play)
                    : SoundComponent(buffer)
                {
                    if (play)
                        this->Sound->Play();
                }

                /// <summary>
                /// サウンドを再生します。
                /// </summary>
                void Play()
                {
                    Sound->Play();
                }

                /// <summary>
                /// サウンドをループ再生します。
                /// </summary>
                void LoopPlay()
                {
                    Sound->LoopPlay();
                }

                /// <summary>
                /// サウンドを取得または設定します。
                /// </summary>
                property SoundBuffer^ Sound;

                /// <summary>
                /// 音量を調整します。
                /// </summary>
                property double VolumeFactor;

                /// <summary>
                /// 周波数を取得します。
                /// </summary>
                property unsigned long Frequency { unsigned long get() { return Sound->Frequency; } }

                /// <summary>
                /// 音量を取得します。
                /// </summary>
                property double Volume { double get() { return Sound->Volume; } }

                /// <summary>
                /// パンを取得します。
                /// </summary>
                property double Pan { double get() { return Sound->Pan; } }

            protected public:

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

                virtual void OnDestroy() override;

            private:

                void Update();
            };
        }
    }
}
