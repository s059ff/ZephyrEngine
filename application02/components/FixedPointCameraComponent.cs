using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;

class FixedPointCameraComponent : AbstractCameraComponent
{
    protected override void Update()
    {
        var transform = Entity.Find("player")?.Get<TransformComponent>();
        if (transform != null)
        {
            this.offsetPosition = transform.Position;
        }
    }

    protected override void ApplyCameraTransform()
    {
        var delta = new Vector3(-100, 100, -100);
        var at = this.offsetPosition;
        var from = delta + at;
        this.Owner.Get<TransformComponent>().Matrix.LookAt(from, at);
    }

    private Vector3 offsetPosition = Vector3.Zero;
}
