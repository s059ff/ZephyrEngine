using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Linalg;
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

    public string ToJsonString(bool indent=false)
    {
        Func<Vector3, float[]> vec2array = (Vector3 v) =>
        {
            return new float[] { v.X, v.Y, v.Z };
        };
        var obj = new Dictionary<string, object>
        {
            { "episode_done", this.EpisodeDone },
            {
                "player", new Dictionary<string, object>
                {
                    { "taken_damage", this.Player.TakenDamage },
                    { "inflicted_damage", this.Player.InflictedDamage },
                    { "altitude", this.Player.Altitude },
                    { "engine_power", this.Player.EnginePower },
                    { "position", vec2array(this.Player.Position) },
                    { "euler_angles", vec2array(this.Player.EulerAngles) },
                    { "velocity", vec2array(this.Player.Velocity) }
                }
            },
        };
        return JsonConvert.SerializeObject(obj, indent ? Formatting.Indented : Formatting.None);
    }

    private void Update()
    {
        var display = Entity.Find("debugger").Get<DebugInformationDisplayComponent>();
        display.DebugMessages["observation"] = this.ToJsonString(indent: true);
    }

    public struct TObservationPlayer
    {
        public float TakenDamage;
        public float InflictedDamage;
        public float Altitude;
        public float EnginePower;
        public Vector3 Position;
        public Vector3 EulerAngles;
        public Vector3 Velocity;
    }

    public bool EpisodeDone;

    public TObservationPlayer Player;
}
