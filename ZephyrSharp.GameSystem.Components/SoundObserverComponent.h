#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 3D サウンドの観測者を表します。
            /// </summary>
            public ref class SoundObserverComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// サウンドの効果範囲を取得または設定します。
                /// </summary>
                property double EffectRange;

                /// <summary>
                /// 音速を取得または設定します。
                /// </summary>
                property double SonicSpeed;

            internal:

                static SoundObserverComponent^ Observer;

                Vector3 Position;

                Vector3 Velocity;

                Matrix4x3 Matrix;

            protected public:

                virtual void OnAttach() override;

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

            private:

                void Update();
            };
        }
    }
}
