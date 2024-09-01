using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class EnvironmentObservationComponent : CustomEntityComponent
{
    private bool EpisodeDone
    {
        get
        {
            assert(Entity.Find("player") == this.Owner);
            return false
                || (3600 < Entity.Find("system").Get<SystemComponent>().FrameCount)
                || ((Entity.Find("player")?.Get<AircraftComponent>()?.Armor ?? 0.0f) == 0.0f)
                || ((Entity.Find("enemy1")?.Get<AircraftComponent>()?.Armor ?? 0.0f) == 0.0f)
                ;
        }
    }

    private float PlayerArmorCurt { get { return this.Owner.Get<AircraftComponent>().UnclampedArmor; } }

    private float PlayerArmorPrev = 1.0f;

    private float PlayerAltitude
    {
        get
        {
            float response = 0.0f;

            var pos = this.Transform.Position;
            var ground = Entity.Find("ground");
            if (ground != null)
            {
                var collision = ground.Get<CollisionComponent>();
                if (collision != null)
                {
                    response = (collision.Object as CurvedSurfaceCollisionObject).ComputeHeight(pos);
                }
            }
            response = (float.IsNaN(response)) ? 0.0f : response;
            return response;
        }
    }

    private float PlayerEnginePower
    {
        get
        {
            var aircraft = this.Owner.Get<AircraftComponent>();
            return aircraft.EnginePower;
        }
    }

    private Vector3 PlayerPosition { get { return this.Transform.Position; } }

    private Quaternion PlayerRotation { get { return new Quaternion(this.Transform.Matrix._Matrix3x3); } }

    private Vector3 PlayerVelocity { get { return this.Physics.Velocity; } }

    private float TargetArmorCurt
    {
        get
        {
            //Entity entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            Entity entity = Entity.Find("enemy1");
            return entity?.Get<AircraftComponent>()?.UnclampedArmor ?? 0.0f;
        }
    }

    private float TargetArmorPrev = 1.0f;

    private Vector3 TargetPosition
    {
        get
        {
            //Entity entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            Entity entity = Entity.Find("enemy1");
            return entity?.Get<TransformComponent>()?.Position ?? Vector3.Zero;
        }
    }

    private Quaternion TargetRotation
    {
        get
        {
            //Entity entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            Entity entity = Entity.Find("enemy1");
            return new Quaternion(entity?.Get<TransformComponent>()?.Matrix._Matrix3x3 ?? new Matrix3x3().Identity());
        }
    }

    private Vector3 TargetVelocity
    {
        get
        {
            //Entity entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            Entity entity = Entity.Find("enemy1");
            return entity?.Get<PhysicsComponent>()?.Velocity ?? Vector3.Zero;
        }
    }

    private Vector3 ThreatMissilePosition
    {
        get
        {
            var entity = Entity.Find(e =>
            {
                var missile = e.Get<MissileComponent>();
                return true
                    && (missile != null)
                    && (missile.TargetEntity == this.Owner)
                    && missile.Locking
                    && missile.Launched;
            });
            return entity?.Get<TransformComponent>().Position ?? Vector3.Zero;
        }
    }

    private Quaternion ThreatMissileRotation
    {
        get
        {
            var entity = Entity.Find(e =>
            {
                var missile = e.Get<MissileComponent>();
                return true
                    && (missile != null)
                    && (missile.TargetEntity == this.Owner)
                    && missile.Locking
                    && missile.Launched;
            });
            return new Quaternion(entity?.Get<TransformComponent>()?.Matrix._Matrix3x3 ?? new Matrix3x3().Identity());
        }
    }

    private Vector3 ThreatMissileVelocity
    {
        get
        {
            var entity = Entity.Find(e =>
            {
                var missile = e.Get<MissileComponent>();
                return true
                    && (missile != null)
                    && (missile.TargetEntity == this.Owner)
                    && missile.Locking
                    && missile.Launched;
            });
            return entity?.Get<PhysicsComponent>()?.Velocity ?? Vector3.Zero;
        }
    }

    public Dictionary<string, object> Observe()
    {
        Func<Vector3, float[]> vec2array = (v) => new float[] { v.X, v.Y, v.Z };
        Func<Quaternion, float[]> quat2array = (q) =>
        {
            float mag = sqrt(square(q.X) + square(q.Y) + square(q.Z) + square(q.W));
            if (1e-6f < mag)
                return new float[] { q.X / mag, q.Y / mag, q.Z / mag, q.W / mag };
            else
                return new float[] { q.X, q.Y, q.Z, q.W };
        };

        float c1 = 1.0f / (0.5f * Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength);
        float c3 = 1.0f / 6.0f;

        return new Dictionary<string, object>
        {
            { "episode_done", this.EpisodeDone },
            {
                "player", new Dictionary<string, object>
                {
                    { "armor_delta", this.PlayerArmorCurt - this.PlayerArmorPrev },
                    { "altitude", c1 * this.PlayerAltitude },
                    { "engine_power", this.PlayerEnginePower },
                    { "position", vec2array(c1 * this.PlayerPosition) },
                    { "rotation", quat2array(this.PlayerRotation) },
                    { "velocity", vec2array(c3 * this.PlayerVelocity) },
                }
            },
            {
                "target", new Dictionary<string, object>
                {
                    { "armor_delta", this.TargetArmorCurt - this.TargetArmorPrev },
                    { "position", vec2array(c1 * this.TargetPosition) },
                    { "rotation", quat2array(this.TargetRotation) },
                    { "velocity", vec2array(c3 * this.TargetVelocity) },
                }
            },
            {
                "threat_missile", new Dictionary<string, object>
                {
                    { "position", vec2array(c1 * this.ThreatMissilePosition) },
                    { "rotation", quat2array(this.ThreatMissileRotation) },
                    { "velocity", vec2array(c3 * this.ThreatMissileVelocity) },
                }
            }
        };
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case PreUpdateMessage:
                this.PreUpdate();
                break;

            case PostUpdateMessage:
                this.PostUpdate();
                break;

            default:
                break;
        }
    }

    private void PreUpdate()
    {
        this.PlayerArmorPrev = this.PlayerArmorCurt;
        this.TargetArmorPrev = this.TargetArmorCurt;
    }

    private void PostUpdate()
    {
        var display = Entity.Find("debugger").Get<DebugInformationDisplayComponent>();
        display.DebugMessages["observation"] = JObject.FromObject(this.Observe()).ToString(Formatting.Indented);
    }

    private static Vector3 MatrixDecomposeYawPitchRoll(Matrix3x3 mat)
    {
        Vector3 euler = new Vector3();
        euler.X = asin(-mat.M32);                  // Pitch
        if (cos(euler.X) > 0.0001)                 // Not at poles
        {
            euler.Y = atan2(mat.M31, mat.M33);     // Yaw
            euler.Z = atan2(mat.M12, mat.M22);     // Roll
        }
        else
        {
            euler.Y = 0.0f;                        // Yaw
            euler.Z = atan2(-mat.M21, mat.M11);    // Roll
        }
        return euler;
    }
}
