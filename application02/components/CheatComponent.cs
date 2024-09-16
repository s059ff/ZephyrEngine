using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static GameScript;

class CheatComponent : CustomEntityComponent
{
    public bool NoAttack = false;

    public bool FreezePosition = false;

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case PostUpdateMessage:
                this.PostUpdate();
                break;

            default:
                break;
        }
    }

    private void PostUpdate()
    {
        if (NoAttack)
        {
            Entity.ForEach((e) =>
            {
                if (e.Has<AircraftComponent>() && e.Name != "player")
                {
                    var aircraft = e.Get<AircraftComponent>();
                    aircraft.GunFireInput = false;
                    aircraft.MissileLaunchInput = false;
                }
            });
        }

        if (FreezePosition)
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
