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
	public static float[,] heightmap (string imagePath, int splitX, int splitY, float min, float max)
	{
		float[,] heights = new float[splitY, splitX];
		using (Bitmap bitmap = new Bitmap (imagePath)) {
			for (int i = 0; i < splitY; i++) {
				for (int j = 0; j < splitX; j++) {
					var pixel = bitmap.GetPixel (bitmap.Width * j / splitX, bitmap.Height * i / splitY);
					heights [i, j] = pixel.R / 255.0f * (max - min) + min;
				}
			}
		}
		return heights;
	}
}
