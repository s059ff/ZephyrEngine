using System;
using System.Reflection;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using ZephyrSharp.Sound;
using static EngineScript;

public static class GameScript
{
    public static BlendState NoBlend = new BlendState();
    public static BlendState Addition = new BlendState();
    public static BlendState HalfAddition = new BlendState();
    public static BlendState Subtraction = new BlendState();
    public static BlendState Multiplication = new BlendState();
    public static BlendState Reverse = new BlendState();
    public static BlendState AlphaBlend = new BlendState();

    public static Font DefaultFont = new Font();

    public static SamplerState Wrap = new SamplerState();
    public static SamplerState Mirror = new SamplerState();

    public static RasterizerState CullingOn = new RasterizerState();
    public static RasterizerState CullingOff = new RasterizerState();

    public static DepthStencilState ZTestOn = new DepthStencilState();
    public static DepthStencilState ZTestOnWriteOff = new DepthStencilState();
    public static DepthStencilState ZTestOff = new DepthStencilState();

    public static SoundBuffer ExplosionSound = new SoundBuffer();
    public static SoundBuffer LargeExplosionSound = new SoundBuffer();
    public static SoundBuffer JetSound = new SoundBuffer();
    public static SoundBuffer LockonSound = new SoundBuffer();
    public static SoundBuffer AlertSound = new SoundBuffer();
    public static SoundBuffer BulletSound = new SoundBuffer();
    public static SoundBuffer BulletHitSound = new SoundBuffer();

    public const string PreUpdateMessage = "preupdate";
    public const string UpdateMessage = "update";
    public const string PostUpdateMessage = "postupdate";
    public const string RenderMessage = "render";
    public const string TranslucentRenderMessage = "translucent render";
    public const string DrawMessage = "draw";
    public const string KillMessage = "kill";
    public const string NoticeMessage = "notice";

    public const int OrganizationFriend = 0;
    public const int OrganizationEnemy = 1;

    public const int CollisionGroupNone = 0;
    public const int CollisionGroupAircraft = 1;
    public const int CollisionGroupMissile = 2;
    public const int CollisionGroupGunBullet = 4;
    public const int CollisionGroupGround = 8;

    public static readonly float SearchOperationRange = NauticalMileToMeter(10.0f);

    public static float WindowAspectRatio { get { return GraphicsDeviceContext.Instance.BackBufferAspectRatio; } }

    #region Controller scripts.
    private static GamePad gamePad = new GamePad();

    public static bool nowpressed(GamePad.LogicalButton button)
    {
        return gamePad.GetButtonState(button) == 1;
    }

    public static bool pressed(GamePad.LogicalButton button)
    {
        return 0 < gamePad.GetButtonState(button);
    }

    public static bool released(GamePad.LogicalButton button)
    {
        return gamePad.GetButtonState(button) <= 0;
    }

    public static bool nowreleased(GamePad.LogicalButton button)
    {
        return gamePad.GetButtonState(button) == -1;
    }

    public static bool nowpressed(Keyboard.KeyCode code)
    {
        return gamePad.GetKeyState(code) == 1;
    }

    public static bool pressed(Keyboard.KeyCode code)
    {
        return 0 < gamePad.GetKeyState(code);
    }

    public static bool released(Keyboard.KeyCode code)
    {
        return gamePad.GetKeyState(code) <= 0;
    }

    public static bool nowreleased(Keyboard.KeyCode code)
    {
        return gamePad.GetKeyState(code) == -1;
    }

    public static int getPressTimeLength(GamePad.LogicalButton button)
    {
        return Math.Max(gamePad.GetButtonState(button), 0);
    }

    public static Tuple<double, double> getAnalogStickAxis1()
    {
        return gamePad.Axis1;
    }

    public static Tuple<double, double> getAnalogStickAxis2()
    {
        return gamePad.Axis2;
    }
    #endregion

    #region 2D Graphics scripts.
    private static Matrix4x3 viewing { get { return Entity.Find("camera2d").Get<CameraComponent>().ViewingMatrix; } }
    private static Matrix4x4 projection { get { return Entity.Find("projector2d").Get<ProjectorComponent>().ProjectionMatrix; } }
    private static RasterizerState rasterizerState = new RasterizerState();
    private static DepthStencilState depthStencilState = new DepthStencilState();

    public static void draw(Texture2D tex)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(depthStencilState);
        Graphics2D.Instance.SetTexture(tex);
        Graphics2D.Instance.SetMatrix(EngineScript.world * viewing * projection);
        Graphics2D.Instance.DrawTexture();
    }

    public static void draw(Texture2D tex, float u0, float v0, float u1, float v1)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(depthStencilState);
        Graphics2D.Instance.SetTexture(tex);
        Graphics2D.Instance.SetMatrix(EngineScript.world * viewing * projection);
        Graphics2D.Instance.SetVertexPositions(-0.5f, 0.5f, 0.5f, -0.5f);
        Graphics2D.Instance.SetTextureCoords(u0, v0, u1, v1);
        Graphics2D.Instance.DrawTextureWithDynamical();
    }

    public static void drawThreshold(Texture2D tex, float u0, float v0, float u1, float v1)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(depthStencilState);
        Graphics2D.Instance.SetTexture(tex);
        Graphics2D.Instance.SetMatrix(EngineScript.world * viewing * projection);
        Graphics2D.Instance.SetColorThreshold(0, 0, 0, 0, 1, 1, 1, 1);
        Graphics2D.Instance.SetTextureThreshold(u0, v0, u1, v1);
        Graphics2D.Instance.DrawTextureWithThreshold();
    }

    public static void rectangle()
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(depthStencilState);
        Graphics2D.Instance.SetMatrix(EngineScript.world * viewing * projection);
        Graphics2D.Instance.DrawRectangle();
    }

    public static void rectangle(float x0, float y0, float x1, float y1)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(depthStencilState);
        Graphics2D.Instance.SetMatrix(EngineScript.world * viewing * projection);
        Graphics2D.Instance.SetVertexPositions(x0, y0, x1, y1);
        Graphics2D.Instance.DrawRectangleWithDynamical();
    }

    public static void font(Font _font)
    {
        Graphics2D.Instance.SetFont(_font);
    }

    public static void color(float rgb)
    {
        Graphics2D.Instance.SetColor(new Color(rgb, rgb, rgb));
    }

    public static void color(float r, float g, float b)
    {
        Graphics2D.Instance.SetColor(new Color(r, g, b));
    }

    public static void color(float r, float g, float b, float a)
    {
        Graphics2D.Instance.SetColor(new Color(r, g, b, a));
    }

    public static void color(Color color)
    {
        Graphics2D.Instance.SetColor(color);
    }

    public static void color(ColorCode code)
    {
        Graphics2D.Instance.SetColor(new Color(code));
    }

    public static void write(string text, TextAlignment horizontal = TextAlignment.Left, TextAlignment vertical = TextAlignment.Top)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(depthStencilState);
        Graphics2D.Instance.SetMatrix(EngineScript.world * viewing * projection);
        Graphics2D.Instance.DrawText(text, horizontal, vertical);
    }

    public static void blend(BlendState state)
    {
        GraphicsDeviceContext.Instance.SetBlendState(state);
    }

    public static void addressing(SamplerState state)
    {
        Graphics2D.Instance.SetAddreessMode(state);
    }
    #endregion

    public static void Create()
    {
        DefaultFont.Create("Consolas", 64);

        NoBlend.Create(BlendOperation.None);
        Addition.Create(BlendOperation.Add, BlendFactor.One, BlendFactor.One);
        HalfAddition.Create(BlendOperation.Add, BlendFactor.One, BlendFactor.InvSrcAlpha);
        Subtraction.Create(BlendOperation.RevSubtract, BlendFactor.One, BlendFactor.One);
        Multiplication.Create(BlendOperation.Add, BlendFactor.Zero, BlendFactor.SrcColor);
        Reverse.Create(BlendOperation.Add, BlendFactor.InvDestColor, BlendFactor.InvSrcColor);
        AlphaBlend.Create(BlendOperation.Add, BlendFactor.SrcAlpha, BlendFactor.InvSrcAlpha);

        Wrap.Create(TextureAddressMode.Wrap, TextureAddressMode.Wrap, TextureAddressMode.Wrap);
        Mirror.Create(TextureAddressMode.Mirror, TextureAddressMode.Mirror, TextureAddressMode.Mirror);

        CullingOn.Create(CullMode.Back, FillMode.Solid);
        CullingOff.Create(CullMode.None, FillMode.Solid);

        ZTestOn.Create(true, false, true);
        ZTestOnWriteOff.Create(true, false, false);
        ZTestOff.Create(false, false, false);

        font(DefaultFont);

        ExplosionSound.Create("res/sound/explosion1.wav");
        LargeExplosionSound.Create("res/sound/explosion2.wav");
        JetSound.Create("res/sound/burner_f15.wav");
        LockonSound.Create("res/sound/lockon4.wav");
        LockonSound.Volume = 0.25;
        AlertSound.Create("res/sound/alert2.wav");
        AlertSound.Volume = 0.25;
        BulletSound.Create("res/sound/bullet.wav");
        BulletHitSound.Create("res/sound/bulletHit.wav");
        BulletHitSound.Volume = 0.1;

        Graphics2D.Instance.Create();
        color(ColorCode.White);

        rasterizerState.Create(CullMode.None, FillMode.Solid);
        depthStencilState.Create(false, false, false);
    }

    public static void Update()
    {
        gamePad.Update();
    }

    public static void Release()
    {
        var type = typeof(GameScript);
        var fields = type.GetFields(BindingFlags.Static);
        foreach (var field in fields)
        {
            var var = field.GetValue(type);
            if ((IDisposable)var != null)
                (var as IDisposable).Dispose();
            field.SetValue(type, null);
        }
    }
}
