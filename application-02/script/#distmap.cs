using Double = ZephyrSharp.ValueWrapper<double>;
using Float = ZephyrSharp.ValueWrapper<float>;
using Integer = ZephyrSharp.ValueWrapper<int>;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
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
	public static float[,] distmap (string imagePath)
	{
		float[,] probablities = null;
		using (Bitmap bitmap = new Bitmap (imagePath)) {
			probablities = new float[bitmap.Height, bitmap.Width];
			for (int i = 0; i < bitmap.Height; i++) {
				for (int j = 0; j < bitmap.Width; j++) {
					var pixel = bitmap.GetPixel (j, i);
					probablities [i, j] = pixel.R / 255.0f;
				}
			}
		}
		return probablities;
	}
}
