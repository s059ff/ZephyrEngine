//#define DebugMode

using System;
using System.Runtime.CompilerServices;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Sound;
using static EngineScript;
using static GameScript;

class Program
{
    public static bool ResetSceneSignal = false;

    static void Main()
    {
        var args = new
        {
            Mode = Environment.GetCommandLineArgs().Length > 1 ? Environment.GetCommandLineArgs()[1].ToLower() : null,
        };
        assert(args.Mode == null || args.Mode == "training" || args.Mode == "evaluation");

        Window window = new Window();
        window.Create("application02", DisplayWidth, DisplayHeight);

        if (args.Mode == "training" || args.Mode == "evaluation")
            window.EnableBackgroundRunning = true;
        else
            window.EnableBackgroundRunning = false;

        GraphicsDevice.Instance.Create(window, FullScreen);
        SoundDevice.Instance.Create(window.Handle);

#if DebugMode
        var runner = CommandRunner.Execute();
        var monitor = GameSystemMonitor.Execute();
#endif

        window.Updated += () =>
        {
            if (args.Mode == "training" || args.Mode == "evaluation")
            {
                if (ResetSceneSignal)
                {
                    Scene.ResetScene(args.Mode);
                    ResetSceneSignal = false;
                }
            }
            else
            {
                bool flag = false;
                flag |= Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("player"))) == null;
                //flag |= Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("enemy"))) == null;
                if (flag)
                {
                    Scene.ResetScene(args.Mode);
                }
            }

            bool rendering, vsync;
            if (args.Mode == "training")
            {
                rendering = pressed(Keyboard.KeyCode.F11) | pressed(Keyboard.KeyCode.F12);
                vsync = pressed(Keyboard.KeyCode.F11);
            }
            else
            {
                rendering = true;
                vsync = true;
            }
            EngineScript.update();
            GameScript.update();
            Entity.BroadcastMessage(UpdateMessage);

            if (rendering)
            {
                GraphicsDeviceContext.Instance.Clear(ColorCode.Black);
                Entity.BroadcastMessage(RenderMessage);
                Entity.BroadcastMessage(TranslucentRenderMessage);
                Entity.BroadcastMessage(DrawMessage);
                GraphicsDeviceContext.Instance.Present(vsync ? 1 : 0);
            }

            Entity.Update();
        };

        try
        {
            EngineScript.initialize();
            GameScript.initialize();

            Scene.ResetScene(args.Mode);

            window.Start();
        }
        finally
        {
#if DebugMode
            GameSystemMonitor.Shutdown(monitor);
            CommandRunner.Shutdown(runner);
#endif

            Entity.Clear();

            EngineScript.finalize();
            GameScript.finalize();

            GraphicsDeviceContext.Instance.Dispose();
            GraphicsDevice.Instance.Dispose();
            SoundDevice.Instance.Dispose();
        }
    }
}
