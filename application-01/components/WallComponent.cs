using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static Script;

class WallComponent : EntityComponent
{
    static GraphicsModel GraphicsModel = new GraphicsModel();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();

    public PlaneSurfaceCollisionObject Collision = new PlaneSurfaceCollisionObject(new PlaneSurface() { });

    static WallComponent()
    {
        VertexShader.CreateFromFile("res/shader/WallVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/WallPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("NORMAL", 0, Format.Float3, 1, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 2, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        GraphicsModel.CreateBillBoard();
        GraphicsModel.Texture = new Texture2D();
        GraphicsModel.Texture.Create("res/texture/wall.png", Accessibility.None);

        Program.ResourceManager.Register("res/shader/WallVertexShader.hlsl", (path) => VertexShader);
        Program.ResourceManager.Load("res/shader/WallVertexShader.hlsl");
        Program.ResourceManager.Register("res/shader/WallPixelShader.hlsl", (path) => PixelShader);
        Program.ResourceManager.Load("res/shader/WallPixelShader.hlsl");
        Program.ResourceManager.Register("WallVertexLayout", (path) => VertexLayout);
        Program.ResourceManager.Load("WallVertexLayout");
        Program.ResourceManager.Register("WallGraphicsModel", (path) => GraphicsModel);
        Program.ResourceManager.Load("WallGraphicsModel");
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        Collision.Shape.Normal = new Vector3(0, 0, -1);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            case RenderMessage:
                this.Render();
                break;

            default:
                break;
        }
    }

    void Update()
    {
    }

    void Render()
    {
        GraphicsDeviceContext context = GraphicsDeviceContext.Instance;
        context.SetBlendState(Addition);
        context.SetRasterizerState(CullingOn);
        context.SetDepthStencilState(ZTestOnWriteOff);
        context.SetVertexLayout(VertexLayout);
        context.SetVertexShader(VertexShader);
        context.SetPixelShader(PixelShader);

        context.SetPrimitiveTopology(GraphicsModel.Topology);
        context.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
        context.SetVertexBuffer(GraphicsModel.VertexNormals, 1);
        context.SetVertexBuffer(GraphicsModel.VertexTextureCoords, 2);

        var world = this.Owner.Get<TransformComponent>().Matrix;
        var viewing = Entity.Find("camera").Get<CameraComponent>().ViewingMatrix;
        var projection = Entity.Find("projector").Get<ProjectorComponent>().ProjectionMatrix;
        var viewing_light = Entity.Find("light").Get<TransformComponent>().Matrix.Inverse;
        var projection_light = Entity.Find("projector_light").Get<ProjectorComponent>().ProjectionMatrix;
        var light_direction = -Entity.Find("light").Get<TransformComponent>().Forward;

        VertexShader.SetConstantBuffer(world * viewing * projection, 0);
        VertexShader.SetConstantBuffer(world * viewing_light * projection_light, 1);
        PixelShader.SetConstantBuffer(world, 0);
        PixelShader.SetConstantBuffer(new Vector4(light_direction, 0), 2);
        PixelShader.SetTexture(GraphicsModel.Texture, 0);
        PixelShader.SetTexture(Program.DepthMap, 1);

        context.Draw(4);
    }
}
