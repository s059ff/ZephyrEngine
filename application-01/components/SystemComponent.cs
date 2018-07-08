using ZephyrSharp.GameSystem;

class SystemComponent : EntityComponent
{
    public float FrameRate { get { return Script.fps; } }

    public int Frame { get { return Script.frame; } }
}
