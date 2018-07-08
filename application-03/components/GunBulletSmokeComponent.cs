using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class GunBulletSmokeComponent : CustomEntityComponent
{
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector2> VertexTextureCoords = new VertexBuffer<Vector2>();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static Texture2D Texture = new Texture2D();

    static GunBulletSmokeComponent()
    {
        VertexPositions.Create(new Vector3[]
        {
            new Vector3(-0.5f, +1, 0),
            new Vector3(+0.5f, +1, 0),
            new Vector3(-0.5f, 0, 0),
            new Vector3(+0.5f, 0, 0),
        }, Accessibility.None);

        VertexTextureCoords.Create(new Vector2[]
        {
            new Vector2(0, 0),
            new Vector2(1, 0),
            new Vector2(0, 1),
            new Vector2(1, 1),
        }, Accessibility.None);

        VertexShader.CreateFromFile("res/shader/GunBulletSmokeVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/GunBulletSmokePixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 1, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        Texture.Create("res/texture/water.dds", Accessibility.None);
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

        var world = new Matrix4x3().Identity();
        var camera = Entity.Find("camera").Get<TransformComponent>();
        var time = this.Owner.Get<LimitedLifeTimeComponent>().CountTime;
        var scale = sin(time * PI) * 6;
        var alpha = sin(time * PI) * 0.4f;
        world.Translate(Transform.Position);
        world.RotateY(atan2(camera.Forward.X, camera.Forward.Z));
        world.Scale(0.5f * scale, scale, 1);
        VertexShader.SetConstantBuffer(world * ViewingMatrix * ProjectionMatrix, 0);
        PixelShader.SetConstantBuffer(new Color(alpha, alpha, alpha), 0);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(Texture, 0);

        device.Draw(4);
    }
}
