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
	public static Entity unit (string name, string squadronName, Vector3 pos, float angle)
	{
		Entity entity = Entity.Instantiate ();
		entity.Name = name;
		entity.Attach (new TransformComponent ());
		entity.Attach (new PhysicsComponent ());
		entity.Attach (new CollisionComponent ());
		entity.Attach (new JetComponent ());
		entity.Attach (new AircraftComponent ());
		entity.Attach (new AIComponent (Enemy));
		if (name == "player")
			entity.Attach (new PlayerComponent ());
		else
			entity.Attach (new NPCAIComponent ());
		entity.Attach (new SquadronComponent (squadronName));
		entity.Attach (new SoundComponent (JetSound));
		entity.Get<TransformComponent> ().Matrix.RotateY (angle);
		entity.Get<TransformComponent> ().Position = pos;
		entity.Get<SoundComponent> ().LoopPlay ();
		return entity;
	}
}
