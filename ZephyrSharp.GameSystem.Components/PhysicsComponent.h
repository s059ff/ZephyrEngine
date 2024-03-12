#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 物理空間におけるエンティティを表します。
            /// </summary>
            public ref class PhysicsComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// オブジェクトにかかる力。
                /// </summary>
                Vector3 Force;

                /// <summary>
                /// オブジェクトにかかる回転の力。
                /// </summary>
                Vector3 Torque;

                /// <summary>
                /// オブジェクトの速度。
                /// </summary>
                Vector3 Velocity;

                /// <summary>
                /// オブジェクトの角速度。
                /// </summary>
                Vector3 AngularVelocity;

                /// <summary>
                /// オブジェクトの加速度。
                /// </summary>
                Vector3 Acceleration;

                /// <summary>
                /// オブジェクトの角加速度。
                /// </summary>
                Vector3 AngularAcceleration;

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
