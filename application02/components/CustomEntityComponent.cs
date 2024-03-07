using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static GameScript;

public class CustomEntityComponent : EntityComponent
{
    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;
        }
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        this.Update();
    }

    protected override void OnDetach()
    {
        base.OnDetach();

        this.Transform = null;
        this.Physics = null;
        this.Collision = null;
    }

    private void Update()
    {
        this.Transform = this.Owner.Get<TransformComponent>();
        this.Physics = this.Owner.Get<PhysicsComponent>();
        this.Collision = this.Owner.Get<CollisionComponent>();
    }

    protected TransformComponent Transform { get; private set; }
    protected PhysicsComponent Physics { get; private set; }
    protected CollisionComponent Collision { get; private set; }

    protected Matrix4x4 WorldMatrix { get { return new Matrix4x4(Transform.Matrix); } }
    protected Matrix4x4 ViewingMatrix
    {
        get
        {
            return new Matrix4x4(Entity.Find("camera").Get<CameraComponent>().ViewingMatrix);
        }
    }
    protected Matrix4x4 ProjectionMatrix
    {
        get
        {
            return Entity.Find("projector").Get<ProjectorComponent>().ProjectionMatrix;
        }
    }
    protected Matrix4x4 WVPMatrix { get { return WorldMatrix * ViewingMatrix * ProjectionMatrix; } }
}
