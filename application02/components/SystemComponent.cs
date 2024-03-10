using ZephyrSharp.GameSystem;
using static EngineScript;
using static GameScript;

public class SystemComponent : CustomEntityComponent
{
    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.update();
                break;
            default:
                break;
        }
    }

    private void update()
    {
        this.FrameCount++;
    }

    public int FrameCount { get; private set; }

    public int EntityCount { get { return Entity.EntityCount; } }
}
