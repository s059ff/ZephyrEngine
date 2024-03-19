using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using static EngineScript;
using static GameScript;

class DebugInformationDisplayComponent : CustomEntityComponent
{
    public Dictionary<string, string> DebugMessages { get; private set; } = new Dictionary<string, string>();

    private Stopwatch stopwatch = new Stopwatch();

    private int frameCount = 0;

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.update();
                break;
            case DrawMessage:
                this.draw();
                break;
            default:
                break;
        }
    }

    private void update()
    {
        this.DebugMessages["entity_count"] = Entity.EntityCount.ToString();

        int friendCount = 0, enemeyCount = 0;
        Entity.ForEach((e) =>
        {
            if (e.Has<AircraftComponent>() && e.Has<AircraftAvionicsComponent>())
            {
                var avionics = e.Get<AircraftAvionicsComponent>();
                if (avionics.Organization == OrganizationFriend)
                    friendCount++;
                if (avionics.Organization == OrganizationEnemy)
                    enemeyCount++;
            }
        });
        this.DebugMessages["friend_count"] = friendCount.ToString();
        this.DebugMessages["enemy_count"] = enemeyCount.ToString();
        this.DebugMessages["frame_count"] = this.frameCount.ToString();

        if (this.frameCount == 0)
        {
            this.DebugMessages["frame_rate"] = "N/A";
        }
        else if (this.frameCount % 60 == 0)
        {
            this.stopwatch.Stop();

            var milliseconds = this.stopwatch.ElapsedMilliseconds;
            var frameRate = 60.0 * 1000.0 / milliseconds;

            this.DebugMessages["frame_rate"] = frameRate.ToString();

            this.stopwatch.Reset();
            this.stopwatch.Start();
        }
        this.frameCount++;
    }

    private void draw()
    {
        Color Green = new Color(0.0f, 0.8f, 0.0f, 0.8f);

        identity();

        blend(HalfAddition);
        color(Green);

        pushMatrix();
        {
            translate(-1.6f, 1.0f, 0.0f);
            scale(0.05f);

            foreach (var message in this.DebugMessages)
            {
                string key = message.Key.Replace("\r", string.Empty);
                string[] values = message.Value.Replace("\r", string.Empty).Split('\n').Where(s => s != string.Empty).ToArray();
                if(values.Length == 1)
                {
                    write($"{key}: {values.First()}");
                    translate(0.0f, -1.0f, 0.0f);
                }
                else if (values.Length > 1)
                {
                    write($"{key}:");
                    translate(0.0f, -1.0f, 0.0f);

                    foreach (var value in values)
                    {
                        write($"{value}");
                        translate(0.0f, -1.0f, 0.0f);
                    }
                }
            }
        }
        popMatrix();
    }
}
