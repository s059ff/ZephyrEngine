using ZephyrSharp.GameSystem;
using ZephyrSharp.Input;
using static GameScript;

class PlayerPilotComponent : AbstractPilotComponent
{
    protected override void Update()
    {
        base.Update();

        var self = this.Owner;
        var aircraft = this.Owner.Get<AircraftComponent>();
        var avionics = this.Owner.Get<AircraftAvionicsComponent>();

        aircraft.YawInput += pressed(GamePad.LogicalButton.LT) ? -1.0f : 0.0f;
        aircraft.YawInput += pressed(GamePad.LogicalButton.RT) ? +1.0f : 0.0f;
        aircraft.RollInput += (float)getAnalogStickAxis1().Item1;
        aircraft.PitchInput += (float)getAnalogStickAxis1().Item2;
        aircraft.ThrottleInput += pressed(GamePad.LogicalButton.RB) ? +1.0f : 0.0f;
        aircraft.ThrottleInput += pressed(GamePad.LogicalButton.LB) ? -1.0f : 0.0f;
        aircraft.MissileLaunchInput = nowpressed(GamePad.LogicalButton.B);
        aircraft.GunFireInput = pressed(GamePad.LogicalButton.A);

        if (pressed(GamePad.LogicalButton.LB) && pressed(GamePad.LogicalButton.RB) && avionics.HasTarget())
        {
            aircraft.AutoPilot(GunBulletComponent.ComputeOptimalAimPosition(this.Owner, avionics.TargetEntity));
        }

        {
            bool changeRadarRangeInput = false;
            changeRadarRangeInput |= nowpressed(GamePad.LogicalButton.X);

            if (changeRadarRangeInput)
            {
                this.Owner.Get<AircraftHUDComponent>()?.ChangeRadarRange();
            }
        }

        {
            bool changeTargetInput = false;
            changeTargetInput |= (nowreleased(GamePad.LogicalButton.Y) && getPressTimeLength(GamePad.LogicalButton.Y) < 15);

            if (changeTargetInput)
            {
                this.Owner.Get<AircraftAvionicsComponent>()?.ChangeTarget();
            }
        }

        {
            Entity entity = Entity.Find("camera");
            AbstractCameraComponent activeCameraComponent = null;

            if (nowpressed(Keyboard.KeyCode.F1))
                activeCameraComponent = entity.Get<TrackingCameraComponent>();
            if (nowpressed(Keyboard.KeyCode.F2))
                activeCameraComponent = entity.Get<FixedPointCameraComponent>();
            if (nowpressed(Keyboard.KeyCode.F3))
                activeCameraComponent = entity.Get<GunCameraComponent>();
            if (aircraft.Armor == 0)
                activeCameraComponent = entity.Get<FixedPointCameraComponent>();

            if (activeCameraComponent != null)
            {
                activeCameraComponent.Activate();
            }
        }
    }
}
