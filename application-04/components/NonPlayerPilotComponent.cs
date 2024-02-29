using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class NonPlayerPilotComponent : AbstractPilotComponent
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

    private void Update()
    {
        var aircraft = this.Owner.Get<AircraftComponent>();
        aircraft.AutoPilot(new Vector3(0, 2000, 0));
    }
}