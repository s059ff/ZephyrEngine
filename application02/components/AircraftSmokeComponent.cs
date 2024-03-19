using System.Collections.Generic;
using System.Linq;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class AircraftSmokeComponent : CustomEntityComponent
{
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector2> VertexTextureCoords = new VertexBuffer<Vector2>();
    static InstanceBuffer<float> InstanceAlphas = new InstanceBuffer<float>();
    static InstanceBuffer<Matrix4x4> InstanceWVPs = new InstanceBuffer<Matrix4x4>();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static Texture2D Texture = new Texture2D();

    const int MaxInstanceCount = 64;
    float CountSpeed = 0.05f;

    class Instance
    {
        public Vector3 Position;
        public float Time;
    }

    List<Instance> Instances = new List<Instance>();

    static AircraftSmokeComponent()
    {
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

        InstanceAlphas.Create(MaxInstanceCount, Accessibility.DynamicWriteOnly);
        InstanceWVPs.Create(MaxInstanceCount, Accessibility.DynamicWriteOnly);

        VertexShader.CreateFromFile("res/shader/AircraftSmokeVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/AircraftSmokePixelShader.hlsl");

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

        Texture.Create("res/texture/smoke.dds", Accessibility.None);
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        if (this.Owner.Has<TransformComponent>())
        {
            this.Instances.Add(new Instance()
            {
                Position = this.Owner.Get<TransformComponent>().Position,
                Time = 0
            });
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
                this.TranslucentRender();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        if (this.HasOwner && this.Owner.Has<TransformComponent>())
        {
            this.Instances.Add(new Instance()
            {
                Position = this.Owner.Get<TransformComponent>().Position + new Vector3(normal(0, 2), normal(0, 2), normal(0, 2)),
                Time = 0
            });
        }

        this.Instances = this.Instances.Where(instance => (instance.Time < 1.0f)).ToList();

        if (this.Instances.Count == 0)
        {
            Entity.Kill(this.Owner);
        }

        foreach (var node in this.Instances)
        {
            node.Time += this.CountSpeed;
        }

        assert(this.Instances.Count < MaxInstanceCount);
    }

    private void TranslucentRender()
    {
        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Subtraction);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        device.SetVertexBuffer(VertexPositions, 0);
        device.SetVertexBuffer(VertexTextureCoords, 1);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(Texture, 0);

        InstanceAlphas.Lock(Accessibility.DynamicWriteOnly);
        for (int i = 0; i < this.Instances.Count; i++)
        {
            var instance = this.Instances[i];
            float x = instance.Time;
            float alpha = clamp(sin(square(1.2f - x)), 0, 1) * 0.2f;

            if (this.Owner.Has<LimitedLifeTimeComponent>())
            {
                float t = this.Owner.Get<LimitedLifeTimeComponent>().CountTime;
                alpha *= 1.0f - t;
            }

            InstanceAlphas.Write(i, alpha);
        }
        InstanceAlphas.Unlock();

        InstanceWVPs.Lock(Accessibility.DynamicWriteOnly);
        for (int i = 0; i < this.Instances.Count; i++)
        {
            var instance = this.Instances[i];
            float x = instance.Time;
            float scale = clamp(-3 * sin(x) * log(x), 0, 1) * 15 + 10;

            Vector3 position = instance.Position;
            Matrix4x3 world = new Matrix4x3().Identity();
            world.Translate(position * this.ViewingMatrix);
            world.Scale(scale);

            InstanceWVPs.Write(i, world * this.ProjectionMatrix);
        }
        InstanceWVPs.Unlock();

        device.SetInstanceBuffer(InstanceAlphas, 2);
        device.SetInstanceBuffer(InstanceWVPs, 3);

        device.DrawInstanced(4, this.Instances.Count);
    }
}
