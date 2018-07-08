#include "zephyr.gamesystem\Entity.h"
#include "zephyr.linalg\linalg.h"
#include "zephyr.linalg\Quaternion.h"
#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.linalg\Vector3.h"

#include "TransformComponent.h"
#include "PhysicsComponent.h"

#define this (*this)

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            void PhysicsComponent::ReceiveMessage(const string& message, void* params[])
            {
                if (message == "update")
                {
                    this.Update();
                }
            }

            void PhysicsComponent::Update()
            {
                auto& Matrix = this.Owner->Get<TransformComponent>()->Matrix;

                // 空気抵抗を計算する
                this.Force += -this.Velocity * 0.5f * this.Velocity.magnitude;

                // 加速度を計算する
                this.Acceleration = this.Force / this.Mass;

                // 速度を更新する
                this.Velocity += this.Acceleration;

                // 座標を更新する
                Matrix.position += this.Velocity;

                // オブジェクトにかかる力をリセットする
                this.Force = linalg::Vector3::Zero;

                // 空気抵抗を計算する
                this.Torque += -this.AngularVelocity * 0.2f;

                // 加速度を計算する
                this.AngularAcceleration = this.Torque / this.InertiaMoment;

                // 速度を更新する
                this.AngularVelocity += this.AngularAcceleration;

                // 角度を更新する
                float squareMag = this.AngularVelocity.squared_magnitude;
                if (squareMag > 0)
                {
                    float mag = sqrt(squareMag);
                    if (mag > 0.000001f)
                    {
                        float oneOverMag = 1.0f / mag;
                        auto p = Matrix.position;
                        Matrix.position = linalg::Vector3(0, 0, 0);
                        Matrix = Matrix * linalg::Matrix4x3(linalg::Quaternion(this.AngularVelocity * oneOverMag, mag));
                        Matrix.position = p;
                    }
                }

                // オブジェクトにかかる力をリセットする
                this.Torque = linalg::Vector3::Zero;
            }
        }
    }
}
