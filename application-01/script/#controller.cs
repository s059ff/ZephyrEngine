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
	public static void update0 ()
	{
		_keyboard.Update ();
		_mouse.Update ();
		mouseX = _mouse.X;
		mouseY = _mouse.Y;
	}

	public static ButtonState getkey (KeyCode code)
	{
		return _keyboard.GetKeyState (code);
	}

	public static bool nowpressed (KeyCode code)
	{
		return _keyboard.GetKeyState (code) == ButtonState.NowPressed;
	}

	public static bool pressed (KeyCode code)
	{
		return _keyboard.GetKeyState (code) == ButtonState.Pressed;
	}

	public static bool released (KeyCode code)
	{
		return _keyboard.GetKeyState (code) == ButtonState.Released;
	}

	public static bool nowreleased (KeyCode code)
	{
		return _keyboard.GetKeyState (code) == ButtonState.NowReleased;
	}

	public static bool click ()
	{
		return _mouse.Left == ButtonState.Pressed;
	}

	public static bool clickL ()
	{
		return _mouse.Left == ButtonState.Pressed;
	}

	public static bool clickR ()
	{
		return _mouse.Right == ButtonState.Pressed;
	}

	public static int mouseX, mouseY;

	public static Keyboard _keyboard = new Keyboard ();

	public static Mouse _mouse = new Mouse ();
}
