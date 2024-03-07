#include "common.csh"

Entity instantiate()
{
    return Entity.Instantiate();
}

void kill(Entity e)
{
    assert(e != null, "Null reference exception.");
    Entity.Kill(e);
}

void attach(Entity entity, EntityComponent comp)
{
    entity.Attach(comp);
}

void attach<Component>(Entity entity) where Component : EntityComponent, new()
{
    entity.Attach(new Component());
}
