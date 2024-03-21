using System;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class JetComponent : CustomEntityComponent
{
    public Vector3 OffsetPosition { private get; set; } = Vector3.Zero;
    public float Power { private get; set; } = 1.0f;
    public const float PowerLowerLimit = 0.9f;

    static VertexBuffer<Vector3> VertexPositionsBuffer = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector2> VertexTexcoordsBuffer = new VertexBuffer<Vector2>();
    static IndexBuffer IndexBuffer = new IndexBuffer();
    static Texture2D Texture = new Texture2D();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();

    static JetComponent()
    {
        VertexShader.CreateFromFile("res/shader/JetVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/JetPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        const int DIVISIONS = 24;   // 円の三角形の分割数
        const int LENGTH = 4;       // 円の数

        // 頂点数
        const int VERTICES = (DIVISIONS + 1 + 1) * LENGTH + DIVISIONS * 4 / 2;

        // インデックス数
        const int INDICES = DIVISIONS * LENGTH * 3 + DIVISIONS * 2 * 3 / 2;

        // 頂点バッファを作成する
        {
            Vector3[] positions = new Vector3[VERTICES];
            Vector2[] texcoords = new Vector2[VERTICES];
            int idx = 0;

            for (int l = 0; l < LENGTH; l++)
            {
                // 中心の点
                float u = (float)l / (LENGTH - 1);
                float z = -(float)l / (LENGTH - 1);
                positions[idx] = new Vector3(0, 0, z);
                texcoords[idx] = new Vector2(0, 0.5f);
                idx++;

                // 円周上の点
                for (int d = 0; d < DIVISIONS + 1; d++)
                {
                    const float pi2 = (float)Math.PI * 2.0f;
                    float r = 0.5f - 0.25f * l / (LENGTH - 1);      // 0.25 -> 0.125
                    float t = pi2 * (float)d / DIVISIONS;           // 0 -> pie * 2
                    float x = r * cos(t);
                    float y = r * sin(t);
                    float v = 0;
                    positions[idx] = new Vector3(x, y, z);
                    texcoords[idx] = new Vector2(u, v);
                    idx++;
                }
            }

            // 断面の点
            for (int d = 0; d < DIVISIONS / 2; d++)
            {
                const float pi = (float)Math.PI;
                float t = pi * d / DIVISIONS * 2;                   // 0 -> pie
                float x = 0.5f * cos(t);
                float y = -0.5f * sin(t);
                var p0 = new Vector3(-x, -y, 0);
                var p1 = new Vector3(x, y, 0);
                var p2 = new Vector3(-0.5f * x, -0.5f * y, -1);
                var p3 = new Vector3(0.5f * x, 0.5f * y, -1);
                var t0 = new Vector2(0, 0);
                var t1 = new Vector2(0, 1);
                var t2 = new Vector2(1, 0);
                var t3 = new Vector2(1, 1);
                positions[idx] = p0;
                texcoords[idx] = t0;
                idx++;
                positions[idx] = p1;
                texcoords[idx] = t1;
                idx++;
                positions[idx] = p2;
                texcoords[idx] = t2;
                idx++;
                positions[idx] = p3;
                texcoords[idx] = t3;
                idx++;
            }
            VertexPositionsBuffer.Create(positions, Accessibility.None);
            VertexTexcoordsBuffer.Create(texcoords, Accessibility.None);
        }

        // インデックスバッファを作成する
        {
            int[] indexBufferSource = new int[INDICES];
            int idx = 0;
            {
                // 円の描画
                for (int l = 0; l < LENGTH; l++)
                {
                    int offset = l * (DIVISIONS + 2);
                    for (int d = 0; d < DIVISIONS; d++)
                    {
                        indexBufferSource[idx++] = offset + 0;
                        indexBufferSource[idx++] = offset + d + 1;
                        indexBufferSource[idx++] = offset + d + 2;
                    }
                }

                // 円柱の描画
                for (int d = 0; d < DIVISIONS / 2; d++)
                {
                    const int offset = (DIVISIONS + 1 + 1) * LENGTH;
                    int i0 = offset + d * 4;
                    int i1 = offset + d * 4 + 1;
                    int i2 = offset + d * 4 + 2;
                    int i3 = offset + d * 4 + 3;
                    indexBufferSource[idx++] = i0;
                    indexBufferSource[idx++] = i1;
                    indexBufferSource[idx++] = i2;
                    indexBufferSource[idx++] = i2;
                    indexBufferSource[idx++] = i1;
                    indexBufferSource[idx++] = i3;
                }
            }
            IndexBuffer.Create(indexBufferSource, Accessibility.None);
        }

        // テクスチャを作成する
        Texture.Create("res/texture/jet.dds", Accessibility.None);
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        assert(this.Owner.Has<AircraftComponent>() || this.Owner.Has<MissileComponent>());

        if (this.Owner.Has<AircraftComponent>())
            this.OffsetPosition = this.Owner.Get<AircraftComponent>().Parameter.EngineNozzlePos;
        if (this.Owner.Has<MissileComponent>())
            this.OffsetPosition = this.Owner.Get<MissileComponent>().EngineNozzlePos;
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case TranslucentRenderMessage:
                this.TranslucentRender();
                break;

            default:
                break;
        }
    }

    private void TranslucentRender()
    {
        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexBuffer(VertexPositionsBuffer, 0);
        device.SetVertexBuffer(VertexTexcoordsBuffer, 1);
        device.SetIndexBuffer(IndexBuffer);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(Texture, 0);

        if (PowerLowerLimit < this.Power)
        {
            var physics = this.Owner.Get<PhysicsComponent>();
            var transform = this.Owner.Get<TransformComponent>();
            var angular = new Vector4(physics.AngularVelocity, 0) * transform.Matrix.Inverse;

            {
                var offsetPosition = this.OffsetPosition;
                Matrix4x3 adjustment = new Matrix4x3();
                adjustment.Identity();
                adjustment.Translate(offsetPosition);
                adjustment.RotateX(clamp((-angular.X * 2 + angular.Z * 0.5f) * 5, -0.2f, 0.2f));
                adjustment.Scale(normal(1.7f, 0.1f), normal(1.7f, 0.1f), normal(3.8f, 0.1f) * (this.Power - PowerLowerLimit) / 0.1f);

                VertexShader.SetConstantBuffer(adjustment * this.WVPMatrix, 0);
                device.DrawIndexed(IndexBuffer.Count);
            }

            if (this.OffsetPosition.X != 0)
            {
                var offsetPosition = this.OffsetPosition;
                offsetPosition.X *= -1;

                Matrix4x3 adjustment = new Matrix4x3();
                adjustment.Identity();
                adjustment.Translate(offsetPosition);
                adjustment.RotateX(clamp((-angular.X * 2 - angular.Z * 0.5f) * 5, -0.2f, 0.2f));
                adjustment.Scale(normal(1.7f, 0.1f), normal(1.7f, 0.1f), normal(3.8f, 0.1f) * (this.Power - PowerLowerLimit) / 0.1f);

                VertexShader.SetConstantBuffer(adjustment * this.WVPMatrix, 0);
                device.DrawIndexed(IndexBuffer.Count);
            }
        }
    }
};
