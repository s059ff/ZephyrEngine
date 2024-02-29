using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class GunFlushComponent : CustomEntityComponent
{
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static GraphicsModel GraphicsModel = new GraphicsModel();

    static GunFlushComponent()
    {
        VertexShader.CreateFromFile("res/shader/GunFlushVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/GunFlushPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0),
        }, VertexShader);

        GraphicsModel.CreateBillBoard();
        GraphicsModel.Texture = new Texture2D();
        GraphicsModel.Texture.Create("res/texture/flash.dds", Accessibility.None);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case TranslucentRenderMessage:
                this.Render();
                break;

            default:
                break;
        }
    }

    private void Render()
    {
        var world = new Matrix4x3().Identity();
        world.Translate(Transform.Position * ViewingMatrix);
        world.Scale(0.5f * sin(this.Owner.Get<LimitedLifeTimeComponent>().CountTime) * PI);

        VertexShader.SetConstantBuffer(world * ProjectionMatrix, 0);
        PixelShader.SetTexture(GraphicsModel.Texture, 0);
        PixelShader.SetConstantBuffer(new Color(1, 1, 1, 1 - this.Owner.Get<LimitedLifeTimeComponent>().CountTime), 0);

        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(GraphicsModel.Topology);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);
        device.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
        device.SetVertexBuffer(GraphicsModel.VertexTextureCoords, 1);
        device.Draw(4);
    }
}
