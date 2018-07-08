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

                // ��C��R���v�Z����
                this.Force += -this.Velocity * 0.5f * this.Velocity.magnitude;

                // �����x���v�Z����
                this.Acceleration = this.Force / this.Mass;

                // ���x���X�V����
                this.Velocity += this.Acceleration;

                // ���W���X�V����
                Matrix.position += this.Velocity;

                // �I�u�W�F�N�g�ɂ�����͂����Z�b�g����
                this.Force = linalg::Vector3::Zero;

                // ��C��R���v�Z����
                this.Torque += -this.AngularVelocity * 0.2f;

                // �����x���v�Z����
                this.AngularAcceleration = this.Torque / this.InertiaMoment;

                // ���x���X�V����
                this.AngularVelocity += this.AngularAcceleration;

                // �p�x���X�V����
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

                // �I�u�W�F�N�g�ɂ�����͂����Z�b�g����
                this.Torque = linalg::Vector3::Zero;
            }
        }
    }
}
