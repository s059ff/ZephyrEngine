using System;
using System.IO;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using ZephyrSharp.Linalg;
using ZephyrSharp.Scripting;
using ZephyrSharp.Sound;
using ZephyrTools.CommandRunner;
using ZephyrTools.GameSystemMonitor;
using static EngineScript;
using static GameScript;

class Program
{
    static float VisibleProgressRate;

    static void DrawLoadingStatus(AbstractScene scene)
    {
        VisibleProgressRate = clamp(close(VisibleProgressRate, scene.LoadingProgress, 0.02f), 0, scene.LoadingProgress);

        var device = GraphicsDeviceContext.Instance;
        var device2d = Graphics2D.Instance;
        var proj = new Matrix4x4().Orthogonal(DisplayAspect * 2, 2, 0, 1);

        device.SetBlendState(Addition);
        device.SetDepthStencilState(ZTestOff);
        device.SetRasterizerState(CullingOff);

        device2d.SetColor(ColorCode.White);
        device2d.SetMatrix(new Matrix4x3().Identity().Translate(0.5f, -0.75f).Scale(0.06f) * proj);
        device2d.DrawText("Now Loading" + "...".Substring(0, (frame / 30) % 3), TextAlignment.Left, TextAlignment.Center);

        device2d.SetColor(ColorCode.Gray);
        device2d.SetMatrix(new Matrix4x3().Identity().Translate(0.5f, -0.75f).Translate(0, -0.05f).Scale(0.5f, 0.02f, 1) * proj);
        device2d.SetVertexPositions(0, 0.5f, 1, -0.5f);
        device2d.DrawRectangleWithDynamical();

        device2d.SetColor(ColorCode.White);
        device2d.SetMatrix(new Matrix4x3().Identity().Translate(0.5f, -0.75f).Translate(0, -0.05f).Scale(0.5f, 0.02f, 1) * proj);
        device2d.SetVertexPositions(0, 0.5f, VisibleProgressRate, -0.5f);
        device2d.DrawRectangleWithDynamical();

        device2d.SetMatrix(new Matrix4x3().Identity().Translate(1.05f, -0.75f).Translate(0, -0.05f).Scale(0.04f) * proj);
        device2d.DrawText(VisibleProgressRate.ToString("P0"), TextAlignment.Left, TextAlignment.Center);
    }

    public static SceneManager SceneManager = new SceneManager();

    static void Main(string[] args)
    {
        Window window = new Window();
        window.Create("application-03", (int)DisplayWidth, (int)DisplayHeight);

        GraphicsDevice.Instance.Create(window, FullScreen);
        SoundDevice.Instance.Create(window.Handle);

#if DEBUG
        var runner = CommandRunner.Execute();
        var monitor = GameSystemMonitor.Execute();
#endif

        foreach (var file in Directory.GetFiles("res/mission/", "*.cs"))
        {
            var assembly = ScriptCompiler.CompileAssemblyFromFile(new ScriptCompilerParameters()
            {
                BaseClassName = "GameScript",
                BatchScriptStyle = false,
                ClassName = "Mission",
                GenerateExecutable = false,
                GenerateInMemory = true,
                PythonScopeStyle = false,
            }, file);
            Missions.MissionAssemblies.Add(Path.GetFileNameWithoutExtension(file), assembly);
        }

        SceneManager.SetNextScene(new TitleScene());

        window.Updated += () =>
        {
            EngineScript.update();
            GameScript.update();

            GraphicsDeviceContext.Instance.Clear(ColorCode.Black);
            if (SceneManager.Running)
            {
                DrawLoadingStatus(SceneManager.Scene);
            }
            else
            {
                if (SceneManager.Scene != null)
                {
                    if (!SceneManager.Running)
                        SceneManager.NextScene();
                }
                else
                {
                    Entity.BroadcastMessage(UpdateMessage);
                    Entity.BroadcastMessage(RenderMessage);
                    Entity.BroadcastMessage(TranslucentRenderMessage);
                    Entity.BroadcastMessage(DrawMessage);
                }
            }
            GraphicsDeviceContext.Instance.Present();

            if (pressed(KeyCode.Escape))
                window.Close();

            Entity.Update();
        };

        try
        {
            EngineScript.initialize();
            GameScript.initialize();

            window.Start();
        }
        finally
        {
#if DEBUG
            GameSystemMonitor.Shutdown(monitor);
            CommandRunner.Shutdown(runner);
#endif

            Entity.Clear();

            ResourceManager.CleanUp();

            EngineScript.finalize();
            GameScript.finalize();

            GraphicsDeviceContext.Instance.Dispose();
            GraphicsDevice.Instance.Dispose();
            SoundDevice.Instance.Dispose();
        }
    }
}
