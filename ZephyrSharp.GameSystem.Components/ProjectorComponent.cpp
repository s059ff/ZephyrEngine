#include "ProjectorComponent.h"

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            ProjectorComponent::ProjectorComponent()
            {
                this->SetPerspectiveMode((float)System::Math::PI / 3, 4.0f / 3.0f, 1.0f, 128.0f);
            }

            void ProjectorComponent::SetPerspectiveMode(float fovY, float aspect, float zn, float zf)
            {
                this->ProjectionMatrix.Perspective(fovY, aspect, zn, zf);
            }

            void ProjectorComponent::SetOrthogonalMode(float width, float height, float zn, float zf)
            {
                this->ProjectionMatrix.Orthogonal(width, height, zn, zf);
            }
        }
    }
}
