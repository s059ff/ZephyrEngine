using System;
using System.Collections.Generic;
using System.Linq;
using ZephyrSharp;
using ZephyrSharp.Linalg;

public static class EngineScript
{
    #region Debug functions.
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

    public static void assert(bool b)
    {
        assert(b, "Assersion failed!");
    }

    public static void assert(bool b, string comment)
    {
        if (!b)
        {
            throw new RuntimeException(comment);
        }
    }
    #endregion

    #region Basic math functions.
    public const float PI = 3.14159265359f;
    public const float PI2 = 3.14159265359f * 2.0f;
    public const float PIOver2 = 3.14159265359f / 2.0f;
    public const float PIOver4 = 3.14159265359f / 4.0f;
    public const float Napier = 2.7182818284590452353602874713526624977572470936999595749669F;

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

    public static float deg2rad(float deg) { return deg / 180.0f * PI; }

    public static float rad2deg(float rad) { return rad / PI * 180.0f; }

    public static void srand(ulong seed) { randomizer = new RandomEngine(seed); }

    public static float uniform(float min = 0, float max = 1) { return randomizer.Random(new UniformDistribution(min, max)); }

    public static float normal(float mean = 0, float variance = 1) { return randomizer.Random(new NormalDistribution(mean, variance)); }

    public static int random(float[] probs) { return randomizer.Random(new DiscreteDistribution(probs)); }

    public static float clamp(float x, float min, float max) { return x < min ? min : x > max ? max : x; }

    public static float close(float value, float target, float delta)
    {
        assert(0 < delta);

        float diff = abs(value - target);
        if (diff < delta)
        {
            return target;
        }
        else
        {
            return value + ((value < target) ? delta : -delta);
        }
    }

    public static float[] linspace(float a, float b, int n)
    {
        assert(0 < n);
        if (n == 1)
        {
            return new float[] { (a + b) / 2 };
        }
        else
        {
            float delta = (b - a) / (n - 1);
            return Enumerable.Range(0, n).Select(i => delta * i / n).Select(v => v + a).ToArray();
        }
    }

    private static RandomEngine randomizer = new RandomEngine();
    #endregion

    #region Physical mathematics functions.
    public const float Gravity = 9.80665f / 60 / 60;

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
        return meter / 1852.0f;
    }

    public static float ToFeet(float meter)
    {
        return 3.281f * meter;
    }

    public static float NauticalMileToMeter(float nm)
    {
        return nm * 1852.0f;
    }
    #endregion

    #region Matrix transformation functions.
    public static void identity() { world = new Matrix4x3().Identity(); }

    public static void translate(float x, float y, float z) { world = world.Translate(x, y, z); }

    public static void translate(float x, float y) { world = world.Translate(x, y); }

    public static void translate(Vector3 v) { world = world.Translate(v.X, v.Y, v.Z); }

    public static void translate(Vector2 v) { world = world.Translate(v.X, v.Y, 0); }

    public static void rotate(float r) { world = world.RotateZ(r); }

    public static void scale(float sx, float sy) { world = world.Scale(sx, sy, 1.0f); }

    public static void scale(float s) { world = world.Scale(s); }

    public static void pushMatrix() { matrix_stack.Push(world); }

    public static void popMatrix() { world = matrix_stack.Pop(); }

    public static Matrix4x3 world { get; private set; }

    private static Stack<Matrix4x3> matrix_stack = new Stack<Matrix4x3>();
    #endregion
}
