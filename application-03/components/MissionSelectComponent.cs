using System.Linq;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class MissionSelectComponent : CustomEntityComponent
{
    Texture2D SparkTexture = new Texture2D();
    Texture2D EffectTexture = new Texture2D();
    bool TranslateNextScene = false;
    string[] MissionList = new string[] { };
    int FrameFromDecidedMission = 0;
    int SelectItemIndex = -1;
    bool DecidedMission = false;
    int DecidedMissionIndex = 0;

    public MissionSelectComponent()
    {
        SparkTexture.Create("res/picture/spark.png", Accessibility.None);
        EffectTexture.Create("res/picture/bg08.jpg", Accessibility.None);

        MissionList = Missions.MissionAssemblies.Keys.ToArray();
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
        if (DecidedMission)
            FrameFromDecidedMission++;

        if (nowClick() && 0 <= SelectItemIndex)
        {
            //TranslateNextScene = true;
            DecidedMission = true;
            DecidedMissionIndex = SelectItemIndex;
        }

        if (TranslateNextScene)
        {
            Program.SceneManager.SetNextScene(new MainScene(), Missions.MissionAssemblies[MissionList[DecidedMissionIndex]]);
        }
    }

    private void Draw()
    {
        Color White = new Color(ColorCode.White);

        font(MeiryoUI);

        blend(Addition);
        identity();
        translate(-1, 0.75f, 0);
        scale(0.1f);

        SelectItemIndex = -1;
        for (int i = 0; i < MissionList.Length; i++)
        {
            var viewport = new Matrix4x4().Viewport(DisplayWidth, DisplayHeight);
            var matrix = world * viewing * projection * viewport;
            float top = (new Vector4(0, 0.5f, 0, 1) * matrix).Y;
            float bottom = (new Vector4(0, -0.5f, 0, 1) * matrix).Y;

            if (is_inner(mouseY, top, bottom))
            {
                color(ColorCode.White);
                SelectItemIndex = i;

                pushMatrix();
                {
                    translate(-1, 0);
                    rotate(deg2rad(-45));
                    translate(cos(frame / 10.0f) * 0.25f, sin(frame / 10.0f) * 0.5f);
                    scale(3);
                    draw(SparkTexture);
                }
                popMatrix();

                pushMatrix();
                {
                    translate(-1, 0);
                    rotate(deg2rad(-45));
                    translate(-cos(frame / 10.0f) * 0.25f, -sin(frame / 10.0f) * 0.5f);
                    scale(3);
                    draw(SparkTexture);
                }
                popMatrix();
            }
            else
                color(ColorCode.Gray);

            write("#" + (i + 1) + " " + MissionList[i], TextAlignment.Left, TextAlignment.Center);
            translate(0.25f, -1);
        }

        float alpha = clamp(FrameFromDecidedMission / 30.0f, 0, 4.0f);
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
