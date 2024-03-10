using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using System.Linq;
using static EngineScript;
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
            .Select(c => (AbstractCameraComponent)c)
            .Select(c => c.isActive = false);
        this.isActive = true;
    }

    private bool isActive = false;

    protected abstract void Update();

    protected abstract void ApplyCameraTransform();
}
