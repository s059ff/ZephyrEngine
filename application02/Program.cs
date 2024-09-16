using CommandLine;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Globalization;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text.RegularExpressions;
using System.Threading;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Sound;
using ZephyrTools.GameSystemMonitor;

class Program
{
    public static bool ResetSceneSignal = false;

    public class Arguments
    {
        [Option("mode", Default = "play")]
        public string ExecutionMode { get; set; }

        [Option("window_size", Default = "1280x720")]
        public string WindowSize { get; set; }

        [Option("fullscreen")]
        public bool FullScreen { get; set; }

        [Option("enemy_count", Default = 8)]
        public int EnemyCount { get; set; }

        [Option("friend_count", Default = 4)]
        public int FriendCount { get; set; }

        [Option("random_seed", Default = 12345UL)]
        public ulong RandomSeed { get; set; }

        [Option("cheat_no_attack")]
        public bool CheatNoAttack { get; set; }

        [Option("cheat_freeze_position")]
        public bool CheatFreezePosition { get; set; }
    }

    private static Arguments ParseArgs()
    {
        Arguments args = Parser.Default.ParseArguments<Arguments>(Environment.GetCommandLineArgs()).Value;
        Debug.Assert(new string[] { "play", "demo", "training", "evaluation" }.Contains(args.ExecutionMode));
        return args;
    }

    static void Main()
    {
        Thread.CurrentThread.CurrentUICulture = new CultureInfo("en-US");
        Thread.CurrentThread.CurrentCulture = new CultureInfo("en-US");

        var args = ParseArgs();
        Console.WriteLine(
            string.Join("\n",
                typeof(Arguments)
                .GetProperties()
                .Where(t => t.GetValue(args, null) != null)
                .Select(e => (key: e.Name, value: e.GetValue(args, null)?.ToString()))
                .Select(e => string.Format("{0}: {1}", e.key, e.value))
            )
        );

        Window window = new Window() { EnableBackgroundRunning = true };

        Regex pattern = new Regex(@"^(?<width>\d+)[x,](?<height>\d+)$");
        Match match = pattern.Match(args.WindowSize);
        int width = int.Parse(match.Groups["width"].Value);
        int height = int.Parse(match.Groups["height"].Value);
        window.Create(width, height);

        GraphicsDevice.Instance.Create(window, args.FullScreen);
        SoundDevice.Instance.Create(window.Handle);

        GameSystemMonitor gameSystemMonitor = null;
        //GameSystemMonitor gameSystemMonitor = GameSystemMonitor.Execute();

        bool update = true;
        bool rendering = !(args.ExecutionMode == "training");
        bool vsync = !(args.ExecutionMode == "training");

        window.Updated += () =>
        {
            if (args.ExecutionMode == "play" || args.ExecutionMode == "demo")
            {
                ResetSceneSignal = false;
                ResetSceneSignal |= Entity.Find(e => ((e.Name ?? "").StartsWith("player"))) is null;
                ResetSceneSignal |= (0 < args.EnemyCount) && (Entity.Find(e => (e.Name ?? "").StartsWith("enemy")) is null);
            }
            if (ResetSceneSignal)
            {
                Scene.ResetScene(args);
                ResetSceneSignal = false;
            }

            update ^= GameScript.nowpressed(Keyboard.KeyCode.F10);
            rendering ^= GameScript.nowpressed(Keyboard.KeyCode.F11);
            vsync ^= GameScript.nowpressed(Keyboard.KeyCode.F12);

            var display = Entity.Find("debugger")?.Get<DebugInformationDisplayComponent>();
            if (display != null)
            {
                var parameters = new Dictionary<string, object>
                {
                    {"update", update },
                    {"rendering", rendering },
                    {"vsync", vsync },
                };
                display.DebugMessages["system"] = JObject.FromObject(parameters).ToString(Formatting.Indented);
            }

            GameScript.Update();

            if (update)
            {
                Entity.BroadcastMessage(GameScript.UpdateMessage);
                Entity.BroadcastMessage(GameScript.PostUpdateMessage);
            }

            if (rendering)
            {
                GraphicsDeviceContext.Instance.Clear(ColorCode.Black);
                Entity.BroadcastMessage(GameScript.RenderMessage);
                Entity.BroadcastMessage(GameScript.TranslucentRenderMessage);
                Entity.BroadcastMessage(GameScript.DrawMessage);
                GraphicsDeviceContext.Instance.Present(vsync ? 1 : 0);
            }

            Entity.Update();
        };

        try
        {
            EngineScript.srand(args.RandomSeed);
            GameScript.Create();

            RuntimeHelpers.RunClassConstructor(typeof(MissileComponent).TypeHandle);

            Scene.ResetScene(args);

            window.Start();
        }
        finally
        {
            if (gameSystemMonitor != null)
            {
                GameSystemMonitor.Shutdown(gameSystemMonitor);
            }

            Entity.Clear();
            GC.Collect();

            GameScript.Release();

            GraphicsDeviceContext.Instance.Dispose();
            GraphicsDevice.Instance.Dispose();
            SoundDevice.Instance.Dispose();
        }
    }
}
