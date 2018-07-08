using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using static EngineScript;
using static GameScript;

class GameOverComponent : CustomEntityComponent
{
    Texture2D EffectTexture = new Texture2D();
    bool PressedAnyKey;
    bool TranslateNextScene;
    int FrameFromPressedAnykey;

    public GameOverComponent()
    {
        EffectTexture.Create("res/picture/bg08.jpg", Accessibility.None);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            case DrawMessage:
                this.Draw();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        if (PressedAnyKey)
            FrameFromPressedAnykey++;

        if (pressed(KeyCode.Enter))
        {
            PressedAnyKey = true;
        }

        if (TranslateNextScene)
        {
            Program.SceneManager.SetNextScene(new TitleScene());
        }
    }

    private void Draw()
    {
        Color White = Color.FromCode(ColorCode.White);
        Color Red = Color.FromCode(ColorCode.Red);

        color(White);
        font(MeiryoUI);

        pushMatrix();
        {
            float alpha = 0;
            alpha = frame < 120 ? cos(frame / 120.0f * PI) : 0;
            if (alpha > 0)
            {
                blend(AlphaBlend);
                color(0, 0, 0, alpha);
                identity();
                scale(2 * DisplayAspect, 2);
                rectangle();
            }

            if (frame > 300)
            {
                blend(AlphaBlend);
                color(Red);
                identity();
                scale(0.15f);
                translate(0, 1, 0);
                write("Game Over", TextAlignment.Center, TextAlignment.Center);

                alpha = sin((frame - 300) / 15.0f * PIOver2) * 0.25f + 0.75f;
                if (alpha > 0)
                {
                    color(1, 1, 1, alpha);
                    translate(0, -1, 0);
                    scale(0.5f);
                    write("Press Enter key...", TextAlignment.Center, TextAlignment.Center);
                }
            }

            alpha = clamp(FrameFromPressedAnykey / 30.0f, 0, 4.0f);
            if (alpha > 0)
            {
                blend(Subtraction);
                color(alpha, alpha, alpha);
                identity();
                scale(2 * DisplayAspect, 2);
                draw(EffectTexture);
            }
            if (alpha == 4)
                TranslateNextScene = true;
        }
        popMatrix();
    }
}
