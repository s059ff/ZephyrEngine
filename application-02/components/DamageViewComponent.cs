using ZephyrSharp.GameSystem;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static Script;

class DamageViewComponent : CustomEntityComponent
{
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();

    static DamageViewComponent()
    {
        VertexPositions.Create(new Vector3[]
        {
            new Vector3(-0.5f, +0.5f, 0),
            new Vector3(+0.5f, +0.5f, 0),
            new Vector3(-0.5f, -0.5f, 0),
            new Vector3(+0.5f, -0.5f, 0),
        }, Accessibility.None);

        VertexShader.CreateFromFile("res/shader/DamageViewVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/DamageViewPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0)
        }, VertexShader);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case DrawMessage:
                this.Draw();
                break;

            default:
                break;
        }
    }

    private void Draw()
    {
        var player = Entity.Find("player");
        var aircraft = player.Get<AircraftComponent>();
        float alpha = clamp(1.0f - 2.0f * aircraft.Armor, 0, 1) * 0.5f;
        if (alpha <= 0)
            return;

        GraphicsDevice device = GraphicsDevice.Instance;
        device.SetBlendState(AlphaBlend);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        device.SetVertexBuffer(VertexPositions, 0);

        Color color = new Color(1, 0, 0, alpha);
        PixelShader.SetConstantBuffer(color, 0);

        device.Draw(4);
    }
}
