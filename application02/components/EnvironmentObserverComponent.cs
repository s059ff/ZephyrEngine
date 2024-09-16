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

class EnvironmentObserverComponent : CustomEntityComponent
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

    private float PlayerArmor { get { return this.Owner.Get<AircraftComponent>().Armor; } }

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

    private Matrix3x3 PlayerRotation { get { return this.Transform.Matrix._Matrix3x3; } }

    private Vector3 PlayerVelocity { get { return this.Physics.Velocity; } }

    private bool PlayerMissileLock { get { return this.Owner?.Get<AircraftComponent>()?.ActiveMissile?.Locking ?? false; } }

    private float OpponentArmor
    {
        get
        {
            //var entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            var entity = Entity.Find("enemy1");
            return entity?.Get<AircraftComponent>()?.Armor ?? 1.0f;
        }
    }

    private float OpponentAltitude
    {
        get
        {
            float response = 0.0f;

            var enemy = Entity.Find("enemy1");
            var pos = enemy?.Get<TransformComponent>().Position ?? Vector3.Zero;

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

    private float OpponentEnginePower
    {
        get
        {
            var entity = Entity.Find("enemy1");
            var aircraft = entity?.Get<AircraftComponent>();
            return aircraft?.EnginePower ?? 0.0f;
        }
    }

    private Vector3 OpponentPosition
    {
        get
        {
            //var entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            var entity = Entity.Find("enemy1");
            return entity?.Get<TransformComponent>()?.Position ?? Vector3.Zero;
        }
    }

    private Matrix3x3 OpponentRotation
    {
        get
        {
            //var entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            var entity = Entity.Find("enemy1");
            return entity?.Get<TransformComponent>()?.Matrix._Matrix3x3 ?? new Matrix3x3().Identity();
        }
    }

    private Vector3 OpponentVelocity
    {
        get
        {
            //var entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            var entity = Entity.Find("enemy1");
            return entity?.Get<PhysicsComponent>()?.Velocity ?? Vector3.Zero;
        }
    }

    private bool OpponentMissileLock
    {
        get
        {
            //var entity = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
            var entity = Entity.Find("enemy1");
            return entity?.Get<AircraftComponent>()?.ActiveMissile?.Locking ?? false;
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

    private Matrix3x3 ThreatMissileRotation
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
            return entity?.Get<TransformComponent>()?.Matrix._Matrix3x3 ?? new Matrix3x3().Identity();
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
        //Func<Matrix3x3, float[]> mat2array = (m) => new float[] { m.M11, m.M12, m.M13, m.M21, m.M22, m.M23, m.M31, m.M32, m.M33 };
        Func<Matrix3x3, float[]> mat2array = (m) => new float[] { m.M11, m.M12, m.M13, m.M21, m.M22, m.M23 };

        float c1 = 1.0f / (0.5f * Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength);
        float c3 = 1.0f / 6.0f;

        Matrix4x3 inv = this.Transform.Matrix.Inverse;

        var enemy = Entity.Find("enemy1");
        var forward = this.Transform.Forward;
        var relative = enemy.Get<TransformComponent>().Position - this.PlayerPosition;
        var dot = Vector3.Inner(forward.Normalize(), relative.Normalize());

        float reward = 0.0f;
        reward += dot;

        return new Dictionary<string, object>
        {
            { "episode_done", this.EpisodeDone },
            { "reward", reward },
            { 
                "player", new Dictionary<string, object>
                {
                    { "armor", this.PlayerArmor },
                    { "altitude", c1 * this.PlayerAltitude },
                    { "engine_power", this.PlayerEnginePower },
                    { "position", vec2array(c1 * this.PlayerPosition) },
                    { "rotation", mat2array(this.PlayerRotation) },
                    { "velocity", vec2array(c3 * this.PlayerVelocity) },
                    { "missile_lock", this.PlayerMissileLock },
                }
            },
            {
                "opponent", new Dictionary<string, object>
                {
                    { "armor", this.OpponentArmor },
                    { "altitude", c1 * this.OpponentAltitude },
                    { "engine_power", this.OpponentEnginePower },
                    { "position", vec2array(c1 * (this.OpponentPosition * inv)) },
                    { "rotation", mat2array(this.OpponentRotation * inv._Matrix3x3) },
                    { "velocity", vec2array(c3 * (this.OpponentVelocity * inv._Matrix3x3)) },
                    { "missile_lock", this.OpponentMissileLock },
                }
            },
            {
                "threat_missile", new Dictionary<string, object>
                {
                    { "position", vec2array(c1 * (this.ThreatMissilePosition * inv)) },
                    { "rotation", mat2array(this.ThreatMissileRotation * inv._Matrix3x3) },
                    { "velocity", vec2array(c3 * (this.ThreatMissileVelocity * inv._Matrix3x3)) },
                }
            }
        };
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case PostUpdateMessage:
                this.PostUpdate();
                break;

            default:
                break;
        }
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
