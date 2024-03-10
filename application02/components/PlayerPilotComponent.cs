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

        aircraft.YawInput += pressed(KeyCode.Q) || pressed(GamePadButton.LB) ? -1.0f : 0.0f;
        aircraft.YawInput += pressed(KeyCode.E) || pressed(GamePadButton.RB) ? +1.0f : 0.0f;

        aircraft.RollInput += pressed(KeyCode.Left) ? -1.0f : 0.0f;
        aircraft.RollInput += pressed(KeyCode.Right) ? +1.0f : 0.0f;
        aircraft.RollInput += (float)getAnalogStickAxis().Item1;

        aircraft.PitchInput += pressed(KeyCode.Up) ? +1.0f : 0.0f;
        aircraft.PitchInput += pressed(KeyCode.Down) ? -1.0f : 0.0f;
        aircraft.PitchInput += (float)getAnalogStickAxis().Item2;

        aircraft.ThrottleInput += pressed(KeyCode.Z) || pressed(GamePadButton.RT) ? +1.0f : 0.0f;
        aircraft.ThrottleInput += pressed(KeyCode.X) || pressed(GamePadButton.LT) ? -1.0f : 0.0f;

        aircraft.MissileLaunchInput = nowpressed(KeyCode.C) || nowpressed(GamePadButton.B);
        aircraft.GunFireInput = pressed(KeyCode.V) || pressed(GamePadButton.A);

        if (pressed(KeyCode.Left) && pressed(KeyCode.Right) && avionics.HasTarget())
        {
            aircraft.AutoPilot(GunBulletComponent.ComputeOptimalAimPosition(this.Owner, avionics.TargetEntity));
        }

        {
            bool changeRadarRangeInput = false;
            changeRadarRangeInput |= nowpressed(KeyCode.A);
            changeRadarRangeInput |= nowpressed(GamePadButton.X);

            if (changeRadarRangeInput)
            {
                this.Owner.Get<AircraftHUDComponent>()?.ChangeRadarRange();
            }
        }

        {
            bool changeTargetInput = false;
            changeTargetInput |= (nowreleased(KeyCode.S) && getPressTimeLength(KeyCode.S) < 15);
            changeTargetInput |= (nowreleased(GamePadButton.Y) && getPressTimeLength(GamePadButton.Y) < 15);

            if (changeTargetInput)
            {
                this.Owner.Get<AircraftAvionicsComponent>()?.ChangeTarget();
            }
        }

        {
            Entity entity = Entity.Find("camera");
            AbstractCameraComponent activeCameraComponent = null;

            if (nowpressed(KeyCode.F1))
                activeCameraComponent = entity.Get<TrackingCameraComponent>();
            if (nowpressed(KeyCode.F2))
                activeCameraComponent = entity.Get<FixedPointCameraComponent>();
            if (aircraft.Armor == 0)
                activeCameraComponent = entity.Get<FixedPointCameraComponent>();

            if (activeCameraComponent != null)
            {
                activeCameraComponent.Activate();
            }
        }
    }
}
