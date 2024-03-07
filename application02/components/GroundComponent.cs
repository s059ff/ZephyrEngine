using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class GroundComponent : CustomEntityComponent
{
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();

    GraphicsModel GraphicsModel = new GraphicsModel();
    Texture2D Texture = new Texture2D();
    Texture2D Texture2 = new Texture2D();
    Texture2D MixingRateTexture = new Texture2D();
    float[,] Heights;

    static GroundComponent()
    {
        VertexShader.CreateFromFile("res/shader/GroundVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/GroundPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
                new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
                new VertexElement("NORMAL", 0, Format.Float3, 1, 0, VertexElement.Classification.VertexData, 0),
                new VertexElement("TEXCOORD", 0, Format.Float2, 2, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);
    }

    public GroundComponent()
    {
        int Split = 512;

        Texture.Create("res/texture/ground.png", Accessibility.None);
        Texture2.Create("res/texture/sand.png", Accessibility.None);
        MixingRateTexture.Create("res/texture/mixing_rate.png", Accessibility.None);
        Heights = heightmap("res/texture/heightmap.png", Split, Split, 0, 0.025f);
        GraphicsModel.CreateMeshMap(Heights);
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        var scale = Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength;
        this.Owner.Get<TransformComponent>().Matrix.RotateX(deg2rad(90));
        this.Owner.Get<TransformComponent>().Matrix.Scale(scale);

        this.Owner.Get<CollisionComponent>().Object = new CurvedSurfaceCollisionObject(new CurvedSurface() { Heights = Heights });
        this.Owner.Get<CollisionComponent>().Group = 4;
        this.Owner.Get<CollisionComponent>().OtherGroups = 0;
    }

    protected override void OnDestroy()
    {
        this.GraphicsModel.Dispose();
        this.Texture.Dispose();
        this.Texture2.Dispose();
        this.MixingRateTexture.Dispose();
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case RenderMessage:
                this.Render();
                break;

            default:
                break;
        }
    }

    private void Render()
    {
        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(NoBlend);
        device.SetRasterizerState(CullingOn);
        device.SetDepthStencilState(ZTestOn);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(GraphicsModel.Topology);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        device.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
        device.SetVertexBuffer(GraphicsModel.VertexNormals, 1);
        device.SetVertexBuffer(GraphicsModel.VertexTextureCoords, 2);
        device.SetIndexBuffer(GraphicsModel.VertexIndices);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(Texture, 0);
        PixelShader.SetTexture(Texture2, 1);
        PixelShader.SetTexture(MixingRateTexture, 2);
        VertexShader.SetConstantBuffer(WVPMatrix, 0);
        PixelShader.SetConstantBuffer(WorldMatrix, 0);
        PixelShader.SetConstantBuffer(new Vector4(Entity.Find("light").Get<TransformComponent>().Forward, 0), 1);

        device.DrawIndexed(GraphicsModel.VertexIndices.Count);
    }
}
