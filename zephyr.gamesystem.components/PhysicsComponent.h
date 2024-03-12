#pragma once

#include "zephyr\property.h"
#include "zephyr\string.h"
#include "zephyr.linalg\Vector3.h"
#include "zephyr.gamesystem\EntityComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// 物理空間におけるエンティティを表します。
            /// </summary>
            class PhysicsComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// オブジェクトにかかる力。
                /// </summary>
                linalg::Vector3 Force;

                /// <summary>
                /// オブジェクトにかかる回転の力。
                /// </summary>
                linalg::Vector3 Torque;

                /// <summary>
                /// オブジェクトの速度。
                /// </summary>
                linalg::Vector3 Velocity;

                /// <summary>
                /// オブジェクトの角速度。
                /// </summary>
                linalg::Vector3 AngularVelocity;

                /// <summary>
                /// オブジェクトの加速度。
                /// </summary>
                linalg::Vector3 Acceleration;

                /// <summary>
                /// オブジェクトの角加速度。
                /// </summary>
                linalg::Vector3 AngularAcceleration;

                /// <summary>
                /// オブジェクトの質量。
                /// </summary>
                float Mass = 1.0f;

                /// <summary>
                /// オブジェクトの慣性モーメント。
                /// </summary>
                float InertiaMoment = 1.0f;

            public:

                virtual void ReceiveMessage(const string& message, void* params[]) override;

            private:

                void Update();
            };
        }
    }
}
