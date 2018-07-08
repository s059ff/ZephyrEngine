#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "SoundObserverComponent.h"

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            void SoundObserverComponent::OnAttach()
            {
                Observer = this;
            }

            void SoundObserverComponent::ReceiveMessage(System::Object^ message, System::Object^ argument)
            {
                if (message == "update")
                {
                    this->Update();
                }
            }

            void SoundObserverComponent::Update()
            {
                this->Position = Owner->Get<TransformComponent^>()->Position;
                this->Matrix = Owner->Get<TransformComponent^>()->Matrix;
                if (Owner->Has<PhysicsComponent^>())
                    this->Velocity = Owner->Get<PhysicsComponent^>()->Velocity;
                else
                    this->Velocity = Vector3::Zero;
            }
        }
    }
}
