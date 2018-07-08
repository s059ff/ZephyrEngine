using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using static Script;

class TitleComponent : CustomEntityComponent
{
    Texture2D EffectTexture = new Texture2D();
    bool PressedAnyKey;
    bool TranslateNextScene;
    int FrameFromPressedAnykey;
    float GazeKeyPressedTime;
    List<Entity> Aircrafts = new List<Entity>();
    Entity CameraTargetAircraft;
    int CameraTargetAircraftIndex;
    Font MeiryoUIUnderLine = new Font();

    public TitleComponent()
    {
        EffectTexture.Create("res/picture/bg08.jpg", Accessibility.None);
        MeiryoUIUnderLine.Create("Meiryo UI", 64, FontOption.Bold);
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

        if (nowreleased(KeyCode.S) || CameraTargetAircraft == null)
        {
            if (GazeKeyPressedTime < 1.0f)
                this.ChangeCameraTarget();
        }

        if (pressed(KeyCode.S))
            GazeKeyPressedTime += 0.1f;
        else
            GazeKeyPressedTime = 0;

        var camera = Entity.Find("camera").Get<CameraComponent>();
        camera.EnableTracking = false;
        if (CameraTargetAircraft.IsAlive)
        {
            camera.GazingPoint = CameraTargetAircraft.Get<TransformComponent>().Position;
        }
        camera.EnableGazing = (1.0f < GazeKeyPressedTime);

        if (TranslateNextScene)
        {
            SceneManager.FookScene(new MissionSelectScene());
        }
    }

    private void ChangeCameraTarget()
    {
        Aircrafts.Clear();
        Entity.ForEach(e => { if (e.IsAlive && e.Has<AircraftComponent>()) Aircrafts.Add(e); });
        if (CameraTargetAircraftIndex == Aircrafts.Count)
            CameraTargetAircraftIndex = 0;
        CameraTargetAircraft = Aircrafts[CameraTargetAircraftIndex++];
    }

    private void Draw()
    {
        Color White = Color.FromCode(ColorCode.White);

        color(White);

        pushMatrix();
        {
            {
                float alpha = frame < 120 ? cos(frame / 120.0f * PI) : 0;
                if (alpha > 0)
                {
                    blend(AlphaBlend);
                    color(0, 0, 0, alpha);
                    identity();
                    scale(2 * DisplayAspect, 2);
                    rectangle();
                }
            }

            if (frame > 300)
            {
                font(MeiryoUIUnderLine);
                blend(AlphaBlend);
                color(White);
                identity();
                scale(0.25f);
                translate(0, 1, 0);
                write("AirSurvival 3", TextAlignment.Center, TextAlignment.Center);

                float alpha = sin((frame - 300) / 15.0f * PIOver2) * 0.25f + 0.75f;
                if (alpha > 0)
                {
                    font(MeiryoUI);
                    color(1, 1, 1, alpha);
                    identity();
                    scale(0.25f);
                    translate(0, -1, 0);
                    scale(0.5f);
                    write("Press Enter key...", TextAlignment.Center, TextAlignment.Center);
                }
            }

            {
                float alpha = clamp(FrameFromPressedAnykey / 30.0f, 0, 4.0f);
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
        }
        popMatrix();
    }
}
