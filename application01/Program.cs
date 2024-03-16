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
        var window = new Window();
        window.Create("Graphics + Collision Test", 1024, 768);

        var device = GraphicsDevice.Instance;
        device.Create(window);

        var context = GraphicsDeviceContext.Instance;

        DepthMap.CreateDepthMap(1024, 1024);

        window.Updated += () =>
        {
            update();

            Entity.BroadcastMessage(UpdateMessage);

            context.SetRenderTargetAndDepthStencil(null, DepthMap);
            context.SetViewport(1024, 1024);
            context.Clear(new Color(0, 0, 0, 0));
            Entity.BroadcastMessage(RenderDepthMapMessage);

            context.ResetRenderTargetAndDepthStencil();
            context.SetViewport(1024, 768);
            context.Clear(ColorCode.Black);
            Entity.BroadcastMessage(RenderMessage);
            Entity.BroadcastMessage(TranslucentRenderMessage);
            context.Present();

            if (pressed(Keyboard.KeyCode.Escape))
                window.Close();

            Entity.Update();
        };

        window.Destroyed += () =>
        {
            context.UnbindAllResources();
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
