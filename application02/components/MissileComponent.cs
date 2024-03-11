using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class MissileComponent : CustomEntityComponent
{
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();
    static GraphicsModel GraphicsModel = new GraphicsModel();

    //const float Weight = 50.0f;
    const float Weight = 20.0f;
    //const float InertiaMoment = 5.0f;
    const float InertiaMoment = 2.0f;
    const float Thrust = 30.0f;
    const float CountSpeed = 0.001f;
    const float TimeToIgnition = 0.0f;
    const float TurningPerformance = 0.025f; // 0.004f;
    const float SeekerAngleRange = 30.0f;
    const float SeekerDistanceRange = 1500.0f;
    const float SeekerSpeed = 0.0075f;
    const float LockableAngleRange = 45.0f;
    const float LockableDistanceRange = 3000.0f;
    const float DestructivePower = 0.5f;
    public Vector3 EngineNozzlePos { get; private set; } = new Vector3(0, 0, -1.770481f);

    public Entity TargetEntity { get; set; }
    public bool Locking { get; private set; }
    public bool Seeking { get; private set; }
    public bool Launched { get; private set; }
    public bool Division { get; private set; }
    public Matrix3x3 SeekerAngle { get; private set; } = new Matrix3x3().Identity();

    readonly Entity From;
    readonly bool FromPlayer;
    float timer = 0;

    static MissileComponent()
    {
        VertexShader.CreateFromFile("res/shader/MissileVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/MissilePixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("NORMAL", 0, Format.Float3, 1, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 2, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        GraphicsModel.CreateFromCX("res/mesh/missile/missile.cx");
    }

    public MissileComponent(Entity lauchedSourceEntity)
    {
        this.From = lauchedSourceEntity;
        this.FromPlayer = lauchedSourceEntity.Name == "player";
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

            case KillMessage:
                if (this.TargetEntity == argument)
                {
                    this.ResetTarget();
                }
                break;

            default:
                break;
        }
    }

    protected override void OnAttach()
    {
        base.OnAttach();
        this.Physics.Mass = Weight;
        this.Physics.InertiaMoment = InertiaMoment;
    }

    private void Update()
    {
        if (this.TargetEntity == null)
        {
            this.Seeking = false;
            this.Locking = false;
        }

        if (this.Launched)
        {
            if (this.timer > TimeToIgnition)
            {
                if (this.Owner.Has<GravityObjectComponent>())
                    this.Owner.Detach<GravityObjectComponent>();

                // 前進移動
                this.Physics.Force += this.Transform.Forward * Thrust;

                #region コンポーネント取り付け
                {
                    if (!this.Owner.Has<JetComponent>())
                        this.Owner.Attach<JetComponent>().OffsetPosition = this.EngineNozzlePos;

                    if (!this.Owner.Has<MissileSmokeComponent>())
                        this.Owner.Attach<MissileSmokeComponent>();

                    if (!this.Owner.Has<CollisionComponent>())
                    {
                        this.Owner.Attach(new CollisionComponent()
                        {
                            Object = new SphereCollisionObject(new Sphere() { Radius = 1.0f }),
                            Group = CollisionGroupMissile,
                            OtherGroups = CollisionGroupAircraft | CollisionGroupGround,
                            Excludes = new CollisionComponent[] { this.From.Get<CollisionComponent>() }
                        });
                        this.Owner.Get<CollisionComponent>().Collided += this.Collided;
                    }
                }
                #endregion

                #region ミサイル回転
                {
                    if (this.Locking)
                    {
                        var transform2 = this.TargetEntity.Get<TransformComponent>();
                        var physics2 = this.TargetEntity.Get<PhysicsComponent>();

                        Vector3 forward = this.Transform.Forward;
                        Vector3 relativeVector = transform2.Position - this.Transform.Position;
                        Vector3 relativeVelocity = physics2.Velocity - this.Physics.Velocity;

                        var angle = Vector3.Angle(forward, relativeVector);
                        if (angle < deg2rad(LockableAngleRange) && relativeVector.Magnitude < LockableDistanceRange)
                        //if (true)
                        {
                            float distance = relativeVector.Magnitude;
                            float access_time = distance / relativeVelocity.Magnitude;
                            if (relativeVelocity.Magnitude > 0)
                            {
                                access_time = 0;
                            }
                            //const float gain = 0.02f;
                            //const float intermediate_distance = 1000f;
                            //float look_ahead_rate = 1.0f / (1.0f + exp(gain * (distance - intermediate_distance)));
                            //Vector3 interceptPoint = transform2.Position + physics2.Velocity * access_time * look_ahead_rate;
                            Vector3 torque = Vector3.Outer(forward, (transform2.Position - this.Transform.Position).Normalize());
                            torque.Normalize();
                            torque *= TurningPerformance;
                            this.Physics.Torque += torque;
                        }
                        else
                        {
                            if (this.FromPlayer)
                            {
                                var player = Entity.Find("player");
                                if (player != null)
                                {
                                    Entity.SendMessage(player, "notice", "Miss");
                                }
                            }
                            this.Locking = false;
                            this.TargetEntity = null;
                        }
                    }
                }
                #endregion
            }
            else
            {
                if (!this.Owner.Has<GravityObjectComponent>())
                    this.Owner.Attach<GravityObjectComponent>();

                // 重力移動
                //Physics.Force = new Vector3(0, -Weight * Gravity * 10, 0);
            }

            #region 分裂多弾頭ミサイル発射
            {
                if (this.timer > 0.2f && this.Division)
                {
                    for (int i = 0; i < 16; i++)
                    {
                        Entity e = Entity.Instantiate();
                        e.Attach(new TransformComponent());
                        e.Attach(new PhysicsComponent());
                        e.Attach(new MissileComponent(this.Owner)
                        {
                            Division = false,
                            TargetEntity = this.TargetEntity,
                            Launched = true,
                            Locking = this.Locking,
                            timer = TimeToIgnition
                        });
                        e.Get<TransformComponent>().Matrix = this.Owner.Get<TransformComponent>().Matrix;
                        Vector3 axis = new Vector3(uniform(-1.0f, 1.0f), uniform(-1.0f, 1.0f), uniform(-1.0f, 1.0f)).Normalize();
                        float angle = normal(0.3f, 0.8f);
                        e.Get<TransformComponent>().Matrix.RotateAroundAxis(axis, angle);
                        e.Get<PhysicsComponent>().Force = this.Owner.Get<PhysicsComponent>().Force;
                        e.Get<PhysicsComponent>().Velocity = this.Owner.Get<PhysicsComponent>().Velocity;
                    }

                    this.Division = false;
                }
            }
            #endregion

            this.timer += CountSpeed;
        }
        else
        {
            #region ミサイルロックオン
            {
                if (this.TargetEntity != null)
                {
                    var transform2 = this.TargetEntity.Get<TransformComponent>();
                    var targetPosition = transform2.Position * this.Transform.Matrix.Inverse;

                    this.Seeking = Vector3.Angle(new Vector3(0, 0, 1), targetPosition) < deg2rad(SeekerAngleRange) && targetPosition.Z < SeekerDistanceRange;
                    if (this.Seeking)
                    {
                        if (this.Locking)
                        {
                            this.SeekerAngle = aim(this.SeekerAngle, targetPosition);
                        }
                        else
                        {
                            Vector3 forward = new Vector3();
                            forward.X = this.SeekerAngle.M31;
                            forward.Y = this.SeekerAngle.M32;
                            forward.Z = this.SeekerAngle.M33;
                            this.SeekerAngle = aim(this.SeekerAngle, targetPosition, SeekerSpeed);
                            if (Vector3.Angle(forward, targetPosition) < deg2rad(1.0f))
                                this.Locking = true;
                        }
                    }
                    else
                    {
                        this.Locking = false;
                        this.SeekerAngle = aim(this.SeekerAngle, new Vector3(0, 0, 1), SeekerSpeed);
                    }
                }
            }
            #endregion
        }

        #region 効果時間切れミサイル消去
        {
            if (1 < this.timer)
            {
                var e = Entity.Instantiate();
                e.Attach(this.Owner.Detach<MissileSmokeComponent>());

                Entity.Kill(this.Owner);
            }
        }
        #endregion

        #region MyRegion

        #endregion
    }

    public void Launch()
    {
        this.Launched = true;
        this.Division = false;
    }

    public void ResetTarget()
    {
        this.TargetEntity = null;
        this.Locking = false;
        this.Seeking = false;
    }

    private void Collided(Entity other, Vector3 point)
    {
        {
            Entity e = Entity.Instantiate();
            e.Attach<TransformComponent>().Position = point;
            e.Attach<ExplosionComponent>();
            // MissileSmokeComponent にて一定時間後に自動消滅
        }

        {
            Entity e = Entity.Instantiate();
            e.Attach(this.Owner.Detach<MissileSmokeComponent>());
            // MissileSmokeComponent にて一定時間後に自動消滅
        }

        {
            Entity e = Entity.Instantiate();
            e.Attach(new TransformComponent() { Position = point });
            e.Attach(new SoundComponent(ExplosionSound, true));
            e.Attach(new LimitedLifeTimeComponent() { CountSpeed = 0.001f });
        }

        if (other.Has<AircraftComponent>())
        {
            var physics = other.Get<PhysicsComponent>();
            var aircraft = other.Get<AircraftComponent>();

            // 機体に衝撃力を作用させる
            {
                Vector3 velocity = this.Physics.Velocity;
                Vector3 torque = Vector3.Outer(physics.Velocity, velocity);
                physics.Force += velocity * 5;
                physics.Torque += torque * 0.02f;
                physics.Velocity = physics.Velocity * 0.8f;
            }

            // 機体にダメージを与える
            aircraft.TakeDamage(DestructivePower);

            // HUD 通知処理
            var player = Entity.Find("player");
            if (player != null)
            {
                if (this.FromPlayer)
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

        Entity.Kill(this.Owner);
    }

    private static Matrix3x3 aim(Matrix3x3 angle, Vector3 point)
    {
        return new Matrix4x3().LookAt(Vector3.Zero, point)._Matrix3x3;
    }

    private static Matrix3x3 aim(Matrix3x3 angle, Vector3 direction, float speed)
    {
        Vector3 forward = new Vector3();
        forward.X = angle.M31;
        forward.Y = angle.M32;
        forward.Z = angle.M33;

        float theta = Vector3.Angle(direction, forward);
        if (abs(theta) > speed)
        {
            Vector3 axis = Vector3.Outer(direction, forward);
            angle.Transform(new Matrix3x3(new Quaternion(axis.Normalize(), -speed)));
        }
        else
        {
            angle = new Matrix4x3().LookAt(Vector3.Zero, direction)._Matrix3x3;
        }
        return angle;
    }

    private void Render()
    {
        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(NoBlend);
        device.SetRasterizerState(CullingOff);
        device.SetDepthStencilState(ZTestOn);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(GraphicsModel.Texture, 0);

        {
            VertexShader.SetConstantBuffer(this.WVPMatrix, 0);
            PixelShader.SetConstantBuffer(this.WorldMatrix, 0);
            PixelShader.SetConstantBuffer(new Vector4(Entity.Find("light").Get<TransformComponent>().Forward, 0), 1);

            device.SetVertexBuffer(GraphicsModel.VertexPositions, 0);
            device.SetVertexBuffer(GraphicsModel.VertexNormals, 1);
            device.SetVertexBuffer(GraphicsModel.VertexTextureCoords, 2);
            device.SetIndexBuffer(GraphicsModel.VertexIndices);
            device.DrawIndexed(GraphicsModel.VertexIndices.Count);
        }
    }
}
