using System.Reflection;
using static EngineScript;
using static GameScript;

class MissionControllerComponent : CustomEntityComponent
{
    MethodInfo UpdateMethod;

    public MissionControllerComponent(Assembly missionAssembly)
    {
        var type = missionAssembly.GetType("Mission");
        type.GetMethod("start").Invoke(null, null);
        UpdateMethod = type.GetMethod("update");
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
        UpdateMethod.Invoke(null, null);
    }
}
