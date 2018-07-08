using ZephyrSharp.Linalg;
using static Script;

class GravityObjectComponent : CustomEntityComponent
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
        this.Physics.Force += new Vector3(0, -this.Physics.Mass * Gravity * 10, 0);
    }
}
