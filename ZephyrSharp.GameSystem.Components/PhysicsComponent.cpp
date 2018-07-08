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

                // ��C��R���v�Z����
                this.Force += -this.Velocity * 0.5f * this.Velocity.Magnitude;

                // �����x���v�Z����
                this.Acceleration = this.Force / this.Mass;

                // ���x���X�V����
                this.Velocity += this.Acceleration;

                // ���W���X�V����
                Matrix.Position += this.Velocity;

                // �I�u�W�F�N�g�ɂ�����͂����Z�b�g����
                this.Force = Vector3();

                // ��C��R���v�Z����
                this.Torque += -this.AngularVelocity * 0.2f;

                // �����x���v�Z����
                this.AngularAcceleration = this.Torque / this.InertiaMoment;

                // ���x���X�V����
                this.AngularVelocity += this.AngularAcceleration;

                // �p�x���X�V����
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

                // �I�u�W�F�N�g�ɂ�����͂����Z�b�g����
                this.Torque = Vector3();
            }
        }
    }
}
