using System;
using System.Reflection;
using ZephyrSharp;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using ZephyrSharp.Sound;
using Color = ZephyrSharp.Graphics.Color;
using Font = ZephyrSharp.Graphics.Font;

public class GameScript : EngineScript
{
    #region Unit functions.
    public static Entity unit(string name, string squadronName, Vector3 pos, float angle)
    {
        Entity entity = Entity.Instantiate();
        entity.Name = name;
        entity.Attach(new TransformComponent());
        entity.Attach(new PhysicsComponent());
        entity.Attach(new CollisionComponent());
        entity.Attach(new JetComponent());
        entity.Attach(new AircraftComponent());
        entity.Attach(new AIComponent(Enemy));
        if (name == "player")
            entity.Attach(new PlayerComponent());
        else
            entity.Attach(new NPCAIComponent());
        entity.Attach(new SquadronComponent(squadronName));
        entity.Attach(new SoundComponent(JetSound));
        entity.Get<TransformComponent>().Matrix.RotateY(angle);
        entity.Get<TransformComponent>().Position = pos;
        entity.Get<SoundComponent>().LoopPlay();

        return entity;
    }
    #endregion

    #region Constant values.
    public static BlendState NoBlend = new BlendState();
    public static BlendState Addition = new BlendState();
    public static BlendState HalfAddition = new BlendState();
    public static BlendState Subtraction = new BlendState();
    public static BlendState Multiplication = new BlendState();
    public static BlendState Reverse = new BlendState();
    public static BlendState AlphaBlend = new BlendState();

    public static Font MeiryoUI = new Font();
    public static Font MSMincho = new Font();

    public static SamplerState Wrap = new SamplerState();
    public static SamplerState Mirror = new SamplerState();

    public static RasterizerState CullingOn = new RasterizerState();
    public static RasterizerState CullingOff = new RasterizerState();

    public static DepthStencilState ZTestOn = new DepthStencilState();
    public static DepthStencilState ZTestOnWriteOff = new DepthStencilState();
    public static DepthStencilState ZTestOff = new DepthStencilState();

    public const string UpdateMessage = "update";
    public const string RenderMessage = "render";
    public const string TranslucentRenderMessage = "translucent render";
    public const string DrawMessage = "draw";
    public const string KillMessage = "kill";

    public const int Friend = 0;
    public const int Enemy = 1;

    public const float SearchOperationRange = 4000;
    public const float DisplayWidth = 1280;
    public const float DisplayHeight = 720;
    public const bool FullScreen = false;
    public const float DisplayAspect = DisplayWidth / DisplayHeight;
    #endregion

    #region Sound script.
    public const double AffectionSoundRange = 500;
    public const double SonicSpeed = 340.0 / 60.0;

    public static double volume(double distance)
    {
        return (distance > 0) ? clamp(AffectionSoundRange / distance, 0, 1) : 1;
    }

    public static double frequency(double vo, double vs, uint f0)
    {
        double k = (SonicSpeed - vo) / (SonicSpeed - vs);
        return (uint)(k * f0);
    }
    #endregion

    #region Controller scripts.
    public static int mouseX, mouseY;
    public static int mouseDX, mouseDY, mouseDZ;
    static Keyboard _keyboard = new Keyboard();
    static Mouse _mouse = new Mouse();

    public static ButtonState getkey(KeyCode code)
    {
        return _keyboard.GetKeyState(code);
    }

    public static bool nowpressed(KeyCode code)
    {
        return _keyboard.GetKeyState(code) == ButtonState.NowPressed;
    }

    public static bool pressed(KeyCode code)
    {
        return _keyboard.GetKeyState(code) == ButtonState.Pressed;
    }

    public static bool released(KeyCode code)
    {
        return _keyboard.GetKeyState(code) == ButtonState.Released;
    }

    public static bool nowreleased(KeyCode code)
    {
        return _keyboard.GetKeyState(code) == ButtonState.NowReleased;
    }

    public static bool click()
    {
        return _mouse.Left == ButtonState.Pressed;
    }

    public static bool clickL()
    {
        return _mouse.Left == ButtonState.Pressed;
    }

    public static bool clickR()
    {
        return _mouse.Right == ButtonState.Pressed;
    }

    public static bool clickC()
    {
        return _mouse.Center == ButtonState.Pressed;
    }

    public static bool nowClick()
    {
        return _mouse.Left == ButtonState.NowPressed;
    }

    public static bool nowClickL()
    {
        return _mouse.Left == ButtonState.NowPressed;
    }

    public static bool nowClickR()
    {
        return _mouse.Right == ButtonState.NowPressed;
    }

    public static bool nowClickC()
    {
        return _mouse.Center == ButtonState.NowPressed;
    }
    #endregion

    #region 2D Graphics scripts.
    public static Matrix4x3 viewing { get { return Entity.Find("camera2d").Get<CameraComponent>().ViewingMatrix; } }
    public static Matrix4x4 projection { get { return Entity.Find("projector2d").Get<ProjectorComponent>().ProjectionMatrix; } }

    static RasterizerState _rasterizerState = new RasterizerState();
    static DepthStencilState _depthStencilState = new DepthStencilState();

    public static void draw(Texture2D tex)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(_rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(_depthStencilState);
        Graphics2D.Instance.SetTexture(tex);
        Graphics2D.Instance.SetMatrix(world * viewing * projection);
        Graphics2D.Instance.DrawTexture();
    }

    public static void draw(Texture2D tex, float u0, float v0, float u1, float v1)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(_rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(_depthStencilState);
        Graphics2D.Instance.SetTexture(tex);
        Graphics2D.Instance.SetMatrix(world * viewing * projection);
        Graphics2D.Instance.SetVertexPositions(-0.5f, 0.5f, 0.5f, -0.5f);
        Graphics2D.Instance.SetTextureCoords(u0, v0, u1, v1);
        Graphics2D.Instance.DrawTextureWithDynamical();
    }

    public static void drawThreshold(Texture2D tex, float u0, float v0, float u1, float v1)
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(_rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(_depthStencilState);
        Graphics2D.Instance.SetTexture(tex);
        Graphics2D.Instance.SetMatrix(world * viewing * projection);
        Graphics2D.Instance.SetColorThreshold(0, 0, 0, 0, 1, 1, 1, 1);
        Graphics2D.Instance.SetTextureThreshold(u0, v0, u1, v1);
        Graphics2D.Instance.DrawTextureWithThreshold();
    }

    public static void rectangle()
    {
        GraphicsDeviceContext.Instance.SetRasterizerState(_rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(_depthStencilState);
        Graphics2D.Instance.SetMatrix(world * viewing * projection);
        Graphics2D.Instance.DrawRectangle();
    }

    public static void font(Font _font)
    {
        Graphics2D.Instance.SetFont(_font);
    }

    public static void color(float rgb)
    {
        Graphics2D.Instance.SetColor(new ZephyrSharp.Graphics.Color(rgb, rgb, rgb));
    }

    public static void color(float r, float g, float b)
    {
        Graphics2D.Instance.SetColor(new ZephyrSharp.Graphics.Color(r, g, b));
    }

    public static void color(float r, float g, float b, float a)
    {
        Graphics2D.Instance.SetColor(new ZephyrSharp.Graphics.Color(r, g, b, a));
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
        GraphicsDeviceContext.Instance.SetRasterizerState(_rasterizerState);
        GraphicsDeviceContext.Instance.SetDepthStencilState(_depthStencilState);
        Graphics2D.Instance.SetMatrix(world * viewing * projection);
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

    public static SoundBuffer ExplosionSound = new SoundBuffer();
    public static SoundBuffer LargeExplosionSound = new SoundBuffer();
    public static SoundBuffer JetSound = new SoundBuffer();
    public static SoundBuffer LockonSound = new SoundBuffer();
    public static SoundBuffer AlertSound = new SoundBuffer();
    public static SoundBuffer BulletSound = new SoundBuffer();
    public static SoundBuffer BulletHitSound = new SoundBuffer();
    public static ResourceManager ResourceManager = new ResourceManager();

    public static void initialize()
    {
        MeiryoUI.Create("Meiryo UI", 64);
        MSMincho.Create("ＭＳ 明朝", 64);

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

        font(MeiryoUI);

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

        _rasterizerState.Create(CullMode.None, FillMode.Solid);
        _depthStencilState.Create(false, false, false);
    }

    public static void update()
    {
        _keyboard.Update();
        _mouse.Update();

        mouseX = _mouse.X;
        mouseY = _mouse.Y;
        mouseDX = _mouse.MovementX;
        mouseDY = _mouse.MovementY;
        mouseDZ = _mouse.MovementZ;
    }

    public static void finalize()
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

    public static SceneManager SceneManager = new SceneManager();
}
