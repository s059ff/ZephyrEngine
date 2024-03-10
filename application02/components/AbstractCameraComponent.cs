using System.Linq;
using static GameScript;

abstract class AbstractCameraComponent : CustomEntityComponent
{
    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                if (this.isActive)
                    this.ApplyCameraTransform();
                break;
            default:
                break;
        }
    }

    public void Activate()
    {
        this.Owner.Components
            .Where(c => c is AbstractCameraComponent)
            .Select(c => c as AbstractCameraComponent)
            .Select(c => c.isActive = false)
            .ToArray();
        this.isActive = true;
    }

    private bool isActive = false;

    protected abstract void Update();

    protected abstract void ApplyCameraTransform();
}
