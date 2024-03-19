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
    static VertexBuffer<Vector3> VertexPositions = new VertexBuffer<Vector3>();
    static VertexBuffer<Vector4> VertexColors = new VertexBuffer<Vector4>();

    public const float BulletSpeed = 40.0f;
    const float DestructivePower = 0.05f;
    readonly bool FromPlayer;

    static GunBulletComponent()
    {
        VertexShader.CreateFromFile("res/shader/GunBulletVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/GunBulletPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("COLOR", 0, Format.Float4, 1, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        VertexPositions.Create(
            new Vector3[]
            {
                new Vector3(0.0f, 0.0f, 0.0f),
                new Vector3(0.0f, 0.0f, -BulletSpeed),
            },
            Accessibility.None
        );
        VertexColors.Create(
            new Vector4[]
            {
                new Vector4(1.0f, 1.0f, 0.0f, 1.0f),
                new Vector4(0.0f, 0.0f, 0.0f, 0.0f),
            },
            Accessibility.None
        );
    }

    public static Vector3 ComputeOptimalAimPosition(Entity myself, Entity target)
    {
        var vt = target.Get<PhysicsComponent>().Velocity;
        var vb = BulletSpeed;
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
        var vb = BulletSpeed;
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
        this.FromPlayer = launchedSourceEntity.Name == "player";
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
        this.Collision.Collided += this.Collided;
        this.Collision.Object.Velocity = this.Transform.Forward * BulletSpeed;
    }

    private void Collided(Entity other, Vector3 point)
    {
        // エフェクトを発生させる
        Entity e = Entity.Instantiate();
        e.Attach(new TransformComponent() { Position = point });
        e.Attach(new LimitedLifeTimeComponent() { CountSpeed = 0.04f });
        e.Attach(new SoundComponent(BulletHitSound) { VolumeFactor = 0.5f });
        e.Get<SoundComponent>().Play();

        if (other.Has<AircraftComponent>())
        {
            var aircraft = other.Get<AircraftComponent>();

            // 機体にダメージを与える
            {
                aircraft.TakeDamage(DestructivePower);
            }

            // HUD 通知処理
            var player = Entity.Find("player");
            if (player != null)
            {
                if (this.FromPlayer)
                {
                    Entity.SendMessage(player, "notice", (aircraft.Armor > 0) ? "Hit" : "Destroyed");

                    if (player.Has<EnvironmentObservationComponent>())
                    {
                        var observer = player.Get<EnvironmentObservationComponent>();
                        observer.Player.InflictedDamage += DestructivePower;
                    }
                }
                if (other.Name == "player")
                {
                    Entity.SendMessage(player, "notice", "Damaged");
                }
            }

            // 火花エフェクト
            e.Attach(new GunBulletSparkComponent());
        }
        else if (other.Has<GroundComponent>())
        {
            // 地面に衝突したときのみ, 煙エフェクトを発生させる
            e.Attach(new GunBulletSmokeComponent());
        }
        Entity.Kill(this.Owner);
    }

    private void Update()
    {
        this.Transform.Position += this.Transform.Forward * BulletSpeed;
        this.Collision.Object.Velocity = this.Transform.Forward * BulletSpeed;
    }

    private void Render()
    {
        VertexShader.SetConstantBuffer(this.Transform.Matrix * this.ViewingMatrix * this.ProjectionMatrix, 0);

        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(Addition);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.LineList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);
        device.SetVertexBuffer(VertexPositions, 0);
        device.SetVertexBuffer(VertexColors, 1);
        device.Draw(2);
    }
}
