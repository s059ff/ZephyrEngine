using Double = ZephyrSharp.ValueWrapper<double>;
using Float = ZephyrSharp.ValueWrapper<float>;
using Integer = ZephyrSharp.ValueWrapper<int>;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Text.RegularExpressions;
using System.Timers;
using Texture = ZephyrSharp.Graphics.Texture2D;
using ZephyrSharp;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using ZephyrSharp.Scripting;
using ZephyrSharp.Sound;

public partial class Script : System.Object
{
	// ---------- For Basic C# library ----------
	// ---------- For Xepher Game Engine library ----------
	// ---------- Graphics Macros ----------
	// ---------- Input Macros ----------
	// ---------- Using Default Namespace ----------
	// ---------- Using GameEngine Namespace ----------
	// ---------- Class Alias ----------
	// 数学定数
	public const float PI = 3.14159265359f;

	public const float PI2 = 3.14159265359f * 2.0f;

	public const float PIOver2 = 3.14159265359f / 2.0f;

	public const float PIOver4 = 3.14159265359f / 4.0f;

	public const float Napier = 2.7182818284590452353602874713526624977572470936999595749669F;

	// 重力加速度[m / frame^2]
	public const float Gravity = 9.80665f / 60 / 60;

	// 数学関数 (float)
	public static float sin (float x)
	{
		return (float)Math.Sin (x);
	}

	public static float cos (float x)
	{
		return (float)Math.Cos (x);
	}

	public static float tan (float x)
	{
		return (float)Math.Tan (x);
	}

	public static float asin (float x)
	{
		return (float)Math.Asin (x);
	}

	public static float acos (float x)
	{
		return (float)Math.Acos (x);
	}

	public static float atan (float x)
	{
		return (float)Math.Atan (x);
	}

	public static float atan2 (float y, float x)
	{
		return (float)Math.Atan2 (y, x);
	}

	public static float abs (float x)
	{
		return (float)Math.Abs (x);
	}

	public static float ceil (float x)
	{
		return (float)Math.Ceiling (x);
	}

	public static float floor (float x)
	{
		return (float)Math.Floor (x);
	}

	public static float round (float x)
	{
		return (float)Math.Round (x);
	}

	public static int sign (float x)
	{
		return Math.Sign (x);
	}

	public static float sqrt (float x)
	{
		return (float)Math.Sqrt (x);
	}

	public static float log (float x)
	{
		return (float)Math.Log (x);
	}

	public static float exp (float x)
	{
		return (float)Math.Exp (x);
	}

	public static float pow (float x, float y)
	{
		return (float)Math.Pow (x, y);
	}

	public static float square (float x)
	{
		return x * x;
	}

	// 比較
	public static int max (int a, int b)
	{
		return a > b ? a : b;
	}

	public static int min (int a, int b)
	{
		return a < b ? a : b;
	}

	public static float max (float a, float b)
	{
		return a > b ? a : b;
	}

	public static float min (float a, float b)
	{
		return a < b ? a : b;
	}

	// 角度変換
	public static float deg2rad (float deg)
	{
		return deg / 180.0f * (float)PI;
	}

	public static float rad2deg (float rad)
	{
		return rad / (float)PI * 180.0f;
	}

	// 乱数
	public static int uniform (int min, int max)
	{
		return new System.Random ().Next (min, max + 1);
	}

	public static float uniform (float min = 0, float max = 1)
	{
		return _engine.Random (new UniformDistribution (min, max));
	}

	public static float normal (float mean = 0, float variance = 1)
	{
		return _engine.Random (new NormalDistribution (mean, variance));
	}

	// 制限
	public static int clamp (int x, int min, int max)
	{
		return x < min ? min : x > max ? max : x;
	}

	public static float clamp (float x, float min, float max)
	{
		return x < min ? min : x > max ? max : x;
	}

	public static Vector3 clamp (Vector3 x, float min, float max)
	{
		float k = x.Magnitude;
		x.Normalize ();
		return clamp (k, min, max) * x;
	}

	// 制限
	public static void clamp (ref int x, int min, int max)
	{
		x = clamp (x, min, max);
	}

	public static void clamp (ref float x, float min, float max)
	{
		x = clamp (x, min, max);
	}

	// 正数に制限
	public static int positive (int x)
	{
		return x > 0 ? x : 0;
	}

	public static float positive (float x)
	{
		return x > 0 ? x : 0;
	}

	// 負数に制限
	public static int negative (int x)
	{
		return x < 0 ? x : 0;
	}

	public static float negative (float x)
	{
		return x < 0 ? x : 0;
	}

	// 範囲内か調べる
	public static bool is_inner (int value, int min, int max)
	{
		return value >= min && value <= max;
	}

	public static bool is_inner (float value, float min, float max)
	{
		return value >= min && value <= max;
	}

	// 範囲外か調べる
	public static bool is_outer (int value, int min, int max)
	{
		return value < min || value > max;
	}

	public static bool is_outer (float value, float min, float max)
	{
		return value < min || value > max;
	}

	// 線形写像
	public static float map (float x, float minx, float maxx, float miny, float maxy)
	{
		float a = (maxy - miny) / (maxx - minx);
		float y = a * (x - minx) + miny;
		return y;
	}

	// ラジアンから度数に変換する
	public static float RadianToDegree (float radian)
	{
		return radian * 180.0f / PI;
	}

	// 度数からラジアンに変換する
	public static float DegreeToRadian (float degree)
	{
		return degree * PI / 180.0f;
	}

	// 度数からラジアンに変換する
	public static float DegreeToRadian (int degree)
	{
		return degree * PI / 180.0f;
	}

	// 速度[m/frame]を秒速[m/s]に変換する
	public static float ToMeterPerSecond (float velocity)
	{
		return velocity * 60;
	}

	// 速度[m/frame]を時速[m/h]に変換する
	public static float ToMeterPerHour (float velority)
	{
		return ToMeterPerSecond (velority) * 60 * 60;
	}

	// 速度[m/frame]を時速[km/h]に変換する
	public static float ToKmPerHour (float velority)
	{
		return ToMeterPerHour (velority) / 1000;
	}

	// 速度[m/frame]をノット[kt]に変換する
	public static float ToKnot (float velocity)
	{
		return ToMeterPerSecond (velocity) * 1.94384f;
	}

	// メートルを海里に変換する
	public static float ToNauticalMile (float meter)
	{
		return 1.852f * meter;
	}

	// メートルをフィートに変換する
	public static float ToFeet (float meter)
	{
		return 3.281f * meter;
	}

	// 海里をメートルに変換する
	public static float NauticalMileToMeter (float nm)
	{
		return nm / 1.852f;
	}

	public static readonly RandomEngine _engine = new RandomEngine ();

	public static void initialize ()
	{
		initialize0 ();
		initialize1 ();
	}

	public static void finalize ()
	{
		finalize0 ();
	}

	public static void update ()
	{
		update0 ();
		update1 ();
	}
}
