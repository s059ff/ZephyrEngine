using ZephyrSharp.GameSystem;

class LimitedLifeTimeComponent : TimerComponent
{
    public LimitedLifeTimeComponent()
    {
        this.Ticked += () =>
        {
            Entity.Kill(this.Owner);
        };
    }
}
