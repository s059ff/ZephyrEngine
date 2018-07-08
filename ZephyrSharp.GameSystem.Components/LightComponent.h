#pragma once

using namespace System::Collections::Generic;
using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// ライトを表します。
            /// </summary>
            public ref class LightComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ライトの設定を表します。
                /// </summary>
                enum class LightMode
                {
                    /// <summary>
                    /// ライトは静止している。
                    /// </summary>
                    Stationary,

                    /// <summary>
                    /// ターゲットを追跡する。
                    /// </summary>
                    Tracking
                };

                /// <summary>
                /// ライトの向きを設定します。
                /// </summary>
                /// <param name="eye">ライトの座標。</param> 
                /// <param name="at">注視先の座標。</param> 
                void LookAt(Vector3 eye, Vector3 at);

                /// <summary>
                /// トラッキングの対象となるエンティティ。
                /// </summary>
                property Entity^ TrackingTarget;

                /// <summary>
                /// トラッキング対象エンティティとこのエンティティの相対位置。
                /// </summary>
                property Vector3 Offset;

                /// <summary>
                /// ライトの動作設定を表します。
                /// </summary>
                property LightMode Mode;

            protected public:

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

            private:

                void Update();
            };
        }
    }
}
