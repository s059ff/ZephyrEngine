using System.Collections.Generic;
using System.Linq;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class StringySmokeComponent : CustomEntityComponent
{
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector4> VertexColors = new VertexBuffer<Vector4>();
    static InstanceBuffer<Color> InstanceColors = new InstanceBuffer<Color>();
    static InstanceBuffer<Matrix4x4> InstanceWVPs = new InstanceBuffer<Matrix4x4>();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();

    public float Intensity { private get; set; }

    const int InstanceCount = 256;
    const float CountSpeed = 0.01f;

    class Node
    {
        public Vector3 Position;
        public float Alpha;
        public float Time;
    }

    LinkedList<Node> Nodes = new LinkedList<Node>();

    static StringySmokeComponent()
    {
        VertexPositions.Create(new Vector3[]
        {
            new Vector3(0.0f, +0.25f, 1.0f),
            new Vector3(0.0f, +0.25f, 0.0f),
            new Vector3(0.0f, 0.0f, 1.0f),
            new Vector3(0.0f, 0.0f, 0.0f),
            new Vector3(0.0f, -0.25f, 1.0f),
            new Vector3(0.0f, -0.25f, 0.0f),
        }, Accessibility.None);

        VertexColors.Create(new Vector4[]
        {
            new Vector4(0, 0, 0, 1),
            new Vector4(0, 0, 0, 1),
            new Vector4(1, 1, 1, 1),
            new Vector4(1, 1, 1, 1),
            new Vector4(0, 0, 0, 1),
            new Vector4(0, 0, 0, 1),
        }, Accessibility.None);

        InstanceColors.Create(InstanceCount, Accessibility.DynamicWriteOnly);
        InstanceWVPs.Create(InstanceCount, Accessibility.DynamicWriteOnly);

        VertexShader.CreateFromFile("res/shader/StringySmokeVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/StringySmokePixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("VERTEX_COLOR", 0, Format.Float4, 1, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("INSTANCE_COLOR", 0, Format.Float4, 2, 0, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 0, Format.Float4, 3, sizeof(float) * 0, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 1, Format.Float4, 3, sizeof(float) * 4, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 2, Format.Float4, 3, sizeof(float) * 8, VertexElement.Classification.InstanceData, 1),
            new VertexElement("WVP", 3, Format.Float4, 3, sizeof(float) * 12, VertexElement.Classification.InstanceData, 1),
        }, VertexShader);
    }

    public StringySmokeComponent()
    {
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        if (this.Owner.Has<TransformComponent>())
        {
            Nodes.AddFirst(new Node()
            {
                Position = this.Owner.Get<TransformComponent>().Position,
                Alpha = 0,
                Time = 0
            });
        }
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
        if (this.Owner.Has<TransformComponent>())
        {
            Nodes.AddFirst(new Node()
            {
                Position = Transform.Position,
                Alpha = clamp(this.Intensity, 0.0f, 1.0f),
                Time = 0
            });
        }
        if (this.Owner.Has<TransformComponent>())
        {
            Nodes.First.Value.Position = Transform.Position;
        }

        foreach (var node in Nodes.Where(node => { return 1.0f <= node.Time; }).ToArray())
        {
            Nodes.Remove(node);
        }

        if (Nodes.Count == 0)
        {
            Entity.Kill(this.Owner);
        }

        foreach (var node in Nodes)
        {
            node.Time += CountSpeed;
        }

        assert(Nodes.Count <= InstanceCount);
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
        device.SetVertexBuffer(VertexColors, 1);

        var viewing = ViewingMatrix;
        var projection = ProjectionMatrix;
        var eye = Entity.Find("camera").Get<TransformComponent>().Position;

        Matrix4x4[] matrices = new Matrix4x4[Nodes.Count];
        Color[] colors = new Color[Nodes.Count];

        int k = 0;
        Vector3 position2 = Nodes.First.Value.Position;
        foreach (var node in Nodes)
        {
            Vector3 position1 = node.Position;

            if (k > 0)
            {
                Vector3 vz = position2 - position1;
                vz.Normalize();

                Vector3 vy = Vector3.Outer(vz, position1 - eye);
                vy.Normalize();
                Vector3 vx = Vector3.Outer(vy, vz);
                Matrix4x3 matrix = new Matrix4x3().Identity();
                matrix.M11 = vx.X; matrix.M12 = vx.Y; matrix.M13 = vx.Z;
                matrix.M21 = vy.X; matrix.M22 = vy.Y; matrix.M23 = vy.Z;
                matrix.M31 = vz.X; matrix.M32 = vz.Y; matrix.M33 = vz.Z;

                var world = new Matrix4x3().Identity();
                world.Translate(position1);
                world.Transform(matrix);
                world.Scale(1, 2, (position1 - position2).Magnitude);

                matrices[k] = world * viewing * projection;

                // 機体の少し後方から発生し, 時間経過で消えるように見せる
                // 機体が旋回しているときは濃度を濃くする
                float alpha = clamp(exp(-square(node.Time - 0.5f) / 0.075f), 0, 1) * 0.75f * node.Alpha;
                colors[k] = new Color(alpha, alpha, alpha);
            }
            k++;
            position2 = position1;
        }

        InstanceWVPs.Lock(Accessibility.DynamicWriteOnly);
        for (int i = 0; i < Nodes.Count; i++)
        {
            InstanceWVPs.Write(i, matrices[i]);
        }
        InstanceWVPs.Unlock();

        InstanceColors.Lock(Accessibility.DynamicWriteOnly);
        for (int i = 0; i < Nodes.Count; i++)
        {
            InstanceColors.Write(i, colors[i]);
        }
        InstanceColors.Unlock();

        device.SetInstanceBuffer(InstanceColors, 2);
        device.SetInstanceBuffer(InstanceWVPs, 3);

        device.DrawInstanced(6, Nodes.Count - 1);
    }
}
