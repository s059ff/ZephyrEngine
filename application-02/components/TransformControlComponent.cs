using ZephyrSharp.Linalg;
using static Script;

public class TransformControlComponent : CustomEntityComponent
{
    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                Update();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        this.Transform.Matrix.Translate(0, 0, mouseDZ * 0.5f);
        if (clickL())
        {
            Vector3 p = this.Transform.Matrix.Position;
            this.Transform.Matrix.Position = Vector3.Zero;
            this.Transform.Matrix = this.Transform.Matrix * new Matrix4x3().Identity().RotateY(mouseDX * 0.01f);
            this.Transform.Matrix.Position = p;

            this.Transform.Matrix.RotateX(mouseDY * 0.01f);
        }
        if (clickR())
        {
        }
        if (clickC())
        {
            this.Transform.Matrix.Translate(-mouseDX * 5, mouseDY * 5, 0);
        }
    }
}
