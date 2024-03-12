#include "zephyr\math.h"

#include "ProjectorComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            ProjectorComponent::ProjectorComponent()
            {
                this->SetPerspectiveMode(PI<> / 3, 4.0f / 3.0f, 1.0f, 128.0f);
            }

            void ProjectorComponent::SetPerspectiveMode(float fovY, float aspect, float zn, float zf)
            {
                this->ProjectionMatrix.perspective(fovY, aspect, zn, zf);
            }

            void ProjectorComponent::SetOrthogonalMode(float width, float height, float zn, float zf)
            {
                this->ProjectionMatrix.orthogonal(width, height, zn, zf);
            }
        }
    }
}
