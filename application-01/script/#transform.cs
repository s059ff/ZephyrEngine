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
	public static void identity ()
	{
		_world.Identity ();
	}

	public static void translate (float x, float y, float z)
	{
		_world.Translate (x, y, z);
	}

	public static void translate (float x, float y)
	{
		_world.Translate (x, y);
	}

	public static void translate (Vector3 v)
	{
		_world.Translate (v.X, v.Y, v.Z);
	}

	public static void translate (Vector2 v)
	{
		_world.Translate (v.X, v.Y, 0);
	}

	public static void rotate (float r)
	{
		_world.RotateZ (r);
	}

	public static void scale (float sx, float sy)
	{
		_world.Scale (sx, sy, 1.0f);
	}

	public static void scale (float s)
	{
		_world.Scale (s);
	}

	public static void transform (Matrix4x3 m)
	{
		_world.Transform (new Matrix4x4 (m));
	}

	public static void transform (Matrix4x4 m)
	{
		_world.Transform (m);
	}

	public static void pushMatrix ()
	{
		_matrix_stack.Push (_world);
	}

	public static void popMatrix ()
	{
		_world = _matrix_stack.Pop ();
	}

	public static void loadMatrix (Matrix3x2 m)
	{
		_world = new Matrix4x4 (m);
	}

	public static void loadMatrix (Matrix4x3 m)
	{
		_world = new Matrix4x4 (m);
	}

	public static void loadMatrix (Matrix4x4 m)
	{
		_world = m;
	}

	public static Matrix4x4 _world = new Matrix4x4 ().Identity ();

	public static Stack<Matrix4x4> _matrix_stack = new Stack<Matrix4x4> ();
}
