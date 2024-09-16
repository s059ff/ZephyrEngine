using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;

class GunCameraComponent : AbstractCameraComponent
{
    protected override void PostUpdate()
    {
    }

    protected override void ApplyCameraTransform()
    {
        var player = Entity.Find("player");
        var transform = player?.Get<TransformComponent>();
        var aircraft = player?.Get<AircraftComponent>();

        if (transform != null && aircraft != null)
        {
            Matrix4x3 m = new Matrix4x3().Identity().Translate(aircraft.ModelRef.Weapon.GunPos + new Vector3(0.0f, 1.0f, 1.0f));
            this.Transform.Matrix = m * transform.Matrix;
        }
    }
}
