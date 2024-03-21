using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using static EngineScript;
using static GameScript;

public class GameSpaceComponent : CustomEntityComponent
{
    public GameSpaceComponent(float spaceLength)
    {
        this.SpaceLength = spaceLength;
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            // 戦闘エリアから離脱した機体を破壊
            case UpdateMessage:
                Entity.ForEach(e =>
                {
                    if (e.Has<AircraftComponent>())
                    {
                        var transform = e.Get<TransformComponent>();
                        bool flag = false
                            || (abs(transform.Position.X) > this.SpaceLength / 2)
                            || (abs(transform.Position.Y) > this.SpaceLength / 2)
                            || (abs(transform.Position.Z) > this.SpaceLength / 2);
                        if (flag)
                        {
                            e.Get<AircraftComponent>().TakeDamage(1.0f);
                        }
                    }
                });
                break;
        }
    }

    public readonly float SpaceLength;
}
