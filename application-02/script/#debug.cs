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
	public static void assert (bool b)
	{
		assert (b, "エラーが発生しました。");
	}

	public static void assert (bool b, string comment)
	{
		if (!b) {
			MessageBox.Show (comment + Environment.NewLine + "スタックトレース:" + Environment.NewLine + Environment.StackTrace, "エラーが発生しました。", MessageBoxIcon.Error);
			throw new RuntimeException (comment);
		}
	}

	public static void stacktrace ()
	{
		MessageBox.Show ("スタックトレース:" + Environment.NewLine + Environment.StackTrace, "スタックトレース", MessageBoxIcon.Information);
	}

	public static void pause ()
	{
		MessageBox.Show ("一時停止", "一時停止", MessageBoxIcon.Information);
	}

	public static void mesbox ()
	{
		MessageBox.Show ("", "");
	}

	public static void mesbox (string contents)
	{
		MessageBox.Show (contents, "");
	}

	public static void mesbox (string contents, string title)
	{
		MessageBox.Show (contents, title);
	}

	public static void dump (object obj)
	{
		string text = string.Empty;
		{
			var infos = obj.GetType ().GetFields ();
			foreach (var info in infos) {
				text += string.Format ("{0} = {1}\n", info.Name, info.GetValue (obj).ToString ());
			}
		}
		{
			var infos = obj.GetType ().GetProperties ();
			foreach (var info in infos) {
				text += string.Format ("{0} = {1}\n", info.Name, info.GetValue (obj).ToString ());
			}
		}
		print (text);
	}
}
