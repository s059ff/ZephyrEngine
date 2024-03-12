using System;
using ZephyrSharp.Input;

public class GamePad
{
    public void Update()
    {
        this.keyboard.Update();
        this.joyStick.Update();
    }

    public enum LogicalButton
    {
        A,
        B,
        X,
        Y,
        LB,
        RB,
        LT,
        RT,
        LSB,
        RSB,
        Back,
        Start,
        Guide,
    }

    public int GetButtonState(LogicalButton button)
    {
        switch (button)
        {
            case LogicalButton.A:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button2) : this.keyboard.GetKeyState(Keyboard.KeyCode.V);
            case LogicalButton.B:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button3) : this.keyboard.GetKeyState(Keyboard.KeyCode.C);
            case LogicalButton.X:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button1) : this.keyboard.GetKeyState(Keyboard.KeyCode.A);
            case LogicalButton.Y:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button4) : this.keyboard.GetKeyState(Keyboard.KeyCode.S);
            case LogicalButton.LB:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button5) : this.keyboard.GetKeyState(Keyboard.KeyCode.Q);
            case LogicalButton.RB:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button6) : this.keyboard.GetKeyState(Keyboard.KeyCode.E);
            case LogicalButton.LT:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button7) : this.keyboard.GetKeyState(Keyboard.KeyCode.X);
            case LogicalButton.RT:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button8) : this.keyboard.GetKeyState(Keyboard.KeyCode.Z);
            case LogicalButton.LSB:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button11) : 0;
            case LogicalButton.RSB:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button12) : this.keyboard.GetKeyState(Keyboard.KeyCode.D);
            case LogicalButton.Back:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button9) : 0;
            case LogicalButton.Start:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button10) : 0;
            case LogicalButton.Guide:
                return this.joyStick.IsConnected() ? this.joyStick.GetButtonState(JoyStick.ButtonCode.Button13) : 0;
            default:
                break;
        }
        throw new InvalidOperationException();
    }

    public Tuple<double, double> Axis1
    {
        get
        {
            if (this.joyStick.IsConnected())
            {
                return this.joyStick.Axis1;
            }
            else
            {
                bool left = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.Left));
                bool right = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.Right));
                bool up = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.Up));
                bool down = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.Down));

                double x = (left ? -1.0 : 0.0) + (right ? +1.0 : 0.0);
                double y = (down ? -1.0 : 0.0) + (up ? +1.0 : 0.0);

                double magnitude = Math.Sqrt(x * x + y * y);
                if (0 < magnitude)
                {
                    x /= magnitude;
                    y /= magnitude;
                }

                return new Tuple<double, double>(x, y);
            }
        }
    }

    public Tuple<double, double> Axis2
    {
        get
        {
            if (this.joyStick.IsConnected())
            {
                return this.joyStick.Axis2;
            }
            else
            {
                bool left = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.J));
                bool right = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.L));
                bool up = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.I));
                bool down = (0 < this.keyboard.GetKeyState(Keyboard.KeyCode.K));

                double x = (left ? -1.0 : 0.0) + (right ? +1.0 : 0.0);
                double y = (down ? -1.0 : 0.0) + (up ? +1.0 : 0.0);

                double magnitude = Math.Sqrt(x * x + y * y);
                if (0 < magnitude)
                {
                    x /= magnitude;
                    y /= magnitude;
                }

                return new Tuple<double, double>(x, y);
            }
        }
    }

    private Keyboard keyboard = new Keyboard();
    private JoyStick joyStick = new JoyStick();
}
