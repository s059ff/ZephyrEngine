using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class AbstractPilotComponent : CustomEntityComponent
{
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

    protected virtual void Update()
    {
        var self = this.Owner;
        var aircraft = this.Owner.Get<AircraftComponent>();
        var avionics = this.Owner.Get<AircraftAvionicsComponent>();

        // 機体操作をリセットする
        aircraft.YawInput = 0.0f;
        aircraft.RollInput = 0.0f;
        aircraft.PitchInput = 0.0f;
        aircraft.ThrottleInput = 0.0f;
        aircraft.MissileLaunchInput = false;
        aircraft.GunFireInput = false;
    }
}
