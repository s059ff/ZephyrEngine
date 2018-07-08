using ZephyrSharp.GameSystem;
using static EngineScript;

public class SystemComponent : CustomEntityComponent
{
    public float FrameRate { get { return fps; } }

    public int Frame { get { return frame; } }

    public int EntityCount { get { return Entity.EntityCount; } }
}
