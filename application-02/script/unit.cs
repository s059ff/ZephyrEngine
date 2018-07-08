#include "common.csh"

Entity unit(string name, string squadronName, Vector3 pos, float angle)
{
    Entity entity = Entity.Instantiate();
    entity.Name = name;
    entity.Attach(new TransformComponent());
    entity.Attach(new PhysicsComponent());
    entity.Attach(new CollisionComponent());
    entity.Attach(new JetComponent());
    entity.Attach(new AircraftComponent());
    entity.Attach(new AIComponent(Enemy));
    if (name == "player")
        entity.Attach(new PlayerComponent());
    else
        entity.Attach(new NPCAIComponent());
    entity.Attach(new SquadronComponent(squadronName));
    entity.Attach(new SoundComponent(JetSound));
    entity.Get<TransformComponent>().Matrix.RotateY(angle);
    entity.Get<TransformComponent>().Position = pos;
    entity.Get<SoundComponent>().LoopPlay();

    return entity;
}
