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

    private void Update()
    {
        var aircraft = this.Owner.Get<AircraftComponent>();
        aircraft.YawInput = 0.0f;
        aircraft.RollInput = 0.0f;
        aircraft.PitchInput = 0.0f;
        aircraft.ThrottleInput = 0.0f;
        aircraft.MissileLaunchInput = false;
        aircraft.GunFireInput = false;
    }
}
