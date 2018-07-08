#include <cmath>

#include "Transform2DComponent.h"
#include "Physics2DComponent.h"

#define this (*this)

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            void Physics2DComponent::ReceiveMessage(System::Object^ message, System::Object^ argument)
            {
                if (message == "update")
                {
                    this.Update();
                }
            }

            void Physics2DComponent::Update()
            {
                auto% Matrix = this.Owner->Get<Transform2DComponent^>()->Matrix;

                // 空気抵抗を計算する
                this.Force += -this.Velocity * 0.5f * this.Velocity.Magnitude;

                // 加速度を計算する
                this.Acceleration = this.Force / this.Mass;

                // 速度を更新する
                this.Velocity += this.Acceleration;

                // 座標を更新する
                Matrix.Position += this.Velocity;

                // オブジェクトにかかる力をリセットする
                this.Force = Vector2();

                // 空気抵抗を計算する
                this.Torque += -this.AngularVelocity * 0.2f;

                // 加速度を計算する
                this.AngularAcceleration = this.Torque / this.InertiaMoment;

                // 速度を更新する
                this.AngularVelocity += this.AngularAcceleration;

                // 角度を更新する
                Vector2 p = Matrix.Position;
                Matrix.Position = Vector2(0, 0);
                Matrix = Matrix * Matrix3x2().Rotate(this.AngularVelocity);
                Matrix.Position = p;

                // オブジェクトにかかる力をリセットする
                this.Torque = 0;
            }
        }
    }
}
