using ZephyrSharp.Linalg;
using static GameScript;

public class TransformControlComponent : CustomEntityComponent
{
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
        this.Transform.Matrix.Translate(0, 0, mouseDZ * 0.5f);
        if (clickL())
        {
            Vector3 p = this.Transform.Matrix.Position;
            this.Transform.Matrix.Position = Vector3.Zero;
            this.Transform.Matrix.RotateX(mouseDY * 0.01f);
            this.Transform.Matrix.RotateY(mouseDX * 0.01f);
            this.Transform.Matrix.Position = p;
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
