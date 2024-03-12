#include "zephyr.gamesystem\Entity.h"

#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "SoundObserverComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            void SoundObserverComponent::OnAttach()
            {
                Observer = this;
            }

            void SoundObserverComponent::ReceiveMessage(const string& message, void* params[])
            {
                if (message == "update")
                {
                    this->Update();
                }
            }

            void SoundObserverComponent::Update()
            {
                this->Position = Owner->Get<TransformComponent>()->Position;
                this->Matrix = Owner->Get<TransformComponent>()->Matrix;
                if (Owner->Has<PhysicsComponent>())
                    this->Velocity = Owner->Get<PhysicsComponent>()->Velocity;
                else
                    this->Velocity = linalg::Vector3::Zero;
            }
        }
    }
}
