using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static Script;

class CustomProjectorComponent : EntityComponent
{
    public static Matrix4x4 ProjectionMatrix { get; private set; }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        if (message as string == UpdateMessage)
            ProjectionMatrix = this.Owner.Get<ProjectorComponent>().ProjectionMatrix;
    }
}
