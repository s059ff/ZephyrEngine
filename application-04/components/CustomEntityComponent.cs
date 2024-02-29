using System;
using System.Collections.Generic;
using System.IO;
using System.Reflection;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
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

        transform = null;
        physics = null;
        collision = null;
    }

    private void Update()
    {
        transform = this.Owner.Get<TransformComponent>();
        physics = this.Owner.Get<PhysicsComponent>();
        collision = this.Owner.Get<CollisionComponent>();
    }

    protected TransformComponent Transform { get { return transform; } }
    protected PhysicsComponent Physics { get { return physics; } }
    protected CollisionComponent Collision { get { return collision; } }

    protected Matrix4x4 WorldMatrix { get { return new Matrix4x4(Transform.Matrix); } }
    protected Matrix4x4 ViewingMatrix { get { return CustomCameraComponent.ViewingMatrix; } }
    protected Matrix4x4 ProjectionMatrix { get { return CustomProjectorComponent.ProjectionMatrix; } }
    protected Matrix4x4 WVPMatrix { get { return WorldMatrix * ViewingMatrix * ProjectionMatrix; } }

    TransformComponent transform;
    PhysicsComponent physics;
    CollisionComponent collision;
}
