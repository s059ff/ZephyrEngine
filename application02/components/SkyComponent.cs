using System.Collections.Generic;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class SkyComponent : CustomEntityComponent
{
    static VertexBuffer<Vector3> VertexBuffer = new VertexBuffer<Vector3>();
    static IndexBuffer IndexBuffer = new IndexBuffer();
    static Texture2DArray Texture = new Texture2DArray();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();

    static SkyComponent()
    {
        // 円周方向の分割数
        const int Slices = 16;

        // Y方向の分割数
        const int Stacks = 8;

        List<Vector3> positions = new List<Vector3>();
        for (int i = 0; i < Stacks + 1; i++)
        {
            float y = 1.0f - 2.0f * (float)i / Stacks;
            float r = sqrt(1 - y * y);
            for (int j = 0; j < Slices + 1; j++)
            {
                float t = (float)j / Slices * 3.14159f * 2;
                float x = r * cos(t);
                float z = r * sin(t);
                Vector3 v = new Vector3(x / 2, y / 2, z / 2);
                positions.Add(v);
            }
        }
        VertexBuffer.Create(positions.ToArray(), Accessibility.None);

        List<int> indices = new List<int>();
        for (int i = 0; i < Stacks; i++)
        {
            for (int j = 0; j < Slices; j++)
            {
                int i0 = (Slices + 1) * i + j;
                int i1 = i0 + 1;
                int i2 = (Slices + 1) * (i + 1) + j;
                int i3 = i2 + 1;
                indices.Add(i0);
                indices.Add(i2);
                indices.Add(i1);
                indices.Add(i1);
                indices.Add(i2);
                indices.Add(i3);
            }
        }
        IndexBuffer.Create(indices.ToArray(), Accessibility.None);

        Texture.CreateCubeMap("res/texture/skybox.dds", Accessibility.None);

        VertexShader.CreateFromFile("res/shader/SkyVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/SkyPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        var scale = Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength * sqrt(2);
        this.Owner.Get<TransformComponent>().Matrix.Scale(scale);
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

    void Render()
    {
        //viewing.Invert();
        //viewing.Position = new Vector3(0, 0, 0);
        //viewing.Invert();

        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(NoBlend);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        device.SetVertexBuffer(VertexBuffer, 0);
        device.SetIndexBuffer(IndexBuffer);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTextureArray(Texture, 0);
        VertexShader.SetConstantBuffer(this.WVPMatrix, 0);

        device.DrawIndexed(IndexBuffer.Count);
    }
}
