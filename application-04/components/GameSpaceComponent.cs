public class GameSpaceComponent : CustomEntityComponent
{
    public GameSpaceComponent(float spaceLength)
    {
        this.SpaceLength = spaceLength;
    }

    public readonly float SpaceLength;
}
