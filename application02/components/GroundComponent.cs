using System.Drawing;
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
    static GraphicsModel GraphicsModel = new GraphicsModel();
    static Texture2D Texture = new Texture2D();
    static Texture2D Texture2 = new Texture2D();
    static Texture2D MixingRateTexture = new Texture2D();
    static float[,] Heights;

    const int NumVertices = 512 + 1;

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

        Texture.Create("res/texture/ground.png", Accessibility.None);
        Texture2.Create("res/texture/sand.png", Accessibility.None);
        MixingRateTexture.Create("res/texture/mixing_rate.png", Accessibility.None);
        Heights = ComputeHeightMapFromImage("res/texture/heightmap.png");
        GraphicsModel.CreateMeshMap(Heights);
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        var scale = Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength;
        this.Owner.Get<TransformComponent>().Matrix.RotateX(deg2rad(90));
        this.Owner.Get<TransformComponent>().Matrix.Scale(scale);

        this.Owner.Get<CollisionComponent>().Object = new CurvedSurfaceCollisionObject(new CurvedSurface() { Heights = Heights });
        this.Owner.Get<CollisionComponent>().Group = CollisionGroupGround;
        this.Owner.Get<CollisionComponent>().OtherGroups = CollisionGroupNone;
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

    private static float[,] ComputeHeightMapFromImage(string path)
    {
        const float max = 0.025f;
        const float min = 0.0f;

        float[,] heights = new float[NumVertices, NumVertices];
        using (Bitmap origin = new Bitmap(path))
        using (Bitmap bitmap = new Bitmap(origin, NumVertices, NumVertices))
        {
            for (int i = 0; i < NumVertices; i++)
            {
                for (int j = 0; j < NumVertices; j++)
                {
                    var pixel = bitmap.GetPixel(j, i);
                    heights[i, j] = pixel.R / 255.0f * (max - min) + min;
                }
            }
        }
        return heights;
    }
}
