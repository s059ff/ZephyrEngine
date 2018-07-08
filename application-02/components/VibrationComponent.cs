using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static Script;

public class VibrationComponent : CustomEntityComponent
{
    public float VibrationPower = 0.01f;

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
        Vector3 v = new Vector3(normal(0, VibrationPower), normal(0, VibrationPower), normal(0, VibrationPower));
        this.Owner.Get<TransformComponent>().Matrix.Translate(v);
    }
}
