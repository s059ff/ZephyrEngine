using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static Script;

public static class LoadingView
{
    static float VisibleProgressRate;

    public static void Draw(LoadingTask task)
    {
        VisibleProgressRate = clamp(close(VisibleProgressRate, task.ProgressRate, 0.02f), 0, task.ProgressRate);

        var device = GraphicsDevice.Instance;
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
}
