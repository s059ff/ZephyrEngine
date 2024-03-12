#include "TransformComponent.h"
#include "CameraComponent.h"

#define this (*this)

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            void CameraComponent::LookAt(Vector3 eye, Vector3 at)
            {
                auto% matrix = this.Owner->Get<TransformComponent^>()->Matrix;
                matrix.LookAt(eye, at);
            }

            Matrix4x3 CameraComponent::ViewingMatrix::get()
            {
                auto% matrix = this.Owner->Get<TransformComponent^>()->Matrix;
                return matrix.Inverse;
            }
        }
    }
}
