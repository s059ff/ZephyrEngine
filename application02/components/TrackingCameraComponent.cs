using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class TrackingCameraComponent : AbstractCameraComponent
{
    public TrackingCameraComponent()
    {
        for (int i = 0; i < TrackingLatency; i++)
        {
            this.targetRotationHistory.AddFirst(new Matrix3x3().Identity());
            this.targetPositionHistroy.AddFirst(new Vector3());
        }
        assert(this.targetRotationHistory.Count == TrackingLatency);
        assert(this.targetPositionHistroy.Count == TrackingLatency);
    }

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

        if (!isConnectedGamePad())
        {
            if (pressed(KeyCode.J))
                this.angleOffset.Y += 0.1f * -PI;
            if (pressed(KeyCode.L))
                this.angleOffset.Y += 0.1f * +PI;
            if (pressed(KeyCode.I))
                this.angleOffset.X += 0.1f * -PIOver2;
            if (pressed(KeyCode.K))
                this.angleOffset.X += 0.1f * +PIOver2;
        }
        else
        {
            this.angleOffset.Y += 0.1f * (float)getAnalogStickSubAxis().Item1 * PI;
            this.angleOffset.X += 0.1f * (float)getAnalogStickSubAxis().Item2 * -PIOver2;
        }

        this.angleOffset2.X = 0.9f * this.angleOffset2.X;
        this.angleOffset2.Y = 0.9f * this.angleOffset2.Y;

        if (max(getPressTimeLength(KeyCode.S), getPressTimeLength(GamePadButton.Y)) > 15 && avionics.TargetEntity != null)
        {
            Vector3 from = transform.Position;
            Vector3 at = avionics.TargetEntity.Get<TransformComponent>().Position;
            Matrix3x3 rotation = this.targetRotationHistory.Last.Value;
            Vector3 dir = (at - from) * rotation.Inverse;

            float dx = -atan2(dir.Y, abs(dir.Z));
            float dy = atan2(dir.X, dir.Z);

            this.angleOffset2.X += 0.1f * dx;
            this.angleOffset2.Y += 0.1f * dy;
        }

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
            }
        }

        switch (this.cameraView)
        {
            case CameraView.ThirdPersonPerspective:
                this.trackingOffset = 0.9f * this.trackingOffset + 0.1f * new Vector3(0, 4, -18);
                break;
            case CameraView.Cockpit:
                this.trackingOffset = 0.9f * this.trackingOffset + 0.1f * aircraft.CockpitPos;
                break;
            default:
                break;
        }

        {
            var distance = (this.trackingOffset - aircraft.CockpitPos).Magnitude;
            aircraft.Visibility = clamp(distance / 15.0f, 0.0f, 1.0f);
        }

        this.targetRotationHistory.RemoveLast();
        this.targetRotationHistory.AddFirst(transform.Matrix._Matrix3x3);

        this.targetPositionHistroy.RemoveLast();
        this.targetPositionHistroy.AddFirst(transform.Position);
    }

    protected override void ApplyCameraTransform()
    {
        var angleOffset = new Matrix3x3().Identity()
            .RotateY(this.angleOffset.Y + this.angleOffset2.Y)
            .RotateX(this.angleOffset.X + this.angleOffset2.X);
        var rotation = angleOffset * this.targetRotationHistory.Last.Value;
        var position = this.trackingOffset * rotation + this.targetPositionHistroy.First.Value;
        this.Owner.Get<TransformComponent>().Matrix = new Matrix4x3(rotation);
        this.Owner.Get<TransformComponent>().Position = position;
    }

    const float TrackingLatency = 12;

    enum CameraView
    {
        ThirdPersonPerspective,
        Cockpit
    }
    CameraView cameraView = CameraView.ThirdPersonPerspective;

    Vector2 angleOffset = new Vector2();
    Vector2 angleOffset2 = new Vector2();

    LinkedList<Matrix3x3> targetRotationHistory = new LinkedList<Matrix3x3>();
    LinkedList<Vector3> targetPositionHistroy = new LinkedList<Vector3>();

    Vector3 trackingOffset = new Vector3();
}
