#include "TransformComponent.h"
#include "LightComponent.h"

#define this (*this)

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            void LightComponent::ReceiveMessage(System::Object^ message, System::Object^ argument)
            {
                if (message == "update")
                {
                    this.Update();
                }
            }

            void LightComponent::Update()
            {
                switch (this.Mode)
                {
                case LightMode::Stationary:
                    break;
                case LightMode::Tracking:
                {
                    this.Owner->Get<TransformComponent^>()->Position = TrackingTarget->Get<TransformComponent^>()->Position;
                    this.Owner->Get<TransformComponent^>()->Matrix.Translate(Offset);
                }
                    break;
                }
            }

            void LightComponent::LookAt(Vector3 eye, Vector3 at)
            {
                auto% matrix = this.Owner->Get<TransformComponent^>()->Matrix;
                matrix.LookAt(eye, at);
            }
        }
    }
}
