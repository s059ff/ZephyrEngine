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

                // ��C��R���v�Z����
                this.Force += -this.Velocity * 0.5f * this.Velocity.Magnitude;

                // �����x���v�Z����
                this.Acceleration = this.Force / this.Mass;

                // ���x���X�V����
                this.Velocity += this.Acceleration;

                // ���W���X�V����
                Matrix.Position += this.Velocity;

                // �I�u�W�F�N�g�ɂ�����͂����Z�b�g����
                this.Force = Vector2();

                // ��C��R���v�Z����
                this.Torque += -this.AngularVelocity * 0.2f;

                // �����x���v�Z����
                this.AngularAcceleration = this.Torque / this.InertiaMoment;

                // ���x���X�V����
                this.AngularVelocity += this.AngularAcceleration;

                // �p�x���X�V����
                Vector2 p = Matrix.Position;
                Matrix.Position = Vector2(0, 0);
                Matrix = Matrix * Matrix3x2().Rotate(this.AngularVelocity);
                Matrix.Position = p;

                // �I�u�W�F�N�g�ɂ�����͂����Z�b�g����
                this.Torque = 0;
            }
        }
    }
}
