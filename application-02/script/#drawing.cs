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
	public static Matrix4x3 _viewing {
		get {
			return Entity.Find ("camera2d").Get<CameraComponent> ().ViewingMatrix;
		}
	}

	public static Matrix4x4 _projection {
		get {
			return Entity.Find ("projector2d").Get<ProjectorComponent> ().ProjectionMatrix;
		}
	}

	public static RasterizerState _rasterizerState = new RasterizerState ();

	public static DepthStencilState _depthStencilState = new DepthStencilState ();

	public static void initialize1 ()
	{
		Graphics2D.Instance.Create ();
		color (ColorCode.White);
		_rasterizerState.Create (CullMode.None, FillMode.Solid);
		_depthStencilState.Create (false, false, false);
	}

	public static void draw (Texture tex)
	{
		GraphicsDevice.Instance.SetRasterizerState (_rasterizerState);
		GraphicsDevice.Instance.SetDepthStencilState (_depthStencilState);
		Graphics2D.Instance.SetTexture (tex);
		Graphics2D.Instance.SetMatrix (_world * _viewing * _projection);
		Graphics2D.Instance.DrawTexture ();
	}

	public static void draw (Texture tex, float u0, float v0, float u1, float v1)
	{
		GraphicsDevice.Instance.SetRasterizerState (_rasterizerState);
		GraphicsDevice.Instance.SetDepthStencilState (_depthStencilState);
		Graphics2D.Instance.SetTexture (tex);
		Graphics2D.Instance.SetMatrix (_world * _viewing * _projection);
		Graphics2D.Instance.SetVertexPositions (-0.5f, 0.5f, 0.5f, -0.5f);
		Graphics2D.Instance.SetTextureCoords (u0, v0, u1, v1);
		Graphics2D.Instance.DrawTextureWithDynamical ();
	}

	public static void drawThreshold (Texture tex, float u0, float v0, float u1, float v1)
	{
		GraphicsDevice.Instance.SetRasterizerState (_rasterizerState);
		GraphicsDevice.Instance.SetDepthStencilState (_depthStencilState);
		Graphics2D.Instance.SetTexture (tex);
		Graphics2D.Instance.SetMatrix (_world * _viewing * _projection);
		Graphics2D.Instance.SetColorThreshold (0, 0, 0, 0, 1, 1, 1, 1);
		Graphics2D.Instance.SetTextureThreshold (u0, v0, u1, v1);
		Graphics2D.Instance.DrawTextureWithThreshold ();
	}

	public static void rectangle ()
	{
		GraphicsDevice.Instance.SetRasterizerState (_rasterizerState);
		GraphicsDevice.Instance.SetDepthStencilState (_depthStencilState);
		Graphics2D.Instance.SetMatrix (_world * _viewing * _projection);
		Graphics2D.Instance.DrawRectangle ();
	}

	public static void font (Font _font)
	{
		Graphics2D.Instance.SetFont (_font);
	}

	public static void color (float rgb)
	{
		Graphics2D.Instance.SetColor (new Color (rgb, rgb, rgb));
	}

	public static void color (float r, float g, float b)
	{
		Graphics2D.Instance.SetColor (new Color (r, g, b));
	}

	public static void color (float r, float g, float b, float a)
	{
		Graphics2D.Instance.SetColor (new Color (r, g, b, a));
	}

	public static void color (Color color)
	{
		Graphics2D.Instance.SetColor (color);
	}

	public static void color (ColorCode code)
	{
		Graphics2D.Instance.SetColor (new Color (code));
	}

	public static void write (string text, TextAlignment horizontal = TextAlignment.Left, TextAlignment vertical = TextAlignment.Top)
	{
		GraphicsDevice.Instance.SetRasterizerState (_rasterizerState);
		GraphicsDevice.Instance.SetDepthStencilState (_depthStencilState);
		Graphics2D.Instance.SetMatrix (_world * _viewing * _projection);
		Graphics2D.Instance.DrawText (text, horizontal, vertical);
	}

	public static void blend (BlendState state)
	{
		GraphicsDevice.Instance.SetBlendState (state);
	}

	public static void addressing (SamplerState state)
	{
		Graphics2D.Instance.SetAddreessMode (state);
	}
}
