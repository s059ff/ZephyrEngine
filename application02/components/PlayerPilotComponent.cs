using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class PlayerPilotComponent : AbstractPilotComponent
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
        var self = this.Owner;
        var aircraft = this.Owner.Get<AircraftComponent>();
        var avionics = this.Owner.Get<AircraftAvionicsComponent>();

        aircraft.YawInput = 0.0f;
        aircraft.RollInput = 0.0f;
        aircraft.PitchInput = 0.0f;
        aircraft.ThrottleInput = 0.0f;
        aircraft.MissileLaunchInput = false;
        aircraft.GunFireInput = false;

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

        var camera = Entity.Find("camera").Get<CameraComponent>();

        bool changeTargetInput = false;
        bool enableGazingInput = false;
        bool changeRadarRangeInput = false;

        changeTargetInput |= (nowreleased(KeyCode.S) && getPressTimeLength(KeyCode.S) < 15);
        changeTargetInput |= (nowreleased(GamePadButton.Y) && getPressTimeLength(GamePadButton.Y) < 15);

        enableGazingInput |= (pressed(KeyCode.S) && getPressTimeLength(KeyCode.S) >= 15);
        enableGazingInput |= (pressed(GamePadButton.Y) && getPressTimeLength(GamePadButton.Y) >= 15);

        changeRadarRangeInput |= nowpressed(KeyCode.A);
        changeRadarRangeInput |= nowpressed(GamePadButton.X);

        if (!isConnectedGamePad())
        {
            if (pressed(KeyCode.J))
                AngleOffsetY = 0.9f * AngleOffsetY + 0.1f * -PI;
            if (pressed(KeyCode.L))
                AngleOffsetY = 0.9f * AngleOffsetY + 0.1f * +PI;
            if (!pressed(KeyCode.J) && !pressed(KeyCode.L))
                AngleOffsetY *= 0.9f;

            if (pressed(KeyCode.I))
                AngleOffsetX = 0.9f * AngleOffsetX + 0.1f * -PIOver2;
            if (pressed(KeyCode.K))
                AngleOffsetX = 0.9f * AngleOffsetX + 0.1f * +PIOver2;
            if (!pressed(KeyCode.I) && !pressed(KeyCode.K))
                AngleOffsetX *= 0.9f;
        }
        else
        {
            AngleOffsetY = 0.9f * AngleOffsetY + 0.1f * (float)getAnalogStickSubAxis().Item1 * PI;
            AngleOffsetX = 0.9f * AngleOffsetX + 0.1f * (float)getAnalogStickSubAxis().Item2 * -PIOver2;
        }

        if (changeTargetInput)
        {
            avionics.ChangeTarget();
        }
        if (enableGazingInput && avionics.TargetEntity != null)
        {
            camera.GazingPoint = avionics.TargetEntity.Get<TransformComponent>().Position;
            camera.EnableGazing = true;
        }
        else
        {
            camera.EnableGazing = false;
        }
        if (changeRadarRangeInput)
        {
            var entity = Entity.Find("ui");
            if (entity != null)
            {
                entity.Get<UIComponent>().ChangeRadarRange();
            }
        }

        camera.AngleOffset = new Matrix3x3().Identity().RotateY(AngleOffsetY).RotateX(AngleOffsetX);

        if (!pressed(KeyCode.LeftCtrl) && nowpressed(KeyCode.D) || nowpressed(GamePadButton.RSB))
        {
            HUDView = !HUDView;
        }

        aircraft.Visible = true;
        if (HUDView)
        {
            camera.TrackingOffset = 0.9f * camera.TrackingOffset + 0.1f * aircraft.CockpitPos;
        }
        else
        {
            camera.TrackingOffset = 0.9f * camera.TrackingOffset + 0.1f * new Vector3(0, 4, -18);
        }

        {
            var distance = (camera.TrackingOffset - aircraft.CockpitPos).Magnitude;
            var alpha = clamp(distance / 15, 0, 1);
            aircraft.Opacity = 1 - alpha;
            if (alpha < .99f)
            {
                aircraft.Visible = false;
            }
        }

        if (nowpressed(KeyCode.F1))
        {
            EnableCameraManualTransform = !EnableCameraManualTransform;
        }

        if (EnableCameraManualTransform)
        {
            camera.EnableTracking = false;
        }
        else
        {
            camera.EnableTracking = true;
            camera.TrackingPose = this.Transform.Matrix;
            camera.TrackingLatency = (int)TrackingLatency;
        }
    }

    bool HUDView = false;

    const float TrackingLatency = 12;

    float AngleOffsetX, AngleOffsetY;

    bool EnableCameraManualTransform = false;
}
