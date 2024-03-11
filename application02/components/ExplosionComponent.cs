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
    static Texture2DArray Texture = new Texture2DArray();
    static Matrix4x4[] InstanceWVPs = new Matrix4x4[InstanceCount];
    static Vector4[] InstanceAlphas = new Vector4[InstanceCount];
    static Vector4[] InstanceTexIndices = new Vector4[InstanceCount];
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector2> VertexTextureCoords = new VertexBuffer<Vector2>();

    const int TextureCount = 64;
    const float CountSpeed = 0.5f * 1.0f / TextureCount;
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

        Texture.Create("res/texture/explos.png", 32, 32, Accessibility.None);

        VertexPositions.Create(new Vector3[]
        {
            new Vector3(-0.5f, +0.5f, 0),
            new Vector3(+0.5f, +0.5f, 0),
            new Vector3(-0.5f, -0.5f, 0),
            new Vector3(+0.5f, -0.5f, 0),
        }, Accessibility.None);

        VertexTextureCoords.Create(new Vector2[]
        {
            new Vector2(0, 0),
            new Vector2(1, 0),
            new Vector2(0, 1),
            new Vector2(1, 1),
        }, Accessibility.None);
    }

    public ExplosionComponent()
    {
        for (int i = 0; i < InstanceCount; i++)
        {
            this.Instances[i] = new Instance();
        }

        foreach (var instance in this.Instances)
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
        this.Time += CountSpeed;

        if (1.0f <= this.Time)
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
        var viewing = this.ViewingMatrix;
        var projection = this.ProjectionMatrix;

        for (int i = 0; i < InstanceCount; i++)
        {
            var instance = this.Instances[i];

            var world = new Matrix4x3().Identity();
            world.Translate((position + instance.Position) * viewing);
            world.Scale(instance.Scale);

            InstanceWVPs[i] = world * projection;
            InstanceAlphas[i] = new Vector4((1.0f - this.Time) * 0.1f, 0, 0, 0);
            InstanceTexIndices[i] = new Vector4(this.Time * TextureCount, 0, 0, 0);
        }

        device.SetVertexBuffer(VertexPositions, 0);
        device.SetVertexBuffer(VertexTextureCoords, 1);
        VertexShader.SetConstantBuffer(InstanceWVPs, 0);
        VertexShader.SetConstantBuffer(InstanceAlphas, 1);
        VertexShader.SetConstantBuffer(InstanceTexIndices, 2);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTextureArray(Texture, 0);

        device.DrawInstanced(4, InstanceCount);
    }
}
