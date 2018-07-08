//using ZephyrSharp.AI;
using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
//using ZephyrTools.StateMachineMonitor;
using static Script;

public class NPCAIComponent : CustomEntityComponent
{
    //StateMachine StateMachine;
    Entity ThreatMissile;
    Entity TargetEntity;

    //StateMachineMonitor StateMachineMonitor;
    bool ShowStateMachine;

    public NPCAIComponent(bool showStateMachine = false)
    {
        //StateMachine = new StateMachine();
        //StateMachine.DefineState("attack");
        //StateMachine.DefineState("retreat");
        //StateMachine.DefineState("avoid missile");
        //StateMachine.DefineState("do nothing");

        ShowStateMachine = showStateMachine;
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        var squadronComponent = this.Owner.Get<SquadronComponent>();

        //if (ShowStateMachine)
        //    StateMachineMonitor = StateMachineMonitor.Execute(StateMachine, squadronComponent.SquadronName + squadronComponent.Number);
    }

    protected override void OnDetach()
    {
        base.OnDetach();

        //if (StateMachineMonitor != null)
        //{
        //    StateMachineMonitor.Shutdown(StateMachineMonitor);
        //    StateMachineMonitor = null;
        //}
    }

    protected override void OnDestroy()
    {
        base.OnDestroy();
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        if (message as string == UpdateMessage)
        {
            this.Update();
        }
    }

    private void Update()
    {
        var aircraft = Owner.Get<AircraftComponent>();
        if (aircraft.Armor == 0.0f)
            return;

        var ai = Owner.Get<AIComponent>();
        var squadron = Owner.Get<SquadronComponent>();
        if (squadron.Number != 0 && squadron.SquadronLeader != null && squadron.SquadronLeader.IsAlive)
        {
            ai.SetSameTarget(squadron.SquadronLeader.Get<AIComponent>());
        }

        this.TargetEntity = ai.TargetEntity;

        //this.UpdateStateMachine();

        if (this.TargetEntity == null || !this.TargetEntity.IsAlive)
            return;

        Vector3 targetPosition = new Vector3();
        //switch (StateMachine.CurrentState)
        //{
        //    case "attack":
        //        {
        //            //targetPosition = this.TargetEntity.Get<TransformComponent>().Position + this.TargetEntity.Get<PhysicsComponent>().Velocity * 180;

        //            var distance = (this.Transform.Position - this.TargetEntity.Get<TransformComponent>().Position).Magnitude;
        //            targetPosition = GunBulletComponent.ComputeOptimalAimPosition(this.Owner, this.TargetEntity);

        //            if (uniform(0, 600) == 0 && aircraft.Locking)
        //            {
        //                aircraft.Launch();
        //            }

        //            if (distance < 800 && Vector3.Angle(this.Transform.Forward, targetPosition - this.Transform.Position) < deg2rad(10))
        //            {
        //                aircraft.Fire();
        //            }

        //            aircraft.DesiredPower = 1.0f;
        //        }
        //        break;
        //    case "retreat":
        //        {
        //            if (squadron.Number == 0 || squadron.SquadronLeader == null || !squadron.SquadronLeader.IsAlive)
        //            {
        //                targetPosition = TargetEntity.Get<TransformComponent>().Position;
        //                targetPosition = Transform.Position + (Transform.Position - targetPosition);
        //                targetPosition.Y = Transform.Position.Y;
        //            }
        //            else
        //            {
        //                targetPosition = squadron.SquadronLeader.Get<TransformComponent>().Position;
        //            }
        //            aircraft.DesiredPower = 0.8f;
        //        }
        //        break;
        //    case "avoid missile":
        //        {
        //            if (ThreatMissile != null)
        //                targetPosition = ThreatMissile.Get<TransformComponent>().Position;
        //            aircraft.DesiredPower = 0.8f;
        //        }
        //        break;
        //    case "do nothing":
        //        {
        //            if (squadron.SquadronLeader != null)
        //            {
        //                targetPosition = squadron.SquadronLeader.Get<TransformComponent>().Position;
        //            }
        //            else
        //            {
        //                targetPosition = Transform.Position + Transform.Forward;
        //                targetPosition.Y = Transform.Position.Y;
        //            }
        //            aircraft.DesiredPower = 0.6f;
        //        }
        //        break;
        //    default:
        //        break;
        //}

        var curvedSurface = (Entity.Find("ground").Get<CollisionComponent>().Object as CurvedSurfaceCollisionObject);
        float height = curvedSurface.ComputeHeight(Transform.Position);

        if (height < 500)
        {
            float k = height / 500;
            k = clamp(k, 0, 1);
            k = 1 - k;
            var distance = (targetPosition - Transform.Position).Magnitude;
            targetPosition = (1 - k) * targetPosition + k * (Transform.Position + new Vector3(0, distance, 0));
            aircraft.DesiredPower = (1 - k) * aircraft.DesiredPower + k * 0.8f;
        }
        Owner.Get<AircraftComponent>().AutoPilot(targetPosition);
    }
}
