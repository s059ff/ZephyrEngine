#include "EntityComponent.h"
#include "Entity.h"

namespace ZephyrSharp
{
    namespace GameSystem
    {
        void EntityComponent::Owner::set(Entity^ value)
        {
            runtime_assert(value != nullptr);
            value->Attach(this);
        }
    }
}
