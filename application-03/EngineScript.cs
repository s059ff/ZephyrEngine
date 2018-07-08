using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text.RegularExpressions;
using System.Timers;
using ZephyrSharp;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Linalg;

public class EngineScript
{
    #region Console functions.
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
    #endregion

    #region Debug functions.
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
    #endregion

    #region Directory functions.
    public static void chdir(string dir)
    {
        Directory.SetCurrentDirectory(dir);
    }

    public static void mkdir(string dir)
    {
        Directory.CreateDirectory(dir);
    }
    #endregion

    #region Distmap functions.
    public static float[,] distmap(string imagePath)
    {
        float[,] probablities = null;
        using (Bitmap bitmap = new Bitmap(imagePath))
        {
            probablities = new float[bitmap.Height, bitmap.Width];
            for (int i = 0; i < bitmap.Height; i++)
            {
                for (int j = 0; j < bitmap.Width; j++)
                {
                    var pixel = bitmap.GetPixel(j, i);
                    probablities[i, j] = pixel.R / 255.0f;
                }
            }
        }
        return probablities;
    }
    #endregion

    #region Entity functions.
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
    #endregion

    #region Heightmap functions.
    public static float[,] heightmap(string imagePath, int splitX, int splitY, float min, float max)
    {
        float[,] heights = new float[splitY, splitX];
        using (Bitmap bitmap = new Bitmap(imagePath))
        {
            for (int i = 0; i < splitY; i++)
            {
                for (int j = 0; j < splitX; j++)
                {
                    var pixel = bitmap.GetPixel(bitmap.Width * j / splitX, bitmap.Height * i / splitY);
                    heights[i, j] = pixel.R / 255.0f * (max - min) + min;
                }
            }
        }
        return heights;
    }
    #endregion

    #region Math functions.
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

    public static int uniform(int min, int max) { return new Random().Next(min, max + 1); }

    public static float uniform(float min = 0, float max = 1) { return _engine.Random(new UniformDistribution(min, max)); }

    public static float normal(float mean = 0, float variance = 1) { return _engine.Random(new NormalDistribution(mean, variance)); }

    public static float random(float[] probs)
    {
        var dist = new DiscreteDistribution(probs);
        int x = _engine.Random(dist);
        return (float)x;
    }

    public static float[] randoms(float[] probs, int count)
    {
        int W = probs.Length;
        var dist = new DiscreteDistribution(probs);
        float[] values = new float[count];
        for (int i = 0; i < count; i++)
        {
            int x = _engine.Random(dist);
            values[i] = x / (float)W;
        }
        return values;
    }

    public static Tuple<float, float>[] randoms(float[,] probs, int count)
    {
        var _probs = probs.Cast<float>().ToArray();
        var dist = new DiscreteDistribution(_probs);
        int H = probs.GetLength(0);
        int W = probs.GetLength(1);
        Tuple<float, float>[] values = new Tuple<float, float>[count];
        for (int i = 0; i < count; i++)
        {
            int n = _engine.Random(dist);
            int y = n / H;
            int x = n % H;
            values[i] = new Tuple<float, float>(y / (float)H, x / (float)W);
        }
        return values;
    }

    public static int clamp(int x, int min, int max) { return x < min ? min : x > max ? max : x; }

    public static float clamp(float x, float min, float max) { return x < min ? min : x > max ? max : x; }

    public static Vector3 clamp(Vector3 x, float min, float max)
    {
        float k = x.Magnitude;
        x.Normalize();
        return clamp(k, min, max) * x;
    }

    public static double clamp(double x, double min, double max) { return x < min ? min : x > max ? max : x; }

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

    public static float close(float value, float desiredValue, float delta)
    {
        if (abs(value - desiredValue) < delta)
            return desiredValue;
        else
            return value + ((desiredValue > value) ? delta : -delta);
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

    static readonly RandomEngine _engine = new RandomEngine();
    #endregion

    #region Setting functions.
    public static Dictionary<string, string> loadSettings(string path)
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
    #endregion

    #region Transform functions.
    public static void identity()
    {
        world.Identity();
    }

    public static void translate(float x, float y, float z)
    {
        world.Translate(x, y, z);
    }

    public static void translate(float x, float y)
    {
        world.Translate(x, y);
    }

    public static void translate(Vector3 v)
    {
        world.Translate(v.X, v.Y, v.Z);
    }

    public static void translate(Vector2 v)
    {
        world.Translate(v.X, v.Y, 0);
    }

    public static void rotate(float r)
    {
        world.RotateZ(r);
    }

    public static void scale(float sx, float sy)
    {
        world.Scale(sx, sy, 1.0f);
    }

    public static void scale(float s)
    {
        world.Scale(s);
    }

    public static void transform(Matrix4x3 m)
    {
        world.Transform(new Matrix4x4(m));
    }

    public static void transform(Matrix4x4 m)
    {
        world.Transform(m);
    }

    public static void pushMatrix()
    {
        _matrix_stack.Push(world);
    }

    public static void popMatrix()
    {
        world = _matrix_stack.Pop();
    }

    public static void loadMatrix(Matrix3x2 m)
    {
        world = new Matrix4x4(m);
    }

    public static void loadMatrix(Matrix4x3 m)
    {
        world = new Matrix4x4(m);
    }

    public static void loadMatrix(Matrix4x4 m)
    {
        world = m;
    }

    public static Matrix4x4 world = new Matrix4x4().Identity();

    static Stack<Matrix4x4> _matrix_stack = new Stack<Matrix4x4>();
    #endregion

    #region Time functions.
    public static int frame;
    public static float fps;

    static Timer _timer = new Timer()
    {
        Interval = 1000,
        AutoReset = true,
    };
    static int _count;
    #endregion

    public static void initialize()
    {
        _timer.Elapsed += (o, e) => { fps = _count; _count = 0; };
        _timer.Start();
    }

    public static void update()
    {
        frame++;
        _count++;
    }

    public static void finalize()
    {
        var type = typeof(EngineScript);
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
