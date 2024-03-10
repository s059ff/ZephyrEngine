using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class WindComponent : CustomEntityComponent
{
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector2> VertexTextureCoords = new VertexBuffer<Vector2>();
    static InstanceBuffer<float> InstanceAlphas = new InstanceBuffer<float>();
    static InstanceBuffer<Matrix4x4> InstanceWVPs = new InstanceBuffer<Matrix4x4>();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static Texture2D Texture = new Texture2D();

    const int InstanceCount = 16;

    class Instance
    {
        public float Time;
        public float CountSpeed;
        public Matrix4x3 Matrix;
    }

    Instance[] Instances = new Instance[InstanceCount];

    static WindComponent()
    {
        VertexPositions.Create(new Vector3[]
        {
            new Vector3(-0.5f, 0, +0.5f),
            new Vector3(+0.5f, 0, +0.5f),
            new Vector3(-0.5f, 0, -0.5f),
            new Vector3(+0.5f, 0, -0.5f),
        }, Accessibility.None);

        VertexTextureCoords.Create(new Vector2[]
        {
            new Vector2(0, 0),
            new Vector2(1, 0),
            new Vector2(0, 1),
            new Vector2(1, 1),
        }, Accessibility.None);

        VertexShader.CreateFromFile("res/shader/WindVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/WindPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("ALPHA", 0, Format.Float1, 2, 0, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 0, Format.Float4, 3, sizeof(float) * 0, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 1, Format.Float4, 3, sizeof(float) * 4, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 2, Format.Float4, 3, sizeof(float) * 8, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 3, Format.Float4, 3, sizeof(float) * 12, VertexElement.Classification.InstanceData, 1),
        }, VertexShader);

        Texture.Create("res/texture/wind.dds", Accessibility.None);

        InstanceAlphas.Create(InstanceCount, Accessibility.DynamicWriteOnly);
        InstanceWVPs.Create(InstanceCount, Accessibility.DynamicWriteOnly);
    }

    public WindComponent()
    {
        for (int i = 0; i < InstanceCount; i++)
        {
            this.Instances[i] = new Instance();
            this.Instances[i].CountSpeed = uniform(0.05f, 0.1f);
            this.Instances[i].Time = 1;
        }
    }

    protected override void OnAttach()
    {
        base.OnAttach();
    }

    protected override void OnDetach()
    {
        base.OnDetach();
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
                this.TranslucentRender();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        //var world = this.Owner.Get<TransformComponent>().Matrix;
        var world = new Matrix4x3().LookAt(this.Transform.Position, this.Transform.Position + this.Physics.Velocity);

        for (int i = 0; i < InstanceCount; i++)
        {
            var instance = this.Instances[i];
            instance.Time += instance.CountSpeed;

            if (1 < instance.Time)
            {
                instance.Time = 0;
                instance.CountSpeed = uniform(0.05f, 0.1f);

                float r = normal(15, 5) + 15;
                float t = uniform(0, PI2);
                float z = normal(70, 20);
                float dx = normal(0.5f, 0.2f);
                float dz = normal(20, 5);

                Matrix4x3 adjustment = new Matrix4x3().Identity();
                adjustment.RotateZ(t);
                adjustment.Translate(0, -r, z);
                adjustment.Scale(dx, 0, dz);
                instance.Matrix = adjustment * world;
            }
        }
    }

    private void TranslucentRender()
    {
        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        device.SetVertexBuffer(VertexPositions, 0);
        device.SetVertexBuffer(VertexTextureCoords, 1);

        PixelShader.SetTexture(Texture, 0);

        InstanceWVPs.Lock(Accessibility.DynamicWriteOnly);
        InstanceAlphas.Lock(Accessibility.DynamicWriteOnly);
        for (int i = 0; i < InstanceCount; i++)
        {
            var instance = this.Instances[i];
            InstanceWVPs.Write(i, instance.Matrix * this.ViewingMatrix * this.ProjectionMatrix);

            // 速度に応じて濃度を濃くする
            float alpha = 0.15f * instance.Time * max(this.Physics.Velocity.Magnitude - 3.0f, 0.0f);
            InstanceAlphas.Write(i, alpha);
        }
        InstanceAlphas.Unlock();
        InstanceWVPs.Unlock();

        device.SetInstanceBuffer(InstanceAlphas, 2);
        device.SetInstanceBuffer(InstanceWVPs, 3);

        device.DrawInstanced(4, InstanceCount);
    }
}
