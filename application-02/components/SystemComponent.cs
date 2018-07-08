using ZephyrSharp.GameSystem;

public class SystemComponent : CustomEntityComponent
{
    public float FrameRate { get { return Script.fps; } }

    public int Frame { get { return Script.frame; } }

    public int EntityCount { get { return Entity.EntityCount; } }
}
