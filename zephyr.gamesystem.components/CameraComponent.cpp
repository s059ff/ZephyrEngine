#include "zephyr.gamesystem\Entity.h"
#include "zephyr.linalg\linalg.h"
#include "zephyr.linalg\Quaternion.h"
#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.linalg\Vector3.h"

#include "TransformComponent.h"
#include "CameraComponent.h"

#define this (*this)

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            void CameraComponent::LookAt(linalg::Vector3 eye, linalg::Vector3 at)
            {
                auto& matrix = this.Owner->Get<TransformComponent>()->Matrix;
                matrix.lookAt(eye, at);
            }

            linalg::Matrix4x3 CameraComponent::_get_ViewingMatrix() const
            {
                auto& matrix = this.Owner->Get<TransformComponent>()->Matrix;
                return matrix.inverse;
            }
        }
    }
}
