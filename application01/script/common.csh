// ---------- For Basic C# library ----------
#using "System.dll"

// ---------- For Xepher Game Engine library ----------
#using "ZephyrSharp.dll"
#using "ZephyrSharp.Graphics.dll"
#using "ZephyrSharp.Graphics.DX11.dll"
#using "ZephyrSharp.Input.dll"
#using "ZephyrSharp.GameSystem.dll"
#using "ZephyrSharp.GameSystem.Components.dll"
#using "ZephyrSharp.Linalg.dll"
#using "ZephyrSharp.Scripting.dll"
#using "ZephyrSharp.Sound.dll"

// ---------- Graphics Macros ----------
#define WHITE ColorCode.White
#define SNOW ColorCode.Snow
#define GHOSTWHITE ColorCode.GhostWhite
#define MINTCREAM ColorCode.MintCream
#define AZURE ColorCode.Azure
#define IVORY ColorCode.Ivory
#define FLORALWHITE ColorCode.FloralWhite
#define ALICEBLUE ColorCode.AliceBlue
#define LAVENDERBLUSH ColorCode.LavenderBlush
#define SEASHELL ColorCode.SeaShell
#define WHITESMOKE ColorCode.WhiteSmoke
#define HONEYDEW ColorCode.Honeydew
#define LIGHTCYAN ColorCode.LightCyan
#define LIGHTYELLOW ColorCode.LightYellow
#define OLDLACE ColorCode.OldLace
#define CORNSILK ColorCode.Cornsilk
#define LINEN ColorCode.Linen
#define LEMONCHIFFON ColorCode.LemonChiffon
#define LIGHTGOLDENRODYELLOW ColorCode.LightGoldenrodYellow
#define LAVENDER ColorCode.Lavender
#define BEIGE ColorCode.Beige
#define MISTYROSE ColorCode.MistyRose
#define PAPAYAWHIP ColorCode.PapayaWhip
#define ANTIQUEWHITE ColorCode.AntiqueWhite
#define BLANCHEDALMOND ColorCode.BlanchedAlmond
#define BISQUE ColorCode.Bisque
#define MOCCASIN ColorCode.Moccasin
#define GAINSBORO ColorCode.Gainsboro
#define PEACHPUFF ColorCode.PeachPuff
#define PALETURQUOISE ColorCode.PaleTurquoise
#define NAVAJOWHITE ColorCode.NavajoWhite
#define PINK ColorCode.Pink
#define WHEAT ColorCode.Wheat
#define PALEGOLDENROD ColorCode.PaleGoldenrod
#define LIGHTGRAY ColorCode.LightGray
#define LIGHTPINK ColorCode.LightPink
#define POWDERBLUE ColorCode.PowderBlue
#define THISTLE ColorCode.Thistle
#define LIGHTBLUE ColorCode.LightBlue
#define KHAKI ColorCode.Khaki
#define VIOLET ColorCode.Violet
#define PLUM ColorCode.Plum
#define AQUAMARINE ColorCode.Aquamarine
#define LIGHTSTEELBLUE ColorCode.LightSteelBlue
#define LIGHTSKYBLUE ColorCode.LightSkyBlue
#define SILVER ColorCode.Silver
#define SKYBLUE ColorCode.SkyBlue
#define PALEGREEN ColorCode.PaleGreen
#define ORCHID ColorCode.Orchid
#define BURLYWOOD ColorCode.BurlyWood
#define HOTPINK ColorCode.HotPink
#define LIGHTSALMON ColorCode.LightSalmon
#define TAN ColorCode.Tan
#define LIGHTGREEN ColorCode.LightGreen
#define CYAN ColorCode.Cyan
#define MAGENTA ColorCode.Magenta
#define FUCHSIA ColorCode.Fuchsia
#define AQUA ColorCode.Aqua
#define YELLOW ColorCode.Yellow
#define DARKGRAY ColorCode.DarkGray
#define DARKSALMON ColorCode.DarkSalmon
#define SANDYBROWN ColorCode.SandyBrown
#define LIGHTCORAL ColorCode.LightCoral
#define TURQUOISE ColorCode.Turquoise
#define SALMON ColorCode.Salmon
#define CORNFLOWERBLUE ColorCode.CornflowerBlue
#define MEDIUMTURQUOISE ColorCode.MediumTurquoise
#define MEDIUMORCHID ColorCode.MediumOrchid
#define DARKKHAKI ColorCode.DarkKhaki
#define MEDIUMPURPLE ColorCode.MediumPurple
#define PALEVIOLETRED ColorCode.PaleVioletRed
#define MEDIUMAQUAMARINE ColorCode.MediumAquamarine
#define GREENYELLOW ColorCode.GreenYellow
#define ROSYBROWN ColorCode.RosyBrown
#define GOLD ColorCode.Gold
#define DARKSEAGREEN ColorCode.DarkSeaGreen
#define MEDIUMSLATEBLUE ColorCode.MediumSlateBlue
#define CORAL ColorCode.Coral
#define DEEPSKYBLUE ColorCode.DeepSkyBlue
#define DODGERBLUE ColorCode.DodgerBlue
#define TOMATO ColorCode.Tomato
#define DEEPPINK ColorCode.DeepPink
#define ORANGE ColorCode.Orange
#define DARKTURQUOISE ColorCode.DarkTurquoise
#define GOLDENROD ColorCode.Goldenrod
#define CADETBLUE ColorCode.CadetBlue
#define YELLOWGREEN ColorCode.YellowGreen
#define LIGHTSLATEGRAY ColorCode.LightSlateGray
#define BLUEVIOLET ColorCode.BlueViolet
#define DARKORCHID ColorCode.DarkOrchid
#define MEDIUMSPRINGGREEN ColorCode.MediumSpringGreen
#define SLATEBLUE ColorCode.SlateBlue
#define PERU ColorCode.Peru
#define ROYALBLUE ColorCode.RoyalBlue
#define DARKORANGE ColorCode.DarkOrange
#define INDIANRED ColorCode.IndianRed
#define GRAY ColorCode.Gray
#define SLATEGRAY ColorCode.SlateGray
#define CHARTREUSE ColorCode.Chartreuse
#define SPRINGGREEN ColorCode.SpringGreen
#define LIGHTSEAGREEN ColorCode.LightSeaGreen
#define STEELBLUE ColorCode.SteelBlue
#define LAWNGREEN ColorCode.LawnGreen
#define DARKVIOLET ColorCode.DarkViolet
#define MEDIUMVIOLETRED ColorCode.MediumVioletRed
#define MEDIUMSEAGREEN ColorCode.MediumSeaGreen
#define CHOCOLATE ColorCode.Chocolate
#define DARKGOLDENROD ColorCode.DarkGoldenrod
#define ORANGERED ColorCode.OrangeRed
#define DIMGRAY ColorCode.DimGray
#define LIMEGREEN ColorCode.LimeGreen
#define CRIMSON ColorCode.Crimson
#define SIENNA ColorCode.Sienna
#define OLIVEDRAB ColorCode.OliveDrab
#define DARKMAGENTA ColorCode.DarkMagenta
#define DARKCYAN ColorCode.DarkCyan
#define SEAGREEN ColorCode.SeaGreen
#define DARKSLATEBLUE ColorCode.DarkSlateBlue
#define TEAL ColorCode.Teal
#define OLIVE ColorCode.Olive
#define PURPLE ColorCode.Purple
#define BLUE ColorCode.Blue
#define LIME ColorCode.Lime
#define RED ColorCode.Red
#define BROWN ColorCode.Brown
#define FIREBRICK ColorCode.Firebrick
#define DARKOLIVEGREEN ColorCode.DarkOliveGreen
#define SADDLEBROWN ColorCode.SaddleBrown
#define FORESTGREEN ColorCode.ForestGreen
#define DARKSLATEGRAY ColorCode.DarkSlateGray
#define MEDIUMBLUE ColorCode.MediumBlue
#define INDIGO ColorCode.Indigo
#define MIDNIGHTBLUE ColorCode.MidnightBlue
#define DARKBLUE ColorCode.DarkBlue
#define DARKRED ColorCode.DarkRed
#define MAROON ColorCode.Maroon
#define NAVY ColorCode.Navy
#define GREEN ColorCode.Green
#define DARKGREEN ColorCode.DarkGreen
#define BLACK ColorCode.Black
#define TRANSPARENT ColorCode.Transparent

#define NOBLEND 0
#define ALPHABLEND 1
#define ADDITION 2
#define SUBTRACTION 3
#define HALFADDITION 4
#define MULTIPLICATION 5
#define REVERSE 6

#define WRAP AddressingMode.Wrap
#define MIRROR AddressingMode.Mirror

#define NOACCESS Accessibility.None
#define READONLY Accessibility.ReadOnly
#define WRITEONLY Accessibility.WriteOnly
#define READWRITE Accessibility.ReadWrite
#define DYNAMICWRITEONLY Accessibility.DynamicWriteOnly

// ---------- Input Macros ----------
#define CENTER TextAlignment.Center
#define TOP TextAlignment.Top
#define BOTTOM TextAlignment.Bottom
#define LEFT TextAlignment.Left
#define RIGHT TextAlignment.Right

#define RELEASED ButtonState.Released
#define PRESSED ButtonState.Pressed
#define NOWRELEASED ButtonState.NowReleased
#define NOWPRESSED ButtonState.NowPressed

#define ENTER KeyCode.Enter
#define SPACE KeyCode.Space
#define ESC KeyCode.Escape

// ---------- Using Default Namespace ----------
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Timers;
using System.Text.RegularExpressions;

// ---------- Using GameEngine Namespace ----------
using ZephyrSharp;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using ZephyrSharp.Scripting;
using ZephyrSharp.Sound;

// ---------- Class Alias ----------
using Integer = ZephyrSharp.ValueWrapper<int>;
using Float = ZephyrSharp.ValueWrapper<float>;
using Double = ZephyrSharp.ValueWrapper<double>;
using Texture = ZephyrSharp.Graphics.Texture2D;
