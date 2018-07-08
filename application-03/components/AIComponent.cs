using System.Collections.Generic;
using System.Linq;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class AIComponent : CustomEntityComponent
{
    const float AngleThreshold = PI / 4;

    static List<AIComponent> AllComponent;

    readonly List<AIComponent> CandidateTargets;
    readonly List<AIComponent> ExcludedTargets;

    public AIComponent Target
    {
        get
        {
            return ExcludedTargets.Count > 0 ? ExcludedTargets.Last() : null;
        }
        set
        {
            // ミサイルロックオン状態を解除する
            var aircraftComponent = this.Owner.Get<AircraftComponent>();
            if (aircraftComponent.ActiveMissile != null)
            {
                aircraftComponent.ActiveMissile.ResetTarget();
            }

            var target = value;
            if (target == null)
            {
                this.CandidateTargets.AddRange(this.ExcludedTargets);
                this.ExcludedTargets.Clear();
            }
            else
            {
                this.CandidateTargets.Remove(target);
                this.ExcludedTargets.Remove(target);
                this.ExcludedTargets.Add(target);
            }
        }
    }
    public Entity TargetEntity { get { return Target != null ? Target.Owner : null; } }
    public readonly int Group;

    static AIComponent()
    {
        AllComponent = new List<AIComponent>();
    }

    public AIComponent(int group)
    {
        this.Group = group;

        this.CandidateTargets = new List<AIComponent>();
        this.ExcludedTargets = new List<AIComponent>();
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        // 自分以外のすべてのユニットをターゲットリストに入れる
        this.CandidateTargets.AddRange(AllComponent.Where(e => e.Group != this.Group));

        // 自分以外のすべてのユニットのターゲットリストに自分を入れる
        foreach (var other in this.CandidateTargets)
        {
            other.CandidateTargets.Add(this);

            if (other.Target == null)
            {
                other.ChangeTarget();
            }
        }

        // 自分をユニット一覧に入れる
        AllComponent.Add(this);
    }

    protected override void OnDetach()
    {
        base.OnDetach();

        // すべてのユニットのターゲットリストから自分を除外する
        foreach (var unit in AllComponent)
        {
            unit.CandidateTargets.Remove(this);
            unit.ExcludedTargets.Remove(this);
        }

        // ユニット一覧から自分を除外する
        AllComponent.Remove(this);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            case KillMessage:
                var camera = Entity.Find("camera").Get<CameraComponent>();
                //if (argument == camera.GazeTarget)
                //{
                //    camera.GazeTarget = null;
                //}
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        this.SortTargetList();

        if (this.Target == null)
            this.ChangeTarget();
    }

    public void ChangeTarget()
    {
        // ミサイルロックオン状態を解除する
        if (this.Owner.Get<AircraftComponent>().ActiveMissile != null)
        {
            this.Owner.Get<AircraftComponent>().ActiveMissile.ResetTarget();
        }

        // 候補がなくなったら除外リストを候補リストに転送
        if (this.CandidateTargets.Count == 0)
        {
            this.CandidateTargets.AddRange(this.ExcludedTargets);
            this.ExcludedTargets.Clear();
        }

        if (this.CandidateTargets.Count > 0)
        {
            // 候補リストの先頭要素をアクティブターゲットにする
            // アクティブターゲットは除外リストに入れる
            this.ExcludedTargets.Add(this.CandidateTargets.First());
            this.CandidateTargets.RemoveAt(0);
        }
    }

    public void ResetTarget()
    {
        this.CandidateTargets.AddRange(this.ExcludedTargets);
        this.ExcludedTargets.Clear();
        this.SortTargetList();
        this.ChangeTarget();
    }

    public void SetTarget(AIComponent target)
    {
        // ミサイルロックオン状態を解除する
        var aircraftComponent = this.Owner.Get<AircraftComponent>();
        if (aircraftComponent.ActiveMissile != null)
        {
            aircraftComponent.ActiveMissile.ResetTarget();
        }

        if (target == null)
        {
            this.CandidateTargets.AddRange(this.ExcludedTargets);
            this.ExcludedTargets.Clear();
        }
        else
        {
            this.CandidateTargets.Remove(target);
            this.ExcludedTargets.Remove(target);
            this.ExcludedTargets.Add(target);
        }
    }

    public void SetSameTarget(AIComponent one)
    {
        this.SetTarget(one.Target);
    }

    private void SortTargetList()
    {
        this.CandidateTargets.Sort((e1, e2) =>
        {
            var p1 = e1.Owner.Get<TransformComponent>().Position;
            var p2 = e2.Owner.Get<TransformComponent>().Position;

            var d1 = Vector3.Angle(this.Transform.Forward, p1 - this.Transform.Position);
            var d2 = Vector3.Angle(this.Transform.Forward, p2 - this.Transform.Position);

            if (d1 > AngleThreshold)
            {
                d1 = (this.Transform.Position - p1).SquaredMagnitude;
            }
            if (d2 > AngleThreshold)
            {
                d2 = (this.Transform.Position - p2).SquaredMagnitude;
            }
            return d1 < d2 ? -1 : 1;
        });
    }

    public bool HasTarget()
    {
        return this.Target != null;
    }
}
