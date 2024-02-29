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

        if (pressed(KeyCode.Q))
        {
            aircraft.Yaw(-1.0f);
        }
        if (pressed(KeyCode.E))
        {
            aircraft.Yaw(1.0f);
        }

        if (pressed(KeyCode.Left))
        {
            aircraft.Roll(-1.0f);
        }
        if (pressed(KeyCode.Right))
        {
            aircraft.Roll(1.0f);
        }
        if (pressed(KeyCode.Up))
        {
            aircraft.Pitch(1.0f);
        }
        if (pressed(KeyCode.Down))
        {
            aircraft.Pitch(-1.0f);
        }

        if (pressed(KeyCode.Left) && pressed(KeyCode.Right) && avionics.HasTarget())
        {
            aircraft.AutoPilot(GunBulletComponent.ComputeOptimalAimPosition(this.Owner, avionics.TargetEntity));
        }
        if (pressed(KeyCode.Z))
        {
            aircraft.DesiredPower = aircraft.DesiredPower + 0.004f;
        }
        if (pressed(KeyCode.X))
        {
            aircraft.DesiredPower = aircraft.DesiredPower - 0.004f;
        }
        if (nowpressed(KeyCode.C))
        {
            aircraft.Launch();
        }
        if (pressed(KeyCode.V))
        {
            aircraft.Fire();
        }
        if (!pressed(KeyCode.LeftCtrl) && !pressed(KeyCode.RightCtrl))
        {
            if (nowreleased(KeyCode.S))
            {
                if (GazeKeyPressedTime < 1.0f)
                    avionics.ChangeTarget();
            }
            if (nowreleased(KeyCode.A))
            {
                Entity.Find("ui").Get<UIComponent>().ChangeRadarRange();
            }
        }

#if false
        if (nowreleased(KeyCode.Left))
        {
            released_frame_left = frame;
        }
        if (nowpressed(KeyCode.Left) && (frame - released_frame_left < 10))
        {
            aircraft.Roll(-10.0f);
            aircraft.Pitch(-60.0f);
        }

        if (nowreleased(KeyCode.Right))
        {
            released_frame_right = frame;
        }
        if (nowpressed(KeyCode.Right) && (frame - released_frame_right < 10))
        {
            aircraft.Roll(10.0f);
            aircraft.Pitch(-60.0f);
        } 

        if (nowreleased(KeyCode.Up))
        {
            released_frame_up = frame;
        }
        if (nowpressed(KeyCode.Up) && (frame - released_frame_up < 10))
        {
        }
#endif

        if (nowreleased(KeyCode.Down))
        {
            ReleasedFrameDown = frame;
        }
        if (nowpressed(KeyCode.Down) && (frame - ReleasedFrameDown < 10))
        {
            aircraft.Avoid();
        }

        if (pressed(KeyCode.S))
            GazeKeyPressedTime += 0.1f;
        else
            GazeKeyPressedTime = 0;

        var camera = Entity.Find("camera").Get<CameraComponent>();
        camera.EnableGazing = false;

        bool angleOffsetChangedX = false, angleOffsetChangedY = false;

        if (pressed(KeyCode.LeftCtrl) || pressed(KeyCode.RightCtrl))
        {
            if (pressed(KeyCode.A))
            {
                AngleOffsetY = 0.9f * AngleOffsetY + 0.1f * -PI;
                angleOffsetChangedY = true;
            }
            if (pressed(KeyCode.D))
            {
                AngleOffsetY = 0.9f * AngleOffsetY + 0.1f * PI;
                angleOffsetChangedY = true;
            }
            if (pressed(KeyCode.W))
            {
                AngleOffsetX = 0.9f * AngleOffsetX + 0.1f * -PIOver2;
                angleOffsetChangedX = true;
            }
            if (pressed(KeyCode.S))
            {
                AngleOffsetX = 0.9f * AngleOffsetX + 0.1f * PIOver2;
                angleOffsetChangedX = true;
            }
        }
        else
        {
            if (avionics.TargetEntity != null)
            {
                camera.GazingPoint = avionics.TargetEntity.Get<TransformComponent>().Position;
                camera.EnableGazing = (1.0f < GazeKeyPressedTime);
            }
            else
            {
                camera.EnableGazing = false;
            }
        }
        if (!angleOffsetChangedX)
            AngleOffsetX *= 0.9f;
        if (!angleOffsetChangedY)
            AngleOffsetY *= 0.9f;
        camera.AngleOffset = new Matrix3x3().Identity().RotateY(AngleOffsetY).RotateX(AngleOffsetX);

        if (!pressed(KeyCode.LeftCtrl) && nowpressed(KeyCode.D))
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

    float GazeKeyPressedTime = 0;

    int ReleasedFrameDown = 0;

    bool HUDView = false;

    const float TrackingLatency = 12;

    float AngleOffsetX, AngleOffsetY;

    bool EnableCameraManualTransform = false;
}
