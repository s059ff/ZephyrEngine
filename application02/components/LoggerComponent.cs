using System;
using System.IO;
using ZephyrSharp.GameSystem;
using static GameScript;

class LoggerComponent : CustomEntityComponent
{
    private StreamWriter stream;
    private int frameCount;

    public LoggerComponent() { }

    protected override void OnAttach()
    {
        base.OnAttach();

        var now = DateTime.Now.ToString("yyyyMMdd_HHmmss");
        this.stream = new StreamWriter($"logs/log_{now}.log") { AutoFlush = true };
        this.WriteDebugLog("The logging task was started.");
    }

    protected override void OnDetach()
    {
        {
            int enemyCount = 0, friendCount = 0;
            Entity.ForEach((e) =>
            {
                if (e.Has<AircraftAvionicsComponent>())
                {
                    var aircraft = e.Get<AircraftComponent>();
                    var avionics = e.Get<AircraftAvionicsComponent>();
                    if (aircraft.Armor > 0)
                    {
                        friendCount += (avionics.Organization == OrganizationFriend) ? 1 : 0;
                        enemyCount += (avionics.Organization == OrganizationEnemy) ? 1 : 0;
                    }
                }
            });
            this.WriteDebugLog($"enemyCount: {enemyCount}");
            this.WriteDebugLog($"friendCount: {friendCount}");
        }

        {
            var player = Entity.Find("player");
            bool isPlayerAlive = (player != null) && (player.Has<AircraftComponent>()) && (player.Get<AircraftComponent>().Armor > 0);
            this.WriteDebugLog($"isPlayerAlive: {isPlayerAlive}");
        }

        {
            this.WriteDebugLog($"frameCount: {this.frameCount}");
            this.WriteDebugLog("The logging task was finished.");
        }

        this.stream.Dispose();
        this.stream = null;
    }

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

    private void Update()
    {
        this.frameCount++;
    }

    private void WriteDebugLog(string message)
    {
        var now = DateTime.Now.ToString("yyyy-MM-dd'T'HH:mm:ss'Z'");
        this.stream.WriteLine($"[{now}] {message}");
    }
}
