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
	public static BlendState NoBlend = new BlendState ();

	public static BlendState Addition = new BlendState ();

	public static BlendState HalfAddition = new BlendState ();

	public static BlendState Subtraction = new BlendState ();

	public static BlendState Multiplication = new BlendState ();

	public static BlendState Reverse = new BlendState ();

	public static BlendState AlphaBlend = new BlendState ();

	public static Font MeiryoUI = new Font ();

	public static Font MSMincho = new Font ();

	public static SamplerState Wrap = new SamplerState ();

	public static SamplerState Mirror = new SamplerState ();

	public static RasterizerState CullingOn = new RasterizerState ();

	public static RasterizerState CullingOff = new RasterizerState ();

	public static DepthStencilState ZTestOn = new DepthStencilState ();

	public static DepthStencilState ZTestOnWriteOff = new DepthStencilState ();

	public static DepthStencilState ZTestOff = new DepthStencilState ();

	public static ResourceManager ResourceManager = ResourceManager.Instance;

	public const string UpdateMessage = "update";

	public const string RenderMessage = "render";

	public const string TranslucentRenderMessage = "translucent render";

	public const string DrawMessage = "draw";

	public const string KillMessage = "kill";

	public const int Friend = 0;

	public const int Enemy = 1;

	public const float SearchOperationRange = 4000;

	public const float DisplayWidth = 1280;

	public const float DisplayHeight = 720;

	public const bool FullScreen = false;

	public const float DisplayAspect = DisplayWidth / DisplayHeight;

	public static void initialize0 ()
	{
		MeiryoUI.Create ("Meiryo UI", 64);
		MSMincho.Create ("ＭＳ 明朝", 64);
		NoBlend.Create (BlendOperation.None);
		Addition.Create (BlendOperation.Add, BlendFactor.One, BlendFactor.One);
		HalfAddition.Create (BlendOperation.Add, BlendFactor.One, BlendFactor.InvSrcAlpha);
		Subtraction.Create (BlendOperation.RevSubtract, BlendFactor.One, BlendFactor.One);
		Multiplication.Create (BlendOperation.Add, BlendFactor.Zero, BlendFactor.SrcColor);
		Reverse.Create (BlendOperation.Add, BlendFactor.InvDestColor, BlendFactor.InvSrcColor);
		AlphaBlend.Create (BlendOperation.Add, BlendFactor.SrcAlpha, BlendFactor.InvSrcAlpha);
		Wrap.Create (TextureAddressMode.Wrap, TextureAddressMode.Wrap, TextureAddressMode.Wrap);
		Mirror.Create (TextureAddressMode.Mirror, TextureAddressMode.Mirror, TextureAddressMode.Mirror);
		CullingOn.Create (CullMode.Back, FillMode.Solid);
		CullingOff.Create (CullMode.None, FillMode.Solid);
		ZTestOn.Create (true, false, true);
		ZTestOnWriteOff.Create (true, false, false);
		ZTestOff.Create (false, false, false);
		font (MeiryoUI);
	}

	public static void finalize0 ()
	{
		NoBlend.Dispose ();
		Addition.Dispose ();
		HalfAddition.Dispose ();
		Subtraction.Dispose ();
		Multiplication.Dispose ();
		Reverse.Dispose ();
		AlphaBlend.Dispose ();
		MeiryoUI.Dispose ();
		Wrap.Dispose ();
		Mirror.Dispose ();
		CullingOn.Dispose ();
		CullingOff.Dispose ();
		ZTestOn.Dispose ();
		ZTestOnWriteOff.Dispose ();
		ZTestOff.Dispose ();
	}
}
