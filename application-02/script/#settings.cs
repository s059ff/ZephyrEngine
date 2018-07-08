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
	public static Dictionary<string, string> loadSettings (string path)
	{
		Dictionary<string, string> settings = new Dictionary<string, string> ();
		using (var stream = new StreamReader (path)) {
			string s = string.Empty;
			while ((s = stream.ReadLine ()) != null) {
				Regex regex = new Regex (@"(?<name>\w+)\s*=\s*(?<value>.+)");
				Match match = regex.Match (s);
				string name = match.Groups ["name"].Value.Trim ();
				string value = match.Groups ["value"].Value.Trim ();
				settings.Add (name, value);
			}
		}
		return settings;
	}
}
