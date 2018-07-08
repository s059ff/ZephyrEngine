using System;
using static Script;

class TimerComponent : CustomEntityComponent
{
    private const float DefaultCountSpeed = 0.01f;

    public event Action Ticked;
    public bool Repeat;
    public float CountSpeed = DefaultCountSpeed;
    public float CountTime;
    public bool Enable = true;

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        if (message as string == UpdateMessage)
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
}
