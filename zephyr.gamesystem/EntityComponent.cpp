#include "EntityComponent.h"
#include "Entity.h"

namespace zephyr
{
    namespace gamesystem
    {
        void EntityComponent::_set_Owner(Entity* value)
        {
            runtime_assert(value != nullptr);
            value->Attach(this);
        }
    }
}
