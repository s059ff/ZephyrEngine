using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static GameScript;

class CheatComponent : CustomEntityComponent
{
    public bool NoDamage = false;

    public bool FixOtherAircrafts = false;

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        if (NoDamage)
        {
            Entity entity = Entity.Find("player");
            AircraftComponent aircraft = entity?.Get<AircraftComponent>();
            if (aircraft != null)
            {
                aircraft.Armor = 1.0f;
            }
        }

        if (FixOtherAircrafts)
        {
            Entity.ForEach((e) =>
            {
                if (e.Has<AircraftComponent>() && e.Name != "player")
                {
                    var physics = e.Get<PhysicsComponent>();
                    if (physics != null)
                    {
                        physics.Velocity = Vector3.Zero;
                        physics.AngularVelocity = Vector3.Zero;
                        physics.Force = Vector3.Zero;
                        physics.Torque = Vector3.Zero;
                    }
                }
            });
        }
    }
}
