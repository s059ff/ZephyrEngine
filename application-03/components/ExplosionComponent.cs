using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class ExplosionComponent : CustomEntityComponent
{
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();
    static Texture2D[] Textures = new Texture2D[TextureCount];
    static GraphicsModel GraphicsModel = new GraphicsModel();
    static Matrix4x4[] InstanceWVPs = new Matrix4x4[InstanceCount];
    static Color[] InstanceColors = new Color[InstanceCount];

    const int TextureCount = 64;
    const float CountSpeed = 0.0075f;
    const int InstanceCount = 64;

    class Instance
    {
        public Vector3 Position;
        public float Scale;
    }

    float Time = 0;
    Instance[] Instances = new Instance[InstanceCount];

    static ExplosionComponent()
    {
        VertexShader.CreateFromFile("res/shader/ExplosionVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/ExplosionPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        for (int i = 0; i < TextureCount; i++)
        {
            Textures[i] = new Texture2D();
            Textures[i].Create(string.Format("res/texture/explos/explos ({0}).png", i + 1), Accessibility.None);
        }

        GraphicsModel.CreateBillBoard();
    }

    public ExplosionComponent()
    {
        for (int i = 0; i < InstanceCount; i++)
        {
            Instances[i] = new Instance();
        }

        foreach (var instance in Instances)
        {
            instance.Position = new Vector3(normal(0, 5), normal(0, 5), normal(0, 5));
            instance.Scale = 50;
        }
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            case TranslucentRenderMessage:
                this.TransparentRender();
                break;

            default:
                break;
        }
    }

    void Update()
    {
        Time += CountSpeed;

        if (1.0f <= Time)
        {
            Entity.Kill(this.Owner);
        }
    }

    void TransparentRender()
    {
        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        var position = this.Owner.Get<TransformComponent>().Position;
        var viewing = ViewingMatrix;
        var projection = ProjectionMatrix;

        for (int i = 0; i < InstanceCount; i++)
        {
            var instance = Instances[i];

            var world = new Matrix4x3().Identity();
            world.Translate((position + instance.Position) * viewing);
            world.Scale(instance.Scale);

            InstanceWVPs[i] = world * projection;
            var a = (1.0f - Time) * 0.1f;
            InstanceColors[i] = new Color(a, a, a, a);
        }

        device.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
        device.SetVertexBuffer(GraphicsModel.VertexTextureCoords, 1);
        VertexShader.SetConstantBuffer(InstanceWVPs, 0);
        VertexShader.SetConstantBuffer(InstanceColors, 1);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(Textures[(int)(Time * TextureCount)], 0);

        device.DrawInstanced(4, InstanceCount);
    }
}
