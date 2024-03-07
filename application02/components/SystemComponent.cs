using ZephyrSharp.GameSystem;
using static EngineScript;

public class SystemComponent : CustomEntityComponent
{
    public int Frame { get { return frame; } }

    public int EntityCount { get { return Entity.EntityCount; } }
}
