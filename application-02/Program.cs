using System;
using System.IO;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Scripting;
using ZephyrSharp.Sound;
using ZephyrTools.CommandRunner;
using ZephyrTools.GameSystemMonitor;
using static Script;

class Program
{
    const bool ShowDebugInfo = true;

    static CommandRunner runner = null;

    static GameSystemMonitor monitor = null;

    static void Main(string[] args)
    {
#if DEBUG
        chdir("../../../");
#endif

        Window window = new Window();
        window.Create("application-02", (int)DisplayWidth, (int)DisplayHeight);

        GraphicsDevice.Instance.Create(window, FullScreen);

        SoundDevice.Instance.Create(window.Handle);

        if (ShowDebugInfo)
        {
            runner = CommandRunner.Execute();
            monitor = GameSystemMonitor.Execute();
        }

        foreach (var file in Directory.GetFiles("res/mission/", "*.cs"))
        {
            var asm = ScriptCompiler.CompileAssemblyFromFile(new ScriptCompilerParameters()
            {
                BaseClassName = "Script",
                BatchScriptStyle = false,
                ClassName = "Mission",
                GenerateExecutable = false,
                GenerateInMemory = true,
                PythonScopeStyle = false,
            }, file);
            Missions.MissionAssemblies.Add(Path.GetFileNameWithoutExtension(file), asm);
        }

        window.Updated += () =>
        {
            update();

            GraphicsDevice.Instance.Clear(ColorCode.Black);
#if true
            LoadingTask loadingTask = SceneManager.TryTransitScene();

            if (loadingTask.Finished)
            {
                Entity.BroadcastMessage(UpdateMessage);

                Entity.BroadcastMessage(RenderMessage);
                Entity.BroadcastMessage(TranslucentRenderMessage);
                Entity.BroadcastMessage(DrawMessage);
            }
            else
            {
                LoadingView.Draw(loadingTask);
            }
#endif
            GraphicsDevice.Instance.Present();

            if (pressed(KeyCode.Escape))
                window.Close();

            Entity.Update();
        };

        try
        {
            initialize();

            //SceneManager.FookScene(new MainScene());
            SceneManager.FookScene(new TitleScene());
            //SceneManager.FookScene(new MissionSelectScene());

            window.Start();
        }
        finally
        {
            Entity.Clear();

            ResourceManager.CleanUp();

            GC.Collect();

            finalize();

            GraphicsDevice.Instance.Dispose();
            SoundDevice.Instance.Dispose();

            if (ShowDebugInfo)
            {
                GameSystemMonitor.Shutdown(monitor);
                CommandRunner.Shutdown(runner);
            }
        }
    }
}
