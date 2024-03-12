#include "zephyr.gamesystem\Entity.h"
#include "zephyr.linalg\linalg.h"
#include "zephyr.linalg\Quaternion.h"
#include "zephyr.linalg\Matrix4x3.h"
#include "zephyr.linalg\Vector3.h"

#include "TransformComponent.h"
#include "LightComponent.h"

#define this (*this)

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            void LightComponent::LookAt(linalg::Vector3 eye, linalg::Vector3 at)
            {
                auto& matrix = this.Owner->Get<TransformComponent>()->Matrix;
                matrix.lookAt(eye, at);
            }
        }
    }
}
