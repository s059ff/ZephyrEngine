using System.Linq;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class GunBulletSparkComponent : CustomEntityComponent
{
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector4> VertexColors = new VertexBuffer<Vector4>();
    static InstanceBuffer<Matrix4x4> InstanceWVPs = new InstanceBuffer<Matrix4x4>();
    static InstanceBuffer<float> InstanceAlphas = new InstanceBuffer<float>();

    const int InstanceCount = 16;

    struct InstanceData
    {
        public Quaternion rotation;
        public float scale;
    }
    InstanceData[] instances;

    static GunBulletSparkComponent()
    {
        VertexShader.CreateFromFile("res/shader/GunBulletSparkVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/GunBulletSparkPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("COLOR", 0, Format.Float4, 1, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("ALPHA", 0, Format.Float1, 2, 0, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 0, Format.Float4, 3, sizeof(float) * 0, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 1, Format.Float4, 3, sizeof(float) * 4, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 2, Format.Float4, 3, sizeof(float) * 8, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 3, Format.Float4, 3, sizeof(float) * 12, VertexElement.Classification.InstanceData, 1),
        }, VertexShader);

        VertexPositions.Create(
            new Vector3[]
            {
                new Vector3(1.0f, 0.0f, 0.0f),
                new Vector3(0.0f, 0.0f, 0.0f),
            },
            Accessibility.None
        );
        VertexColors.Create(
            new Vector4[]
            {
                new Vector4(1.0f, 1.0f, 0.0f, 1.0f),
                new Vector4(0.0f, 0.0f, 0.0f, 0.0f),
            },
            Accessibility.None
        );

        InstanceAlphas.Create(InstanceCount, Accessibility.DynamicWriteOnly);
        InstanceWVPs.Create(InstanceCount, Accessibility.DynamicWriteOnly);
    }

    public GunBulletSparkComponent()
    {
        this.instances = new InstanceData[InstanceCount];
        foreach (var i in Enumerable.Range(0, InstanceCount))
        {
            Vector3 axis = new Vector3(normal(0, 1), normal(0, 1), normal(0, 1)).Normalize();
            float theta = uniform(0, PI2);
            this.instances[i].rotation = new Quaternion(axis, theta);
            this.instances[i].scale = normal(1.0f, 0.5f);
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
                this.Render();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
    }

    private void Render()
    {
        InstanceAlphas.Lock(Accessibility.DynamicWriteOnly);
        {
            float time = this.Owner.Get<LimitedLifeTimeComponent>().CountTime;
            foreach (var i in Enumerable.Range(0, InstanceCount))
            {
                InstanceAlphas.Write(i, 1.0f - time);
            }
        }
        InstanceAlphas.Unlock();

        InstanceWVPs.Lock(Accessibility.DynamicWriteOnly);
        {
            const float c = 100.0f;
            float time = this.Owner.Get<LimitedLifeTimeComponent>().CountTime;
            foreach (var i in Enumerable.Range(0, InstanceCount))
            {
                var rotation = this.instances[i].rotation;
                var scale = this.instances[i].scale;
                Matrix4x3 world = new Matrix4x3()
                    .Identity()
                    .Translate(this.Transform.Position)
                    .Transform(new Matrix4x3(rotation))
                    .Translate(new Vector3(c * time, 0, 0))
                    .Scale(scale)
                    ;
                InstanceWVPs.Write(i, world * this.ViewingMatrix * this.ProjectionMatrix);
            }
        }
        InstanceWVPs.Unlock();

        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.LineList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);
        device.SetVertexBuffer(VertexPositions, 0);
        device.SetVertexBuffer(VertexColors, 1);
        device.SetInstanceBuffer(InstanceAlphas, 2);
        device.SetInstanceBuffer(InstanceWVPs, 3);
        device.DrawInstanced(2, InstanceCount);
    }
}
