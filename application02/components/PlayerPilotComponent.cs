﻿using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using static EngineScript;
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
            this.Owner.Get<AircraftHUDComponent>()?.ChangeRadarRange();
        }

        camera.AngleOffset = new Matrix3x3().Identity().RotateY(AngleOffsetY).RotateX(AngleOffsetX);

        if ((!pressed(KeyCode.LeftCtrl) && nowpressed(KeyCode.D)) || nowpressed(GamePadButton.RSB))
        {
            switch (this.cameraView)
            {
                case CameraView.ThirdPersonPerspective:
                    this.cameraView = CameraView.Cockpit;
                    break;
                case CameraView.Cockpit:
                    this.cameraView = CameraView.ThirdPersonPerspective;
                    break;
                default:
                    break;
            }
        }

        switch (this.cameraView)
        {
            case CameraView.ThirdPersonPerspective:
                camera.TrackingOffset = 0.9f * camera.TrackingOffset + 0.1f * new Vector3(0, 4, -18);
                break;
            case CameraView.Cockpit:
                camera.TrackingOffset = 0.9f * camera.TrackingOffset + 0.1f * aircraft.CockpitPos;
                break;
            default:
                break;
        }

        {
            var distance = (camera.TrackingOffset - aircraft.CockpitPos).Magnitude;
            aircraft.Visibility = clamp(distance / 15, 0, 1);
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

    enum CameraView
    {
        ThirdPersonPerspective,
        Cockpit
    }

    const float TrackingLatency = 12;

    CameraView cameraView = CameraView.ThirdPersonPerspective;

    float AngleOffsetX, AngleOffsetY;

    bool EnableCameraManualTransform = false;
}
