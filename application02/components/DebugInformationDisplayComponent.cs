using System.Collections.Generic;
using System.Diagnostics;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using static EngineScript;
using static GameScript;

class DebugInformationDisplayComponent : CustomEntityComponent
{
    public Dictionary<string, string> DebugMessages { get; private set; } = new Dictionary<string, string>();

    private Stopwatch stopwatch = new Stopwatch();

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
        int friendCount = 0, enemeyCount = 0;
        Entity.ForEach((e) =>
        {
            if (e.Has<AircraftComponent>() && e.Has<AircraftAvionicsComponent>())
            {
                var avionics = e.Get<AircraftAvionicsComponent>();
                if (avionics.Organization == Friend)
                    friendCount++;
                if (avionics.Organization == Enemy)
                    enemeyCount++;
            }
        });
        this.DebugMessages["friend_count"] = friendCount.ToString();
        this.DebugMessages["enemy_count"] = enemeyCount.ToString();

        int frameCount = Entity.Find("system").Get<SystemComponent>().FrameCount;
        this.DebugMessages["frame_count"] = frameCount.ToString();
        if (frameCount % 60 == 0)
        {
            this.stopwatch.Stop();

            var milliseconds = this.stopwatch.ElapsedMilliseconds;
            var frameRate = 60.0 * 1000.0 / (double)milliseconds;

            this.DebugMessages["frames_per_sec"] = frameRate.ToString();

            this.stopwatch.Reset();
            this.stopwatch.Start();
        }
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
                write($"{message.Key}: {message.Value}");
                translate(0.0f, -1.0f, 0.0f);
            }
        }
        popMatrix();
    }
}
