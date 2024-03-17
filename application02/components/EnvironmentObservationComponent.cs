using Newtonsoft.Json;
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
    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;
            default:
                break;
        }
    }

    public string ToJsonString(bool indent = false)
    {
        Func<Vector3, float[]> vec2array = (v) =>
        {
            return new float[] { v.X, v.Y, v.Z };
        };
        Func<Quaternion, float[]> quat2array = (v) =>
        {
            return new float[] { v.X, v.Y, v.Z, v.W };
        };

        float c1 = 1.0f / (0.5f * Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength);
        float c2 = 1.0f / PI;
        float c3 = 1.0f / 6.0f;

        var obj = new Dictionary<string, object>
        {
            { "episode_done", this.EpisodeDone },
            {
                "player", new Dictionary<string, object>
                {
                    { "taken_damage", this.Player.TakenDamage },
                    { "inflicted_damage", this.Player.InflictedDamage },
                    { "altitude", c1 * this.Player.Altitude },
                    { "engine_power", this.Player.EnginePower },
                    { "position", vec2array(c1 * this.Player.Position) },
                    { "rotation", quat2array(this.Player.Rotation) },
                    { "velocity", vec2array(c3 * this.Player.Velocity) },
                }
            }
        };
        return JsonConvert.SerializeObject(obj, indent ? Formatting.Indented : Formatting.None);
    }

    private void Update()
    {
        {
            var display = Entity.Find("debugger").Get<DebugInformationDisplayComponent>();
            display.DebugMessages["observation"] = this.ToJsonString(indent: true);
        }
        {
            var observer = this.Owner.Get<EnvironmentObservationComponent>();
            var aircraft = this.Owner.Get<AircraftComponent>();
            if (observer != null)
            {
                var ground = Entity.Find("ground");
                var target = this.Owner.Get<AircraftAvionicsComponent>()?.TargetEntity;
                var threat = Entity.Find(e =>
                {
                    var missile = e.Get<MissileComponent>();
                    return (missile != null && missile.TargetEntity == this.Owner && missile.Locking);
                });

                float altitude = float.NaN;
                if (ground != null)
                {
                    var coll = ground.Get<CollisionComponent>().Object as CurvedSurfaceCollisionObject;
                    altitude = coll.ComputeHeight(this.Transform.Position);
                }
                observer.Player.Altitude = altitude;
                observer.Player.EnginePower = aircraft.EnginePower;
                observer.Player.Position = this.Transform.Position;
                observer.Player.Rotation = new Quaternion(this.Transform.Matrix._Matrix3x3);
                observer.Player.Velocity = this.Physics.Velocity;
            }
        }
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
            euler.Y = 0.0f;                         // Yaw
            euler.Z = atan2(-mat.M21, mat.M11);    // Roll
        }
        return euler;
    }

    public struct TObservationPlayer
    {
        public float TakenDamage;
        public float InflictedDamage;
        public float Altitude;
        public float EnginePower;
        public Vector3 Position;
        public Quaternion Rotation;
        public Vector3 Velocity;
    }

    public bool EpisodeDone;

    public TObservationPlayer Player;
}
