using System.Reflection;
using System.Threading;
using ZephyrSharp.GameSystem;
using static Script;

class MissionControllerComponent : CustomEntityComponent
{
    MethodInfo StartMethod;

    MethodInfo UpdateMethod;

    public MissionControllerComponent(LoadingTask task, string missionName)
    {
        var type = Missions.MissionAssemblies[missionName].GetType("Mission");
        StartMethod = type.GetMethod("start");
        UpdateMethod = type.GetMethod("update");
        StartMethod.Invoke(null, new object[] { task });
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
