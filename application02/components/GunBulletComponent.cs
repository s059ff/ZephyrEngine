using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class GunBulletComponent : CustomEntityComponent
{
    static VertexLayout VertexLayout = new VertexLayout();
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexBuffer<uint> VertexPositions = new VertexBuffer<uint>();

    public const float BulletSpeed = 40.0f;
    float Damage = 0.05f;
    readonly bool ShootedByPlayer;

    static GunBulletComponent()
    {
        VertexShader.CreateFromFile("res/shader/GunBulletVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/GunBulletPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("INDEX", 0, Format.SInt1, 0, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        VertexPositions.Create(new uint[2] { 0, 1 }, Accessibility.None);
    }

    public static Vector3 ComputeOptimalAimPosition(Entity myself, Entity target)
    {
        var vt = target.Get<PhysicsComponent>().Velocity;
        var vb = GunBulletComponent.BulletSpeed;
        var pt = target.Get<TransformComponent>().Position - myself.Get<TransformComponent>().Position;
        var a = (vt.X * vt.X + vt.Y * vt.Y + vt.Z * vt.Z - vb * vb);

        var b = (pt.X * vt.X + pt.Y * vt.Y + pt.Z * vt.Z);
        var c = (pt.X * pt.X + pt.Y * pt.Y + pt.Z * pt.Z);
        var t = (-b - sqrt(b * b - a * c)) / a;
        assert(t >= 0);

        Vector3 destination = target.Get<TransformComponent>().Position + t * target.Get<PhysicsComponent>().Velocity;
        return destination;
    }

    public static float ComputeHitTime(Entity myself, Entity target)
    {
        var vt = target.Get<PhysicsComponent>().Velocity;
        var vb = GunBulletComponent.BulletSpeed;
        var pt = target.Get<TransformComponent>().Position - myself.Get<TransformComponent>().Position;
        var a = (vt.X * vt.X + vt.Y * vt.Y + vt.Z * vt.Z - vb * vb);

        var b = (pt.X * vt.X + pt.Y * vt.Y + pt.Z * vt.Z);
        var c = (pt.X * pt.X + pt.Y * pt.Y + pt.Z * pt.Z);
        var t = (-b - sqrt(b * b - a * c)) / a;
        assert(t >= 0);

        return t;
    }

    public GunBulletComponent(Entity launchedSourceEntity)
    {
        this.ShootedByPlayer = launchedSourceEntity.Name == "player";
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
                this.Render();
                break;

            default:
                break;
        }
    }

    protected override void OnAttach()
    {
        base.OnAttach();
        Collision.Collided += Collided;
        Collision.Object.Velocity = Transform.Forward * BulletSpeed;
    }

    private void Collided(Entity other, Vector3 point)
    {
        if (other.Has<AircraftComponent>())
        {
            Entity e = Entity.Instantiate();
            e.Attach(new TransformComponent() { Position = point });
            //e.Attach<GunBulletSmokeComponent>();
            e.Attach(new LimitedLifeTimeComponent()
            {
                CountSpeed = 0.04f
            });
            var soundComponent = new SoundComponent(BulletHitSound);
            soundComponent.VolumeFactor = 0.5f;
            e.Attach(soundComponent);
            soundComponent.Play();

            var aircraft = other.Get<AircraftComponent>();
            aircraft.Damage(Damage);

            var player = Entity.Find("player");
            if (player != null)
            {
                if (this.ShootedByPlayer)
                {
                    if (aircraft.Armor > 0)
                        Entity.SendMessage(player, "notice", "Hit");
                    else
                        Entity.SendMessage(player, "notice", "Destroyed");
                }
                if (other.Name == "player")
                    Entity.SendMessage(Entity.Find("player"), "notice", "Damaged");
            }
        }
        else if (other.Has<GroundComponent>())
        {
            Entity e = Entity.Instantiate();
            e.Attach(new TransformComponent() { Position = point });
            e.Attach<GunBulletSmokeComponent>();
            e.Attach(new LimitedLifeTimeComponent()
            {
                CountSpeed = 0.04f
            });
            var soundComponent = new SoundComponent(BulletHitSound);
            soundComponent.VolumeFactor = 0.5f;
            e.Attach(soundComponent);
            soundComponent.Play();
        }
        Entity.Kill(this.Owner);
    }

    private void Update()
    {
        Transform.Position += Transform.Forward * BulletSpeed;
        Collision.Object.Velocity = Transform.Forward * BulletSpeed;
    }

    private void Render()
    {
        VertexShader.SetConstantBuffer(ViewingMatrix * ProjectionMatrix, 0);
        VertexShader.SetConstantBuffer(new Vector4[] { new Vector4(Transform.Position, 1), new Vector4(Transform.Position - Transform.Forward * BulletSpeed, 1) }, 1);

        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.LineList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);
        device.SetVertexBuffer(VertexPositions, 0);
        device.Draw(2);
    }
}
