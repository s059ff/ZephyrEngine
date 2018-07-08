using System;
using ZephyrSharp;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Input;
using static Script;

class Program
{
    public static Texture2D DepthMap = new Texture2D();

    public static ResourceManager ResourceManager = new ResourceManager();

    static void Main(string[] args)
    {
#if DEBUG
        chdir("../../../");
#endif

        var window = new Window();
        window.Create("Graphics + Collision Test", 1024, 768);

        var device = GraphicsDevice.Instance;
        device.Create(window);

        DepthMap.CreateDepthMap(1024, 1024);

        window.Updated += () =>
        {
            update();

            Entity.BroadcastMessage(UpdateMessage);

            device.SetRenderTargetAndDepthStencil(null, DepthMap);
            device.SetViewport(1024, 1024);
            device.Clear(new Color(0, 0, 0, 0));
            Entity.BroadcastMessage(RenderDepthMapMessage);

            device.ResetRenderTargetAndDepthStencil();
            device.SetViewport(1024, 768);
            device.Clear(ColorCode.Black);
            Entity.BroadcastMessage(RenderMessage);
            Entity.BroadcastMessage(TranslucentRenderMessage);
            device.Present();

            if (pressed(KeyCode.Escape))
                window.Close();

            Entity.Update();
        };

        window.Destroyed += () =>
        {
            device.UnbindAllResources();
            Entity.Clear();
            DepthMap.Dispose();
            ResourceManager.CleanUp();
            finalize();
            GC.Collect();
            device.Dispose();
        };

        try
        {
            initialize();

            Scene.MakeScene();

            window.Start();
        }
        finally
        {
            window.Dispose();
        }
    }
}
