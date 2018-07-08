using Double = ZephyrSharp.ValueWrapper<double>;
using Float = ZephyrSharp.ValueWrapper<float>;
using Integer = ZephyrSharp.ValueWrapper<int>;
using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
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
	public const double AffectionSoundRange = 500;

	public const double SonicSpeed = 340.0 / 60.0;

	public static SoundBuffer ExplosionSound = new SoundBuffer ();

	public static SoundBuffer LargeExplosionSound = new SoundBuffer ();

	public static SoundBuffer JetSound = new SoundBuffer ();

	public static SoundBuffer LockonSound = new SoundBuffer ();

	public static SoundBuffer AlertSound = new SoundBuffer ();

	public static SoundBuffer BulletSound = new SoundBuffer ();

	public static SoundBuffer BulletHitSound = new SoundBuffer ();

	public static void initialize3 ()
	{
		ExplosionSound.Create ("res/sound/explosion1.wav");
		LargeExplosionSound.Create ("res/sound/explosion2.wav");
		JetSound.Create ("res/sound/burner_f15.wav");
		LockonSound.Create ("res/sound/lockon4.wav");
		LockonSound.Volume = 0.25;
		AlertSound.Create ("res/sound/alert2.wav");
		AlertSound.Volume = 0.25;
		BulletSound.Create ("res/sound/bullet.wav");
		BulletHitSound.Create ("res/sound/bulletHit.wav");
		BulletHitSound.Volume = 0.1;
	}

	public static void finalize1 ()
	{
		ExplosionSound.Dispose ();
		LargeExplosionSound.Dispose ();
		JetSound.Dispose ();
		LockonSound.Dispose ();
		AlertSound.Dispose ();
		BulletSound.Dispose ();
		BulletHitSound.Dispose ();
	}

	public static double volume (double distance)
	{
		return (distance > 0) ? clamp (AffectionSoundRange / distance, 0, 1) : 1;
	}

	public static double frequency (double vo, double vs, uint f0)
	{
		double k = (SonicSpeed - vo) / (SonicSpeed - vs);
		return (uint)(k * f0);
	}

	public static void initialize ()
	{
		initialize0 ();
		initialize1 ();
		initialize2 ();
		initialize3 ();
	}

	public static void finalize ()
	{
		finalize0 ();
		finalize1 ();
	}

	public static void update ()
	{
		update0 ();
		update1 ();
	}
}
