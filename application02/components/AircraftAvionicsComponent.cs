using System;
using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class AircraftAvionicsComponent : CustomEntityComponent
{
    public AircraftAvionicsComponent(int organization)
    {
        this.Organization = organization;
    }
    
    public void ChangeTarget()
    {
        Entity highestPriorityEntity = null;
        float highestPriority = 0.0f;

        Entity.ForEach(e =>
        {
            if (e.Has<AircraftComponent>() && e.Has<AircraftAvionicsComponent>())
            {
                if (e.Get<AircraftComponent>().Armor == 0)
                    return;
                if (this.Organization == e.Get<AircraftAvionicsComponent>().Organization)
                    return;

                var pos = e.Get<TransformComponent>().Position;
                var distance = (pos - this.Transform.Position).Magnitude;
                var angle = Vector3.Angle(this.Transform.Forward, pos - this.Transform.Position);

                float epsilon = 1e-8f;
                float priority = 1.0f / (angle + epsilon);
                if (highestPriority < priority)
                {
                    highestPriorityEntity = e;
                    highestPriority = priority;
                }
            }
        });

        if (this.targetEntity != highestPriorityEntity)
        {
            var aircraft = this.Owner.Get<AircraftComponent>();
            if (aircraft.ActiveMissile != null)
            {
                aircraft.ActiveMissile.ResetTarget();
            }

            this.targetEntity = highestPriorityEntity;
        }
    }

    public void ChangeTargetRandomly()
    {
        List<Entity> entities = new List<Entity>();

        Entity.ForEach(e =>
        {
            if (e.Has<AircraftComponent>() && e.Has<AircraftAvionicsComponent>())
            {
                if (e.Get<AircraftComponent>().Armor == 0)
                    return;
                if (this.Organization == e.Get<AircraftAvionicsComponent>().Organization)
                    return;
                entities.Add(e);
            }
        });

        if (entities.Count > 0)
        {
            var random = new Random();
            this.targetEntity = entities[random.Next(entities.Count)];
        }
    }

    public bool HasTarget()
    {
        return this.TargetEntity != null;
    }

    const float DistanceThreshold = 4000.0f;
    const float AngleThreshold = PI / 4;

    public readonly int Organization;

    public Entity TargetEntity
    {
        get
        {
            if (this.targetEntity != null)
            {
                if (!this.targetEntity.Has<AircraftComponent>() || this.targetEntity.Get<AircraftComponent>().Armor == 0)
                {
                    this.targetEntity = null;
                }
            }
            if (this.targetEntity == null)
            {
                if (this.Owner.Name == "player")
                {
                    this.ChangeTarget();
                }
                else
                {
                    this.ChangeTargetRandomly();
                }
            }
            return this.targetEntity;
        }
    }

    Entity targetEntity;
}
