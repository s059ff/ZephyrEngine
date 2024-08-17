using Double = ZephyrSharp.ValueWrapper<double>;
using Float = ZephyrSharp.ValueWrapper<float>;
using Integer = ZephyrSharp.ValueWrapper<int>;
using System.Collections.Generic;
using System.Collections;
using System.Diagnostics;
using System.IO;
using System.Text.RegularExpressions;
using System.Timers;
using System;
using Texture = ZephyrSharp.Graphics.Texture2D;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using ZephyrSharp.Scripting;
using ZephyrSharp.Sound;
using ZephyrSharp;
public class Script
{
public static void print(string text, params object[] args)
{
    Console.Write(text, args);
}
public static void println(string text, params object[] args)
{
    Console.WriteLine(text, args);
}
public static void print(object o)
{
    Console.Write(o);
}
public static void println(object o)
{
    Console.WriteLine(o);
}
public static BlendState NoBlend = new BlendState();
public static BlendState Addition = new BlendState();
public static BlendState HalfAddition = new BlendState();
public static BlendState Subtraction = new BlendState();
public static BlendState Multiplication = new BlendState();
public static BlendState Reverse = new BlendState();
public static BlendState AlphaBlend = new BlendState();
public static SamplerState Wrap = new SamplerState();
public static SamplerState Mirror = new SamplerState();
public static RasterizerState CullingOn = new RasterizerState();
public static RasterizerState CullingOff = new RasterizerState();
public static DepthStencilState ZTestOn = new DepthStencilState();
public static DepthStencilState ZTestOnWriteOff = new DepthStencilState();
public static DepthStencilState ZTestOff = new DepthStencilState();
public const string UpdateMessage = "update";
public const string RenderDepthMapMessage = "render depth map";
public const string RenderMessage = "render";
public const string TranslucentRenderMessage = "translucent render";
public const string DrawMessage = "draw";
public static void __initialize_2872()
{
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
}
public static void __finalize_3933()
{
    NoBlend.Dispose();
    Addition.Dispose();
    HalfAddition.Dispose();
    Subtraction.Dispose();
    Multiplication.Dispose();
    Reverse.Dispose();
    AlphaBlend.Dispose();
    Wrap.Dispose();
    Mirror.Dispose();
    CullingOn.Dispose();
    CullingOff.Dispose();
    ZTestOn.Dispose();
    ZTestOnWriteOff.Dispose();
    ZTestOff.Dispose();
}
public static void __update_5170()
{
    _keyboard.Update();
    _mouse.Update();
    mouseX = _mouse.X;
    mouseY = _mouse.Y;
}
public static int getkey(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code);
}
public static bool nowpressed(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) == 1;
}
public static bool pressed(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) > 0;
}
public static bool released(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) <= 0;
}
public static bool nowreleased(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) == -1;
}
public static bool click()
{
    return _mouse.Left > 0;
}
public static bool clickL()
{
    return _mouse.Left > 0;
}
public static bool clickR()
{
    return _mouse.Right > 0;
}
public static int mouseX, mouseY;
public static Keyboard _keyboard = new Keyboard();
public static Mouse _mouse = new Mouse();
public static void assert(bool b)
{
    assert(b, "エラーが発生しました。");
}
public static void assert(bool b, string comment)
{
    if (!b) 
    { 
        MessageBox.Show(
            comment + Environment.NewLine 
            + "スタックトレース:" + Environment.NewLine 
            + Environment.StackTrace, "エラーが発生しました。", MessageBoxIcon.Error); 
        throw new RuntimeException(comment); 
    }
}
public static void stacktrace()
{
    MessageBox.Show(
        "スタックトレース:" + Environment.NewLine + Environment.StackTrace, 
        "スタックトレース", MessageBoxIcon.Information); 
}
public static void pause()
{
    MessageBox.Show("一時停止", "一時停止", MessageBoxIcon.Information);
}
public static void mesbox()
{
    MessageBox.Show("", "");
}
public static void mesbox(string contents)
{
    MessageBox.Show(contents, "");
}
public static void mesbox(string contents, string title)
{
    MessageBox.Show(contents, title);
}
public static void dump(object obj)
{
    string text = string.Empty;
    {
        var infos = obj.GetType().GetFields();
        foreach (var info in infos)
        {
            text += string.Format("{0} = {1}\n", info.Name, info.GetValue(obj).ToString());
        }
    }
    {
        var infos = obj.GetType().GetProperties();
        foreach (var info in infos)
        {
            text += string.Format("{0} = {1}\n", info.Name, info.GetValue(obj).ToString());
        }
    }
    print(text);
}
public static void chdir(string dir)
{
    Directory.SetCurrentDirectory(dir);
}
public static void mkdir(string dir)
{
    Directory.CreateDirectory(dir);
}
public static Entity instantiate()
{
    return Entity.Instantiate();
}
public static void kill(Entity e)
{
    assert(e != null, "Null reference exception.");
    Entity.Kill(e);
}
public static void attach(Entity entity, EntityComponent comp)
{
    entity.Attach(comp);
}
public static void attach<Component>(Entity entity) where Component : EntityComponent, new()
{
    entity.Attach(new Component());
}
public const float PI = 3.14159265359f;
public const float PI2 = 3.14159265359f * 2.0f;
public const float PIOver2 = 3.14159265359f / 2.0f;
public const float PIOver4 = 3.14159265359f / 4.0f;
public const float Napier = 2.7182818284590452353602874713526624977572470936999595749669F;
public const float Gravity = 9.80665f / 60 / 60;
public static float sin(float x) { return (float)Math.Sin(x); }
public static float cos(float x) { return (float)Math.Cos(x); }
public static float tan(float x) { return (float)Math.Tan(x); }
public static float asin(float x) { return (float)Math.Asin(x); }
public static float acos(float x) { return (float)Math.Acos(x); }
public static float atan(float x) { return (float)Math.Atan(x); }
public static float atan2(float y, float x) { return (float)Math.Atan2(y, x); }
public static float abs(float x) { return (float)Math.Abs(x); }
public static float ceil(float x) { return (float)Math.Ceiling(x); }
public static float floor(float x) { return (float)Math.Floor(x); }
public static float round(float x) { return (float)Math.Round(x); }
public static int sign(float x) { return Math.Sign(x); }
public static float sqrt(float x) { return (float)Math.Sqrt(x); }
public static float log(float x) { return (float)Math.Log(x); }
public static float exp(float x) { return (float)Math.Exp(x); }
public static float pow(float x, float y) { return (float)Math.Pow(x, y); }
public static float square(float x) { return x * x; }
public static int max(int a, int b) { return a > b ? a : b; }
public static int min(int a, int b) { return a < b ? a : b; }
public static float max(float a, float b) { return a > b ? a : b; }
public static float min(float a, float b) { return a < b ? a : b; }
public static float deg2rad(float deg) { return deg / 180.0f * (float)PI; }
public static float rad2deg(float rad) { return rad / (float)PI * 180.0f; }
public static int uniform(int min, int max) { return new System.Random().Next(min, max + 1); }
public static float uniform(float min = 0, float max = 1) { return _engine.Random(new UniformDistribution(min, max)); }
public static float normal(float mean = 0, float variance = 1) { return _engine.Random(new NormalDistribution(mean, variance)); }
public static int clamp(int x, int min, int max) { return x < min ? min : x > max ? max : x; }
public static float clamp(float x, float min, float max) { return x < min ? min : x > max ? max : x; }
public static Vector3 clamp(Vector3 x, float min, float max)
{
    float k = x.Magnitude;
    x.Normalize();
    return clamp(k, min, max) * x;
}
public static void clamp(ref int x, int min, int max) { x = clamp(x, min, max); }
public static void clamp(ref float x, float min, float max) { x = clamp(x, min, max); }
public static int positive(int x) { return x > 0 ? x : 0; }
public static float positive(float x) { return x > 0 ? x : 0; }
public static int negative(int x) { return x < 0 ? x : 0; }
public static float negative(float x) { return x < 0 ? x : 0; }
public static bool is_inner(int value, int min, int max) { return value >= min && value <= max; }
public static bool is_inner(float value, float min, float max) { return value >= min && value <= max; }
public static bool is_outer(int value, int min, int max) { return value < min || value > max; }
public static bool is_outer(float value, float min, float max) { return value < min || value > max; }
public static float map(float x, float minx, float maxx, float miny, float maxy)
{
    float a = (maxy - miny) / (maxx - minx);
    float y = a * (x - minx) + miny;
    return y;
}
public static float RadianToDegree(float radian)
{
    return radian * 180.0f / PI;
}
public static float DegreeToRadian(float degree)
{
    return degree * PI / 180.0f;
}
public static float DegreeToRadian(int degree)
{
    return degree * PI / 180.0f;
}
public static float ToMeterPerSecond(float velocity)
{
    return velocity * 60;
}
public static float ToMeterPerHour(float velority)
{
    return ToMeterPerSecond(velority) * 60 * 60;
}
public static float ToKmPerHour(float velority)
{
    return ToMeterPerHour(velority) / 1000;
}
public static float ToKnot(float velocity)
{
    return ToMeterPerSecond(velocity) * 1.94384f;
}
public static float ToNauticalMile(float meter)
{
    return 1.852f * meter;
}
public static float ToFeet(float meter)
{
    return 3.281f * meter;
}
public static float NauticalMileToMeter(float nm)
{
    return nm / 1.852f;
}
public static RandomEngine _engine = new RandomEngine();
Dictionary<string, string> loadSettings(string path)
{
    Dictionary<string, string> settings = new Dictionary<string, string>();
    using (var stream = new StreamReader(path))
    {
        string s = string.Empty;
        while ((s = stream.ReadLine()) != null)
        {
            Regex regex = new Regex(@"(?<name>\w+)\s*=\s*(?<value>.+)");
            Match match = regex.Match(s);
            string name = match.Groups["name"].Value.Trim();
            string value = match.Groups["value"].Value.Trim();
            settings.Add(name, value);
        }
    }
    return settings;
}
public static int frame;
public static float fps;
public static void __initialize_17608()
{
    _timer.Interval = 1000;
    _timer.AutoReset = true;
    _timer.Elapsed += (o, e) => { fps = _count; _count = 0; };
    _timer.Start();
}
public static void __update_17795()
{
    frame++;
    _count++;
}
public static Timer _timer = new Timer();
public static int _count;
public static void identity()
{
    _world.Identity();
}
public static void translate(float x, float y, float z)
{
    _world.Translate(x, y, z);
}
public static void translate(float x, float y)
{
    _world.Translate(x, y);
}
public static void translate(Vector3 v)
{
    _world.Translate(v.X, v.Y, v.Z);
}
public static void translate(Vector2 v)
{
    _world.Translate(v.X, v.Y, 0);
}
public static void rotate(float r)
{
    _world.RotateZ(r);
}
public static void scale(float sx, float sy)
{
    _world.Scale(sx, sy, 1.0f);
}
public static void scale(float s)
{
    _world.Scale(s);
}
public static void transform(Matrix4x3 m)
{
    _world.Transform(new Matrix4x4(m));
}
public static void transform(Matrix4x4 m)
{
    _world.Transform(m);
}
public static void pushMatrix()
{
    _matrix_stack.Push(_world);
}
public static void popMatrix()
{
    _world = _matrix_stack.Pop();
}
public static void loadMatrix(Matrix3x2 m)
{
    _world = new Matrix4x4(m);
}
public static void loadMatrix(Matrix4x3 m)
{
    _world = new Matrix4x4(m);
}
public static void loadMatrix(Matrix4x4 m)
{
    _world = m;
}
public static Matrix4x4 _world = new Matrix4x4().Identity();
public static Stack<Matrix4x4> _matrix_stack = new Stack<Matrix4x4>();
public static void finalize() { __finalize_3933(); }
public static void initialize() { __initialize_2872();__initialize_17608(); }
public static void update() { __update_5170();__update_17795(); }
}