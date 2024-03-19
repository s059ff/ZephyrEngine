using System;
using static GameScript;

class TimerComponent : CustomEntityComponent
{
    private const float DefaultCountSpeed = 0.01f;

    public event Action Ticked;
    public bool Repeat = false;
    public float CountSpeed = DefaultCountSpeed;
    public float CountTime = 0;
    public bool Enable = true;

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
        if (this.Enable)
        {
            this.CountTime += this.CountSpeed;
            if (1.0f <= this.CountTime)
            {
                this.Ticked();
                this.Enable = false;

                if (this.Repeat)
                {
                    this.CountTime = 0;
                    this.Enable = true;
                }
            }
        }
    }
}
