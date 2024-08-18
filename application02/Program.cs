using CommandLine;
using System;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
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
        [Option('m', "mode", Default = "play")]
        public string Mode { get; set; }

        [Option('w', "width", Default = 1920)]
        public int WindowWidth { get; set; }

        [Option('h', "height", Default = 1080)]
        public int WindowHeight { get; set; }

        [Option('f', "fullscreen")]
        public bool FullScreen { get; set; }

        [Option("enemy_count", Default = 0)]
        public int EnemyCount { get; set; }

        [Option("friend_count", Default = 0)]
        public int FriendCount { get; set; }

        [Option("debug")]
        public bool Debug { get; set; }

        [Option("random_seed", Default = 12345UL)]
        public ulong RandomSeed { get; set; }
    }

    private static Arguments ParseArgs()
    {
        Arguments args = Parser.Default.ParseArguments<Arguments>(Environment.GetCommandLineArgs()).Value;
        Debug.Assert(new string[] { "play", "demo", "training", "evaluation" }.Contains(args.Mode));
        return args;
    }

    static void Main()
    {
        var args = ParseArgs();

        Window window = new Window();
        window.Create(args.WindowWidth, args.WindowHeight);

        if (true)
            window.EnableBackgroundRunning = true;
        else
            window.EnableBackgroundRunning = false;

        GraphicsDevice.Instance.Create(window, args.FullScreen);
        SoundDevice.Instance.Create(window.Handle);

        GameSystemMonitor monitor = null;
        if (args.Debug)
        {
            monitor = GameSystemMonitor.Execute();
        }

        window.Updated += () =>
        {
            if (args.Mode == "training" || args.Mode == "evaluation")
            {
                if (ResetSceneSignal)
                {
                    Scene.ResetScene(args);
                    ResetSceneSignal = false;
                }
            }
            else
            {
                bool flag = false;
                flag |= Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("player"))) is null;
                flag |= (0 < args.EnemyCount) && (Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("enemy"))) is null);
                if (flag)
                {
                    Scene.ResetScene(args);
                }
            }

            bool rendering, vsync;
            if (args.Mode == "training")
            {
                rendering = GameScript.pressed(Keyboard.KeyCode.F11) | GameScript.pressed(Keyboard.KeyCode.F12);
                vsync = GameScript.pressed(Keyboard.KeyCode.F11);
            }
            else
            {
                rendering = true;
                vsync = true;
            }
            GameScript.Update();
            Entity.BroadcastMessage(GameScript.UpdateMessage);

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
            if (args.Debug)
            {
                GameSystemMonitor.Shutdown(monitor);
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
