using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class CustomCameraComponent : EntityComponent
{
    public static Matrix4x4 ViewingMatrix { get; private set; }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        if (message as string == UpdateMessage)
            ViewingMatrix = new Matrix4x4(this.Owner.Get<CameraComponent>().ViewingMatrix);
    }
}
