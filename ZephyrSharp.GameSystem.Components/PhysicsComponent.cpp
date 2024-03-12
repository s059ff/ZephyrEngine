#include <cmath>

#include "TransformComponent.h"
#include "PhysicsComponent.h"

#define this (*this)

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            void PhysicsComponent::ReceiveMessage(System::Object^ message, System::Object^ argument)
            {
                if (message == "update")
                {
                    this.Update();
                }
            }

            void PhysicsComponent::Update()
            {
                auto% Matrix = this.Owner->Get<TransformComponent^>()->Matrix;

                // 空気抵抗を計算する
                this.Force += -this.Velocity * 0.5f * this.Velocity.Magnitude;

                // 加速度を計算する
                this.Acceleration = this.Force / this.Mass;

                // 速度を更新する
                this.Velocity += this.Acceleration;

                // 座標を更新する
                Matrix.Position += this.Velocity;

                // オブジェクトにかかる力をリセットする
                this.Force = Vector3();

                // 空気抵抗を計算する
                this.Torque += -this.AngularVelocity * 0.2f;

                // 加速度を計算する
                this.AngularAcceleration = this.Torque / this.InertiaMoment;

                // 速度を更新する
                this.AngularVelocity += this.AngularAcceleration;

                // 角度を更新する
                float squareMag = this.AngularVelocity.SquaredMagnitude;
                if (squareMag > 0)
                {
                    float mag = sqrt(squareMag);
                    if (mag > 0.000001f)
                    {
                        float oneOverMag = 1.0f / mag;
                        Vector3 p = Matrix.Position;
                        Matrix.Position = Vector3(0, 0, 0);
                        Matrix = Matrix * Matrix4x3(Quaternion(this.AngularVelocity * oneOverMag, mag));
                        Matrix.Position = p;
                    }
                }

                // オブジェクトにかかる力をリセットする
                this.Torque = Vector3();
            }
        }
    }
}
