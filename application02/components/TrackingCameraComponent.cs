using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class TrackingCameraComponent : AbstractCameraComponent
{
    protected override void Update()
    {
        var player = Entity.Find("player");
        var transform = player?.Get<TransformComponent>();
        var aircraft = player?.Get<AircraftComponent>();
        var avionics = player?.Get<AircraftAvionicsComponent>();

        if (player == null || transform == null || aircraft == null || avionics == null)
            return;

        this.angleOffset.X = 0.9f * this.angleOffset.X;
        this.angleOffset.Y = 0.9f * this.angleOffset.Y;

        this.angleOffset.Y += 0.1f * (float)getAnalogStickAxis2().Item1 * PI;
        this.angleOffset.X += 0.1f * (float)getAnalogStickAxis2().Item2 * -PIOver2;

        this.angleOffset2.X = 0.9f * this.angleOffset2.X;
        this.angleOffset2.Y = 0.9f * this.angleOffset2.Y;

        if (getPressTimeLength(GamePad.LogicalButton.Y) > 15 && avionics.TargetEntity != null)
        {
            Vector3 from = transform.Position;
            Vector3 at = avionics.TargetEntity.Get<TransformComponent>().Position;
            Matrix3x3 rotation = transform.Matrix._Matrix3x3;
            Vector3 dir = (at - from) * rotation.Inverse;

            float dx = -atan2(dir.Y, abs(dir.Z));
            float dy = atan2(dir.X, dir.Z);

            this.angleOffset2.X += 0.1f * dx;
            this.angleOffset2.Y += 0.1f * dy;
        }

        if (nowpressed(GamePad.LogicalButton.RSB))
        {
            switch (this.cameraView)
            {
                case CameraView.ThirdPersonPerspective:
                    this.cameraView = CameraView.Cockpit;
                    break;
                case CameraView.Cockpit:
                    this.cameraView = CameraView.ThirdPersonPerspective;
                    break;
            }
        }

        switch (this.cameraView)
        {
            case CameraView.ThirdPersonPerspective:
                this.trackingOffset = 0.9f * this.trackingOffset + 0.1f * new Vector3(0, 4, -18);
                break;
            case CameraView.Cockpit:
                this.trackingOffset = 0.9f * this.trackingOffset + 0.1f * aircraft.Parameter.CockpitPos;
                break;
            default:
                break;
        }

        {
            var distance = (this.trackingOffset - aircraft.Parameter.CockpitPos).Magnitude;
            aircraft.Visibility = clamp(distance / 15.0f, 0.0f, 1.0f);
        }
    }

    protected override void ApplyCameraTransform()
    {
        var player = Entity.Find("player");
        var transform = player?.Get<TransformComponent>();
        var angleOffset = new Matrix3x3().Identity()
            .RotateY(this.angleOffset.Y + this.angleOffset2.Y)
            .RotateX(this.angleOffset.X + this.angleOffset2.X);
        var rotation = angleOffset * transform.Matrix._Matrix3x3;
        var position = this.trackingOffset * rotation + transform.Position;
        this.Owner.Get<TransformComponent>().Matrix = new Matrix4x3(rotation);
        this.Owner.Get<TransformComponent>().Position = position;
    }

    enum CameraView
    {
        ThirdPersonPerspective,
        Cockpit
    }
    CameraView cameraView = CameraView.ThirdPersonPerspective;

    Vector2 angleOffset = new Vector2();
    Vector2 angleOffset2 = new Vector2();

    Vector3 trackingOffset = new Vector3();
}
