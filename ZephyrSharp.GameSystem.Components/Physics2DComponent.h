#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 物理空間における 2D エンティティを表します。
            /// </summary>
            public ref class Physics2DComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// オブジェクトにかかる力。
                /// </summary>
                Vector2 Force;

                /// <summary>
                /// オブジェクトにかかる回転の力。
                /// </summary>
                float Torque;

                /// <summary>
                /// オブジェクトの速度。
                /// </summary>
                Vector2 Velocity;

                /// <summary>
                /// オブジェクトの角速度。
                /// </summary>
                float AngularVelocity;

                /// <summary>
                /// オブジェクトの加速度。
                /// </summary>
                Vector2 Acceleration;

                /// <summary>
                /// オブジェクトの角加速度。
                /// </summary>
                float AngularAcceleration;

                /// <summary>
                /// オブジェクトの質量。
                /// </summary>
                float Mass = 1.0f;

                /// <summary>
                /// オブジェクトの慣性モーメント。
                /// </summary>
                float InertiaMoment = 1.0f;

            protected public:

                virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) override;

            private:

                void Update();
            };
        }
    }
}
