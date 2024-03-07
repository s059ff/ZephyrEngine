using System.Collections.Generic;
using System.Linq;
using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static Script;

public class BallComponent : EntityComponent
{
    static GraphicsModel GraphicsModel = new GraphicsModel();
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader0 = new PixelShader();
    static PixelShader PixelShader1 = new PixelShader();
    static SamplerState SamplerState0 = new SamplerState();
    static SamplerState SamplerState1 = new SamplerState();

    SphereCollisionObject Collision = new SphereCollisionObject(new Sphere() { });
    Color Color = new Color(uniform(0.0f, 1.0f), uniform(0.0f, 1.0f), uniform(0.0f, 1.0f), 1);

    static LinkedList<BallComponent> Instances = new LinkedList<BallComponent>();

    static BallComponent()
    {
        VertexShader.CreateFromFile("res/shader/BallVertexShader.hlsl");
        PixelShader0.CreateFromFile("res/shader/BallPixelShader.hlsl", "pass0");
        PixelShader1.CreateFromFile("res/shader/BallPixelShader.hlsl", "pass1");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("NORMAL", 0, Format.Float3, 1, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        GraphicsModel.CreateSphere(16, 16);

        SamplerState0.Create(TextureAddressMode.Wrap, TextureAddressMode.Wrap, TextureAddressMode.Wrap);
        SamplerState1.CreateComparator();

        Program.ResourceManager.Register("res/shader/BallVertexShader.hlsl", (path) => VertexShader);
        Program.ResourceManager.Load("res/shader/BallVertexShader.hlsl");
        Program.ResourceManager.Register("res/shader/BallPixelShader0.hlsl", (path) => PixelShader0);
        Program.ResourceManager.Load("res/shader/BallPixelShader0.hlsl");
        Program.ResourceManager.Register("res/shader/BallPixelShader1.hlsl", (path) => PixelShader1);
        Program.ResourceManager.Load("res/shader/BallPixelShader1.hlsl");
        Program.ResourceManager.Register("WallVertexLayout", (path) => VertexLayout);
        Program.ResourceManager.Load("WallVertexLayout");
        Program.ResourceManager.Register("WallGraphicsModel", (path) => GraphicsModel);
        Program.ResourceManager.Load("WallGraphicsModel");
        Program.ResourceManager.Register("WallSamplerState0", (path) => SamplerState0);
        Program.ResourceManager.Load("WallSamplerState0");
        Program.ResourceManager.Register("WallSamplerState1", (path) => SamplerState1);
        Program.ResourceManager.Load("WallSamplerState1");
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        Instances.AddLast(this);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            case RenderDepthMapMessage:
                this.RenderDepthMap();
                break;

            case RenderMessage:
                this.Render();
                break;

            default:
                break;
        }
    }

    private void Update()
    {
        var transform = this.Owner.Get<TransformComponent>();
        var world = transform.Matrix;

        var physics = this.Owner.Get<PhysicsComponent>();
        physics.Force = new Vector3(0, -Gravity * physics.Mass, 0);

        Collision.Matrix = world;
        Collision.Velocity = physics.Velocity;

        {
            var floor = Entity.Find("floor");
            var point = Collision.CollidePoint(floor.Get<FloorComponent>().Collision);
            if (!float.IsNaN(point.X))
            {
                Vector3 v1 = point - transform.Position - physics.Velocity;
                Vector3 v2 = transform.Position - point;
                Vector4 _n = new Vector4(floor.Get<FloorComponent>().Collision.Shape.Normal, 0);
                _n = _n * floor.Get<TransformComponent>().Matrix;
                Vector3 n = new Vector3(_n.X, _n.Y, _n.Z);
                Vector3 v3 = Vector3.Project(v2, n) * 2;

                transform.Position = point;
                physics.Force += v3.Normalize() * physics.Velocity.Magnitude * physics.Mass;
            }
        }

        for (int i = 1; i <= 4; i++)
        {
            var wall = Entity.Find("wall" + i);
            var point = Collision.CollidePoint(wall.Get<WallComponent>().Collision);
            if (!float.IsNaN(point.X))
            {
                Vector3 v1 = point - transform.Position - physics.Velocity;
                Vector3 v2 = transform.Position - point;
                Vector4 _n = new Vector4(wall.Get<WallComponent>().Collision.Shape.Normal, 0);
                _n = _n * wall.Get<TransformComponent>().Matrix;
                Vector3 n = new Vector3(_n.X, _n.Y, _n.Z);
                Vector3 v3 = Vector3.Project(v2, n) * 2;

                transform.Position = point;
                physics.Force += v3.Normalize() * physics.Velocity.Magnitude * physics.Mass;
            }
        }

        if (Instances.First.Value == this)
        {
            int InstanceCount = Instances.Count;
            for (int i = 0; i < InstanceCount; i++)
            {
                var obj1 = Instances.ToArray()[i];
                var transform1 = obj1.Owner.Get<TransformComponent>();
                var physics1 = obj1.Owner.Get<PhysicsComponent>();

                if (physics1.Velocity.SquaredMagnitude == 0)
                    continue;

                for (int j = i + 1; j < InstanceCount; j++)
                {
                    var obj2 = Instances.ToArray()[j];
                    var transform2 = obj2.Owner.Get<TransformComponent>();
                    var physics2 = obj2.Owner.Get<PhysicsComponent>();

                    if (physics2.Velocity.SquaredMagnitude == 0)
                        continue;

                    var time = obj1.Collision.CollideTime(obj2.Collision);
                    //var time = CollisionDetector.CalculateCollisionTime(obj1.Shape, transform1.Matrix, obj2.Shape, transform2.Matrix);
                    if (!float.IsNaN(time) && (0 <= time) && (time <= 1))
                    {
                        var v1 = physics1.Velocity;
                        var v2 = physics2.Velocity;
                        transform1.Position = transform1.Position + (time - 1) * physics1.Velocity;
                        transform2.Position = transform2.Position + (time - 1) * physics2.Velocity;
                        physics1.Force += v2.Normalize() * physics2.Velocity.Magnitude * physics2.Mass;
                        physics2.Force += v1.Normalize() * physics1.Velocity.Magnitude * physics1.Mass;
                    }
                }

                Vector3 repulsiveForce = new Vector3();

                for (int j = 0; j < InstanceCount; j++)
                {
                    var obj2 = Instances.ToArray()[j];
                    var transform2 = obj2.Owner.Get<TransformComponent>();
                    var physics2 = obj2.Owner.Get<PhysicsComponent>();

                    if (i != j)
                    {
                        repulsiveForce += (transform1.Position - transform2.Position).Normalize() / (transform2.Position - transform1.Position).SquaredMagnitude;
                    }
                }

                physics1.Force += repulsiveForce / 100;
            }

            if (frame % 180 == 0)
            {
                for (int i = 0; i < 10; i++)
                {
                    Entity ball = Entity.Instantiate();
                    ball.Attach(new TransformComponent());
                    ball.Attach(new PhysicsComponent());
                    ball.Attach(new BallComponent());
                    ball.Get<TransformComponent>().Matrix = new Matrix4x3().Identity().Translate(uniform(-5.0f, 5.0f), uniform(3.0f, 5.0f), uniform(-5.0f, 5.0f));
                    ball.Get<PhysicsComponent>().Mass = 10.0f;
                    ball.Get<PhysicsComponent>().Force = new Vector3(uniform(-1.0f, 1.0f), 0, uniform(-1.0f, 1.0f));
                }
            }
        }

        if (transform.Position.X < -4.5f)
        {
            transform.Matrix.M41 = -4.5f;
            physics.Force += new Vector3(0.25f, 0, 0);
        }
        if (transform.Position.X > 4.5f)
        {
            transform.Matrix.M41 = 4.5f;
            physics.Force += new Vector3(-0.25f, 0, 0);
        }
        if (transform.Position.Z < -4.5f)
        {
            transform.Matrix.M43 = -4.5f;
            physics.Force += new Vector3(0, 0, 0.25f);
        }
        if (transform.Position.Z > 4.5f)
        {
            transform.Matrix.M43 = 4.5f;
            physics.Force += new Vector3(0, 0, -0.25f);
        }
        if (transform.Position.Y < 0.5f)
        {
            transform.Matrix.M42 = 0.5f;
            physics.Force += new Vector3(0, 0.25f, 0);
        }

        physics.Velocity = clamp(physics.Velocity, 0, 0.2f);
    }

    private void RenderDepthMap()
    {
        GraphicsDeviceContext context = GraphicsDeviceContext.Instance;
        context.SetBlendState(NoBlend);
        context.SetRasterizerState(CullingOff);
        context.SetDepthStencilState(ZTestOn);
        context.SetVertexLayout(VertexLayout);
        context.SetVertexShader(VertexShader);
        context.SetPixelShader(PixelShader0);

        context.SetPrimitiveTopology(GraphicsModel.Topology);
        context.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
        context.SetVertexBuffer(GraphicsModel.VertexNormals, 1);
        context.SetIndexBuffer(GraphicsModel.VertexIndices);

        var world = this.Owner.Get<TransformComponent>().Matrix;
        var viewing_light = Entity.Find("light").Get<TransformComponent>().Matrix.Inverse;
        var projection_light = Entity.Find("projector_light").Get<ProjectorComponent>().ProjectionMatrix;

        VertexShader.SetConstantBuffer(world * viewing_light * projection_light, 0);
        VertexShader.SetConstantBuffer(world * viewing_light * projection_light, 1);
        PixelShader0.SetConstantBuffer(world, 0);
        PixelShader0.SetConstantBuffer(Color, 1);

        context.DrawIndexed(GraphicsModel.VertexIndices.Count);
    }

    private void Render()
    {
        GraphicsDeviceContext context = GraphicsDeviceContext.Instance;
        context.SetBlendState(NoBlend);
        context.SetRasterizerState(CullingOff);
        context.SetDepthStencilState(ZTestOn);
        context.SetVertexLayout(VertexLayout);
        context.SetVertexShader(VertexShader);
        context.SetPixelShader(PixelShader1);

        context.SetPrimitiveTopology(GraphicsModel.Topology);
        context.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
        context.SetVertexBuffer(GraphicsModel.VertexNormals, 1);
        context.SetIndexBuffer(GraphicsModel.VertexIndices);

        var world = this.Owner.Get<TransformComponent>().Matrix;
        var viewing = Entity.Find("camera").Get<CameraComponent>().ViewingMatrix;
        var projection = Entity.Find("projector").Get<ProjectorComponent>().ProjectionMatrix;
        var viewing_light = Entity.Find("light").Get<TransformComponent>().Matrix.Inverse;
        var projection_light = Entity.Find("projector_light").Get<ProjectorComponent>().ProjectionMatrix;
        var light_direction = -Entity.Find("light").Get<TransformComponent>().Forward;

        VertexShader.SetConstantBuffer(world * viewing * projection, 0);
        VertexShader.SetConstantBuffer(world * viewing_light * projection_light, 1);
        PixelShader1.SetConstantBuffer(world, 0);
        PixelShader1.SetConstantBuffer(Color, 1);
        PixelShader1.SetConstantBuffer(new Vector4(light_direction, 0), 2);
        PixelShader1.SetTexture(Program.DepthMap, 1);
        PixelShader1.SetSamplerState(SamplerState0, 0);
        PixelShader1.SetSamplerState(SamplerState1, 1);

        context.DrawIndexed(GraphicsModel.VertexIndices.Count);
    }
}
