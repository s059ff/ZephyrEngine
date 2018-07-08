using System.Collections.Generic;
using System.Linq;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static Script;

public class AircraftFlameComponent : CustomEntityComponent
{
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();
    static Texture2DArray Textures = new Texture2DArray();
    static GraphicsModel GraphicsModel = new GraphicsModel();
    static Matrix4x4[] InstanceWVPs = new Matrix4x4[InstanceCount];
    static Color[] InstanceColors = new Color[InstanceCount];

    const int TextureCount = 16;
    const float CountSpeed = 0.1f;
    const int InstanceCount = 64;

    class Instance
    {
        public Vector3 Position;
        public float Time;
    }

    LinkedList<Instance> Instances = new LinkedList<Instance>();

    static AircraftFlameComponent()
    {
        VertexShader.CreateFromFile("res/shader/AircraftFlameVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/AircraftFlamePixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        Textures.Create("res/texture/flame.dds", Accessibility.None);

        GraphicsModel.CreateBillBoard();
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
        if (this.HasOwner && this.Owner.Has<TransformComponent>())
        {
            Instances.AddFirst(new Instance()
            {
                Position = this.Owner.Get<TransformComponent>().Position + new Vector3(normal(0, 2), normal(0, 2), normal(0, 2)),
                Time = 0
            });
        }

        foreach (var instance in Instances.Where(instance => 1.0f <= instance.Time).ToArray())
        {
            Instances.Remove(instance);
        }

        if (Instances.Count == 0)
        {
            Entity.Kill(this.Owner);
        }

        foreach (var node in Instances)
        {
            node.Time += CountSpeed;
        }

        assert(Instances.Count < InstanceCount);
    }

    void TransparentRender()
    {
        GraphicsDevice device = GraphicsDevice.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleStrip);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        var viewing = ViewingMatrix;
        var projection = ProjectionMatrix;

        int k = 0;
        foreach (var instance in Instances)
        {
            Vector3 position = instance.Position;
            float x = instance.Time;
            float scale = clamp(-3 * sin(x) * log(x), 0, 1) * 10 + 5;
            float alpha = clamp(sin(square(1.2f - x)), 0, 1) * 0.2f;

            var world = new Matrix4x3().Identity();
            world.Translate(position * ViewingMatrix);
            world.Scale(scale);

            InstanceWVPs[k] = world * ProjectionMatrix;
            InstanceColors[k] = new Color(alpha, alpha ,alpha, instance.Time);

            k++;
        }

        device.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
        device.SetVertexBuffer(GraphicsModel.VertexTextureCoords, 1);
        VertexShader.SetConstantBuffer(InstanceWVPs, 0);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTextureArray(Textures, 0);
        PixelShader.SetConstantBuffer(InstanceColors, 0);

        device.DrawInstanced(4, InstanceCount);
    }
}
