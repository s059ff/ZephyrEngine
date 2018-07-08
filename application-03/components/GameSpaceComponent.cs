public class GameSpaceComponent : CustomEntityComponent
{
    public GameSpaceComponent(float areaLength)
    {
        this.AreaLength = areaLength;
    }

    public readonly float AreaLength;
}
