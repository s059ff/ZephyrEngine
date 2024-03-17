using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;
using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class AircraftComponent : CustomEntityComponent
{
    public class AircraftParameter
    {
        public string Name;
        public float Weight;
        public float InertiaMoment;
        public float Thrust;
        public Vector3 EngineNozzlePos;
        public Vector3 CanardPos;
        public Vector3 ElevatorPos;
        public Vector3 WeaponPos0;
        public Vector3 WeaponPos1;
        public Vector3 WeaponPos2;
        public Vector3 WeaponPos3;
        public Vector3 WingEdgePos;
        public Vector3 CockpitPos;
        public Vector3 GunPos;
        public Texture2D Texture;
        public Texture2D NormalMapTexture;
        public GraphicsModel Body;
        public GraphicsModel LeftCanard;
        public GraphicsModel RightCanard;
        public GraphicsModel LeftElevator;
        public GraphicsModel RightElevator;
    }

    class WeaponSystem
    {
        public float ReloadTime = 1.0f;
        public Vector3 WeaponPos;
        public Entity MissileEntity;
    }

    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();
    static List<AircraftParameter> AircraftParameters = new List<AircraftParameter>();

    public const float Radius = 5.0f;
    public const int WeaponCount = 4;
    private const float MissileReloadSpeed = 1.0f / 1800;
    private const float GunReloadSpeed = 0.25f;
    private const float EnginePowerThreshold = 0.9f;

    public readonly AircraftParameter Parameter;
    private readonly Entity LeftSmokeGeneratorEntity;
    private readonly Entity RightSmokeGeneratorEntity;
    private readonly WeaponSystem[] Weapons = new WeaponSystem[WeaponCount];

    public MissileComponent ActiveMissile
    {
        get
        {
            return this.Weapons[this.NextUseWeapon].MissileEntity?.Get<MissileComponent>();
        }
    }
    public float[] ReloadTimes
    {
        get
        {
            return this.Weapons.Select(w => w.ReloadTime).ToArray();
        }
    }

    public float Armor { get; private set; } = 1.0f;
    public float Visibility { private get; set; } = 1.0f;
    public float EnginePower { get; private set; } = 0.5f;
    private float GunReloadTime = 0;
    private List<Entity> GunFlushs = new List<Entity>();
    private int NextUseWeapon = 0;

    public float ThrottleInput { get; set; }
    public float PitchInput { get; set; }
    public float RollInput { get; set; }
    public float YawInput { get; set; }
    public bool MissileLaunchInput { get; set; }
    public bool GunFireInput { get; set; }

    static AircraftComponent()
    {
        VertexShader.CreateFromFile("res/shader/AircraftVertexShader.hlsl");
        PixelShader.CreateFromFile("res/shader/AircraftPixelShader.hlsl");

        VertexLayout.Create(new VertexElement[]
        {
            new VertexElement("POSITION", 0, Format.Float3, 0, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("NORMAL", 0, Format.Float3, 1, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TEXCOORD", 0, Format.Float2, 2, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("TANGENT", 0, Format.Float3, 3, 0, VertexElement.Classification.VertexData, 0),
            new VertexElement("BINORMAL", 0, Format.Float3, 4, 0, VertexElement.Classification.VertexData, 0),
        }, VertexShader);

        using (var stream = new StreamReader("res/data/aircrafts.csv"))
        {
            const char separator = '\t';

            string[] headers = stream.ReadLine().Split(separator);
            FieldInfo[] fields = typeof(AircraftParameter).GetFields();
            assert(headers.All(header => fields.Select(f => f.Name).Contains(header)));

            while (!stream.EndOfStream)
            {
                AircraftParameter param = new AircraftParameter();
                {
                    string[] values = stream.ReadLine().Split(separator);
                    assert(headers.Count() == values.Count());

                    foreach (var tuple in headers.Zip(values, Tuple.Create))
                    {
                        var header = tuple.Item1;
                        var value = tuple.Item2;

                        var field = fields.Where(f => f.Name == header).First();
                        if (field != null)
                        {
                            object obj = null;
                            obj = (field.FieldType == typeof(string)) ? value : obj;
                            obj = (field.FieldType == typeof(float)) ? float.Parse(value) : obj;
                            obj = (field.FieldType == typeof(Vector3)) ? Vector3.Parse(value) : obj;
                            field.SetValue(param, obj);
                        }
                    }
                }

                param.Texture = new Texture2D();
                param.Texture.Create(string.Format("res/mesh/aircraft/{0}/{0}_P01.png", param.Name), Accessibility.None);

                param.NormalMapTexture = new Texture2D();
                param.NormalMapTexture.Create(string.Format("res/mesh/aircraft/{0}/{0}_N.png", param.Name), Accessibility.None);

                param.Body = new GraphicsModel();
                param.Body.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_Body.cx", param.Name));
                if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_LeftCanard.cx", param.Name)))
                {
                    param.LeftCanard = new GraphicsModel();
                    param.LeftCanard.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_LeftCanard.cx", param.Name));
                }
                if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_RightCanard.cx", param.Name)))
                {
                    param.RightCanard = new GraphicsModel();
                    param.RightCanard.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_RightCanard.cx", param.Name));
                }
                if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_LeftElevator.cx", param.Name)))
                {
                    param.LeftElevator = new GraphicsModel();
                    param.LeftElevator.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_LeftElevator.cx", param.Name));
                }
                if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_RightElevator.cx", param.Name)))
                {
                    param.RightElevator = new GraphicsModel();
                    param.RightElevator.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_RightElevator.cx", param.Name));
                }

                AircraftParameters.Add(param);
            }
        }
    }

    public AircraftComponent(string aircraftName)
    {
        Func<Vector3, Vector3> flip = (v) => new Vector3(-v.X, v.Y, v.Z);

        this.Parameter = AircraftParameters.Where((parameter) => parameter.Name == aircraftName).First();
        for (int i = 0; i < WeaponCount; i++)
        {
            this.Weapons[i] = new WeaponSystem();
            switch (i)
            {
                case 0:
                    this.Weapons[0].WeaponPos = this.Parameter.WeaponPos0;
                    break;
                case 1:
                    this.Weapons[1].WeaponPos = flip(this.Parameter.WeaponPos0);
                    break;
                case 2:
                    this.Weapons[2].WeaponPos = this.Parameter.WeaponPos1;
                    break;
                case 3:
                    this.Weapons[3].WeaponPos = flip(this.Parameter.WeaponPos1);
                    break;
                case 4:
                    this.Weapons[4].WeaponPos = this.Parameter.WeaponPos2;
                    break;
                case 5:
                    this.Weapons[5].WeaponPos = flip(this.Parameter.WeaponPos2);
                    break;
                case 6:
                    this.Weapons[6].WeaponPos = this.Parameter.WeaponPos3;
                    break;
                case 7:
                    this.Weapons[7].WeaponPos = flip(this.Parameter.WeaponPos3);
                    break;
            }
        }

        this.LeftSmokeGeneratorEntity = Entity.Instantiate();
        this.LeftSmokeGeneratorEntity.Attach(new TransformComponent());
        this.LeftSmokeGeneratorEntity.Attach(new StringySmokeComponent());

        this.RightSmokeGeneratorEntity = Entity.Instantiate();
        this.RightSmokeGeneratorEntity.Attach(new TransformComponent());
        this.RightSmokeGeneratorEntity.Attach(new StringySmokeComponent());
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
                if (this.Visibility == 1.0f)
                    this.Render();
                break;

            case TranslucentRenderMessage:
                if (this.Visibility < 1.0f)
                    this.Render();
                break;

            default:
                break;
        }
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        this.Collision.Object = new SphereCollisionObject(new Sphere() { Radius = AircraftComponent.Radius });
        this.Collision.Group = CollisionGroupAircraft;
        this.Collision.OtherGroups = CollisionGroupGround;
        this.Collision.Collided += this.Collided;
    }

    private void Collided(Entity other, Vector3 point)
    {
        if (other.Has<GroundComponent>())
        {
            this.TakeDamage(1.0f);
            this.Destroy();
        }
    }

    protected override void OnDestroy()
    {
        base.OnDestroy();
    }

    public void AutoPilot(Vector3 destination)
    {
        var p = destination * this.Transform.Matrix.Inverse;
        var z = Vector3.Angle(p, new Vector3(0, 0, 1));

        var y = Vector3.Angle(new Vector3(p.X, p.Y, 0), new Vector3(0, 1, 0));
        if ((deg2rad(20) < y) && (deg2rad(2) < z))
        {
            var power = clamp(y / 2, 0.2f, 1);
            this.RollInput = power * ((p.X > 0) ? 1 : -1);
            this.PitchInput = 0.0f;
            this.YawInput = 0.0f;
        }
        else
        {
            this.RollInput = 0.0f;
            this.YawInput = (p.X > 0) ? 1 : -1;

            if (deg2rad(5) < z)
            {
                var power = clamp(z * 6, 0.5f, 1);
                this.PitchInput = power * ((p.Y > 0) ? -1 : 1);
            }
            else
            {
                this.PitchInput = (p.Y > 0) ? -0.25f : 0.25f;
            }
        }
    }

    public void AutoPilot()
    {
        var avionics = this.Owner.Get<AircraftAvionicsComponent>();
        if (avionics == null)
            return;

        Vector3? threatMissilePosition = null;
        {
            float threatMissileDistance = float.MaxValue;
            bool isThreatMissileLaunched = false;
            Entity.ForEach(e =>
            {
                var missile = e.Get<MissileComponent>();
                if (missile != null && missile.TargetEntity == this.Owner && missile.Locking)
                {
                    Vector3 position = missile.Owner.Get<TransformComponent>().Position;
                    float distance = (this.Transform.Position - position).Magnitude;

                    // 発射前ミサイルよりも発射済みミサイルを優先する
                    if (distance < threatMissileDistance || !isThreatMissileLaunched)
                    {
                        threatMissilePosition = position;
                        threatMissileDistance = distance;
                        isThreatMissileLaunched = missile.Launched;
                    }
                }
            });
        }

        if (this.Transform.Position.Y < 1000)
        {
            // 高度が低い場合, 上昇する
            this.AutoPilot(new Vector3(this.Transform.Position.X, 2000, this.Transform.Position.Z));
        }
        else if (min(this.Transform.Position.X, this.Transform.Position.Z) < -8000 || max(this.Transform.Position.X, this.Transform.Position.Z) > +8000)
        {
            // 戦闘エリアからの離脱を防ぐ
            this.AutoPilot(new Vector3(0, 2000, 0));
        }
        else if (threatMissilePosition != null)
        {
            // ミサイルにロックされている場合, 回避行動を行う
            Vector3 n = (this.Transform.Position - (Vector3)threatMissilePosition).Normalize();
            Vector3 a = this.Transform.Forward;
            Vector3 b = Vector3.Inner(a, n) * n;
            Vector3 v = a - b;
            Vector3 destination = this.Transform.Position + v;
            this.AutoPilot(destination);

            // 確認用
            float angle = Vector3.Angle(v, n);
            assert(abs(angle - PIOver2) < 1e-2);
        }
        else if (avionics.HasTarget())
        {
            Vector3 destination = GunBulletComponent.ComputeOptimalAimPosition(this.Owner, avionics.TargetEntity);
            this.AutoPilot(destination);
        }
        else
        {
            // ターゲットがいない場合, 中心に移動する
            this.AutoPilot(new Vector3(0, 2000, 0));
        }
    }

    public void AutoAttack()
    {
        var avionics = this.Owner.Get<AircraftAvionicsComponent>();
        if (avionics == null)
            return;
        if (!avionics.HasTarget())
            return;

        #region 主兵装の操作
        {
            this.MissileLaunchInput = (this.ActiveMissile != null && this.ActiveMissile.Locking && uniform() < 0.001f);
        }
        #endregion

        #region 機関砲の操作
        {
            var viewing = this.ViewingMatrix;
            var projection = this.ProjectionMatrix;
            var time = GunBulletComponent.ComputeHitTime(this.Owner, avionics.TargetEntity);

            var p1 = new Vector3(0, 0, time * GunBulletComponent.BulletSpeed) * this.Transform.Matrix;
            var p2 = avionics.TargetEntity.Get<TransformComponent>().Position + time * avionics.TargetEntity.Get<PhysicsComponent>().Velocity;

            this.GunFireInput = ((p2 - p1).SquaredMagnitude < square(Radius));
        }
        #endregion
    }

    void Update()
    {
        this.ThrottleInput = clamp(this.ThrottleInput, -1.0f, 1.0f);
        this.PitchInput = clamp(this.PitchInput, -1.0f, 1.0f);
        this.RollInput = clamp(this.RollInput, -1.0f, 1.0f);
        this.YawInput = clamp(this.YawInput, -1.0f, 1.0f);

        #region アナログスティック入力を正規化
        {
            // ジョイスティックにおける axis.magnitude <= 1 の制約を, 他の入力方式 (キーボード, リモートコントロール) にも課す
            float x = this.RollInput;
            float y = this.PitchInput;
            float magnitude = (float)Math.Sqrt(x * x + y * y);
            if (1.0f < magnitude)
            {
                this.RollInput /= magnitude;
                this.PitchInput /= magnitude;
            }
        }
        #endregion

        #region エンジン推力による前進
        {
            this.EnginePower = clamp(this.EnginePower + 0.004f * this.ThrottleInput, 0.25f, 1.0f);
            this.Physics.Mass = this.Parameter.Weight;
            this.Physics.InertiaMoment = this.Parameter.InertiaMoment;
            this.Physics.Force += this.Transform.Forward * (this.Parameter.Thrust * this.EnginePower * max(1.0f, (this.EnginePower - EnginePowerThreshold) * 10.0f * 1.5f));
        }
        #endregion

        #region エンジン動作による振動
        {
            float vibrationScale = max(0.8f / (1.0f - EnginePowerThreshold) * (this.EnginePower - EnginePowerThreshold) + 0.2f, 0.2f);
            float vx = normal(0.0f, vibrationScale);
            float vy = normal(0.0f, vibrationScale);
            float vz = normal(0.0f, vibrationScale);
            this.Physics.Force += new Vector3(vx, vy, vz);
        }
        #endregion

        #region ピッチ操作
        {
            float power = clamp(this.PitchInput, -1.0f, 1.0f);
            if (power > 0) power = 0.5f * power;
            float x = this.Physics.Velocity.Magnitude;
            float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
            this.Physics.Torque += this.Transform.Rightward * 0.003f * power * k;
        }
        #endregion

        #region ロール操作
        {
            float power = clamp(this.RollInput, -1.0f, 1.0f);
            float x = this.Physics.Velocity.Magnitude;
            float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
            this.Physics.Torque += this.Transform.Forward * -0.02f * power * k;
        }
        #endregion

        #region ヨー操作
        {
            float power = clamp(this.YawInput, -1.0f, 1.0f);
            float x = this.Physics.Velocity.Magnitude;
            float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
            this.Physics.Torque += this.Transform.Upward * 0.00075f * power * k;
        }
        #endregion

        #region ミサイルのリロード
        {
            foreach (var weapon in this.Weapons)
            {
                weapon.ReloadTime = close(weapon.ReloadTime, 1.0f, MissileReloadSpeed);

                if (weapon.ReloadTime >= 1.0f && weapon.MissileEntity == null)
                {
                    Entity e = Entity.Instantiate();
                    e.Attach(new TransformComponent());
                    e.Attach(new PhysicsComponent());
                    e.Attach(new MissileComponent(this.Owner));
                    weapon.MissileEntity = e;
                }
            }
        }
        #endregion

        #region 機関砲のリロード
        {
            this.GunReloadTime = close(this.GunReloadTime, 1.0f, GunReloadSpeed);
        }
        #endregion

        #region 主翼端の風切りエフェクト更新
        if (this.Armor > 0)
        {
            Func<Vector3, Vector3> flip = (v) => new Vector3(-v.X, v.Y, v.Z);

            this.LeftSmokeGeneratorEntity.Get<TransformComponent>().Matrix = this.Transform.Matrix;
            this.LeftSmokeGeneratorEntity.Get<TransformComponent>().Matrix.Translate(this.Parameter.WingEdgePos);
            this.LeftSmokeGeneratorEntity.Get<StringySmokeComponent>().Intensity = this.Physics.AngularVelocity.Magnitude * 60;

            this.RightSmokeGeneratorEntity.Get<TransformComponent>().Matrix = this.Transform.Matrix;
            this.RightSmokeGeneratorEntity.Get<TransformComponent>().Matrix.Translate(flip(this.Parameter.WingEdgePos));
            this.RightSmokeGeneratorEntity.Get<StringySmokeComponent>().Intensity = this.Physics.AngularVelocity.Magnitude * 60;
        }
        #endregion

        #region アフターバーナーのエフェクト更新
        {
            this.Owner.Get<JetComponent>().Power = this.EnginePower;
        }
        #endregion

        #region ダメージ表現のための煙と炎
        if (this.Armor <= 0.25f)
        {
            if (!this.Owner.Has<AircraftFlameComponent>())
                this.Owner.Attach<AircraftFlameComponent>();

            if (!this.Owner.Has<AircraftSmokeComponent>())
                this.Owner.Attach<AircraftSmokeComponent>();
        }
        else
        {
            if (this.Owner.Has<AircraftFlameComponent>())
                this.Owner.Detach<AircraftFlameComponent>();

            if (this.Owner.Has<AircraftSmokeComponent>())
                this.Owner.Detach<AircraftSmokeComponent>();
        }
        #endregion

        #region 耐久値がなくなったとき, 地上に落下
        if (this.Armor == 0)
        {
            this.PitchInput = 0.0f;
            this.RollInput = 0.0f;
            this.YawInput = 0.0f;
            this.ThrottleInput = 0.0f;
            this.MissileLaunchInput = false;
            this.GunFireInput = false;

            {
                Vector3 axis = new Vector3(this.Transform.Rightward.X, 0, this.Transform.Rightward.Z).Normalize();
                Vector3 torque = 0.001f * axis * (0 < this.Transform.Upward.Y ? 1.0f : -1.0f);
                this.Physics.Torque += torque;
            }

            {
                Vector3 axis = this.Transform.Forward;
                Vector3 torque = 0.05f * axis;
                this.Physics.Torque += torque;
            }
        }
        #endregion

        #region サウンドの設定
        {
            if (this.Owner.Has<SoundComponent>())
            {
                if (this.Owner.Name == "player")
                    this.Owner.Get<SoundComponent>().VolumeFactor = square(this.EnginePower);
                else
                    this.Owner.Get<SoundComponent>().VolumeFactor = 1.0f;
            }
        }
        #endregion

        #region ロックオンサウンドの設定
        {
            if (this.Owner.Name == "player")
            {
                if (this.ActiveMissile != null)
                {
                    if (this.ActiveMissile.Locking)
                    {
                        if (!LockonSound.Playing)
                            LockonSound.LoopPlay();
                    }
                    else
                    {
                        if (this.ActiveMissile.Seeking)
                        {
                            int frameCount = Entity.Find("system").Get<SystemComponent>().FrameCount;
                            if ((frameCount % 30) < 15)
                            {
                                if (!LockonSound.Playing)
                                    LockonSound.Play();
                            }
                            else
                                LockonSound.Stop();
                        }
                        else
                        {
                            LockonSound.Stop();
                        }
                    }
                }
                else
                {
                    LockonSound.Stop();
                }
            }
        }
        #endregion

        #region マズルフラッシュの座標の更新
        {
            foreach (var e in this.GunFlushs.Where(e => !e.IsAlive).ToArray())
            {
                this.GunFlushs.Remove(e);
            }
            foreach (var e in this.GunFlushs)
            {
                e.Get<TransformComponent>().Position = this.Transform.Position + this.Parameter.GunPos * this.Transform.Matrix._Matrix3x3;
            }
        }
        #endregion

        #region ミサイル操作
        if (this.MissileLaunchInput)
        {
            var weapon = this.Weapons[this.NextUseWeapon];
            if (weapon.ReloadTime == 1.0f)
            {
                weapon.MissileEntity.Get<MissileComponent>().Launch();
                weapon.MissileEntity.Attach(new SoundComponent(JetSound));
                weapon.MissileEntity.Get<SoundComponent>().LoopPlay();
                weapon.MissileEntity = null;
                weapon.ReloadTime = 0;

                this.NextUseWeapon = (this.NextUseWeapon + 1) % WeaponCount;
            }
        }
        #endregion

        #region 機銃発射
        if (this.GunFireInput)
        {
            if (this.GunReloadTime == 1)
            {
                {
                    Entity e = Entity.Instantiate();
                    e.Attach(new TransformComponent() { Matrix = this.Transform.Matrix });
                    e.Get<TransformComponent>().Position = this.Transform.Position + this.Parameter.GunPos * this.Transform.Matrix._Matrix3x3;
                    e.Get<TransformComponent>().Matrix.RotateAroundAxis(new Vector3(uniform(-1.0f, 1.0f), uniform(-1.0f, 1.0f), uniform(-1.0f, 1.0f)).Normalize(), normal(0, 0.005f));
                    e.Attach(new CollisionComponent()
                    {
                        Object = new PointCollisionObject(new Point()),
                        Group = CollisionGroupGunBullet,
                        OtherGroups = CollisionGroupAircraft | CollisionGroupGround,
                        Excludes = new CollisionComponent[] { this.Collision }
                    });
                    e.Attach(new GunBulletComponent(this.Owner));
                    e.Attach(new SoundComponent(BulletSound));
                    e.Get<SoundComponent>().VolumeFactor = 0.8f;
                    e.Get<SoundComponent>().Play();
                    e.Attach(new LimitedLifeTimeComponent()
                    {
                        CountSpeed = 0.01f
                    });
                }

                if (this.Visibility == 1.0f)
                {
                    Entity e = Entity.Instantiate();
                    e.Attach(new TransformComponent() { Matrix = this.Transform.Matrix });
                    e.Get<TransformComponent>().Position = this.Transform.Position + this.Parameter.GunPos * this.Transform.Matrix._Matrix3x3;
                    e.Attach<GunFlushComponent>();
                    e.Attach(new LimitedLifeTimeComponent()
                    {
                        CountSpeed = 0.2f
                    });
                    this.GunFlushs.Add(e);
                }
                this.GunReloadTime = 0f;
            }
        }
        #endregion
    }

    public void TakeDamage(float damage)
    {
        this.Armor = clamp(this.Armor - damage, 0.0f, 1.0f);

        if (this.Armor == 0)
        {
            if (!this.Owner.Has<TimerComponent>())
            {
                this.Owner.Attach(new TimerComponent() { CountSpeed = 0.001f });
                this.Owner.Get<TimerComponent>().Ticked += this.Destroy;
            }

            if (this.Owner.Has<AircraftAvionicsComponent>())
                this.Owner.Detach<AircraftAvionicsComponent>();
            if (this.Owner.Has<SquadronComponent>())
                this.Owner.Detach<SquadronComponent>();
            if (this.Owner.Has<PlayerPilotComponent>())
                this.Owner.Detach<PlayerPilotComponent>();
            if (this.Owner.Has<NonPlayerPilotComponent>())
                this.Owner.Detach<NonPlayerPilotComponent>();

            if (this.Owner.Name == "player")
            {
                var camera = Entity.Find("camera");
                camera.Get<FixedPointCameraComponent>()?.Activate();
            }
        }

        if (this.Owner.Has<EnvironmentObservationComponent>())
        {
            var observer = this.Owner.Get<EnvironmentObservationComponent>();
            observer.Player.TakenDamage += damage;
        }
    }

    void Render()
    {
        Func<Vector3, Vector3> flip = (v) => new Vector3(-v.X, v.Y, v.Z);

        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(this.Visibility == 1.0f ? NoBlend : AlphaBlend);
        device.SetRasterizerState(CullingOn);
        device.SetDepthStencilState(this.Visibility == 1.0f ? ZTestOn : ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(this.Parameter.Texture, 0);
        PixelShader.SetTexture(this.Parameter.NormalMapTexture, 1);

        PixelShader.SetConstantBuffer(new Vector4(Entity.Find("camera").Get<TransformComponent>().Position, 1), 2);
        PixelShader.SetConstantBuffer(new Vector4(Entity.Find("light").Get<TransformComponent>().Forward, 0), 3);
        PixelShader.SetConstantBuffer(new Color(1, 1, 1, this.Visibility), 4);

        {
            VertexShader.SetConstantBuffer(this.WVPMatrix, 0);
            PixelShader.SetConstantBuffer(this.WorldMatrix, 0);
            PixelShader.SetConstantBuffer(this.WorldMatrix.Inverse, 1);

            device.SetVertexBuffer(this.Parameter.Body.VertexPositions, 0);
            device.SetVertexBuffer(this.Parameter.Body.VertexNormals, 1);
            device.SetVertexBuffer(this.Parameter.Body.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.Parameter.Body.VertexTangents, 3);
            device.SetVertexBuffer(this.Parameter.Body.VertexBinormals, 4);
            device.SetIndexBuffer(this.Parameter.Body.VertexIndices);
            device.DrawIndexed(this.Parameter.Body.VertexIndices.Count);
        }

        var angular = new Vector4(this.Physics.AngularVelocity, 0) * this.Transform.Matrix.Inverse;

        if (this.Parameter.LeftCanard != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(this.Parameter.CanardPos);
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp(angular.X * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * this.WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * this.WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * this.WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.Parameter.LeftCanard.VertexPositions, 0);
            device.SetVertexBuffer(this.Parameter.LeftCanard.VertexNormals, 1);
            device.SetVertexBuffer(this.Parameter.LeftCanard.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.Parameter.LeftCanard.VertexTangents, 3);
            device.SetVertexBuffer(this.Parameter.LeftCanard.VertexBinormals, 4);
            device.SetIndexBuffer(this.Parameter.LeftCanard.VertexIndices);
            device.DrawIndexed(this.Parameter.LeftCanard.VertexIndices.Count);
        }

        if (this.Parameter.RightCanard != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(flip(this.Parameter.CanardPos));
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp(angular.X * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * this.WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * this.WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * this.WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.Parameter.RightCanard.VertexPositions, 0);
            device.SetVertexBuffer(this.Parameter.RightCanard.VertexNormals, 1);
            device.SetVertexBuffer(this.Parameter.RightCanard.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.Parameter.RightCanard.VertexTangents, 3);
            device.SetVertexBuffer(this.Parameter.RightCanard.VertexBinormals, 4);
            device.SetIndexBuffer(this.Parameter.RightCanard.VertexIndices);
            device.DrawIndexed(this.Parameter.RightCanard.VertexIndices.Count);
        }

        if (this.Parameter.LeftElevator != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(this.Parameter.ElevatorPos);
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp((-angular.X * 2 + angular.Z * 0.5f) * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * this.WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * this.WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * this.WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.Parameter.LeftElevator.VertexPositions, 0);
            device.SetVertexBuffer(this.Parameter.LeftElevator.VertexNormals, 1);
            device.SetVertexBuffer(this.Parameter.LeftElevator.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.Parameter.LeftElevator.VertexTangents, 3);
            device.SetVertexBuffer(this.Parameter.LeftElevator.VertexBinormals, 4);
            device.SetIndexBuffer(this.Parameter.LeftElevator.VertexIndices);
            device.DrawIndexed(this.Parameter.LeftElevator.VertexIndices.Count);
        }

        if (this.Parameter.RightElevator != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(flip(this.Parameter.ElevatorPos));
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp((-angular.X * 2 - angular.Z * 0.5f) * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * this.WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * this.WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * this.WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.Parameter.RightElevator.VertexPositions, 0);
            device.SetVertexBuffer(this.Parameter.RightElevator.VertexNormals, 1);
            device.SetVertexBuffer(this.Parameter.RightElevator.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.Parameter.RightElevator.VertexTangents, 3);
            device.SetVertexBuffer(this.Parameter.RightElevator.VertexBinormals, 4);
            device.SetIndexBuffer(this.Parameter.RightElevator.VertexIndices);
            device.DrawIndexed(this.Parameter.RightElevator.VertexIndices.Count);
        }

        #region ミサイル更新
        for (int i = 0; i < WeaponCount; i++)
        {
            if (this.Weapons[i].MissileEntity != null)
            {
                Entity e = this.Weapons[i].MissileEntity;
                e.Get<TransformComponent>().Matrix = this.Transform.Matrix;
                e.Get<TransformComponent>().Matrix.Translate(this.Weapons[i].WeaponPos);
                e.Get<PhysicsComponent>().Velocity = this.Physics.Velocity;
                e.Get<MissileComponent>().TargetEntity = (this.Owner.Has<AircraftAvionicsComponent>()) ? this.Owner.Get<AircraftAvionicsComponent>().TargetEntity : null;
            }
        }
        #endregion
    }

    void Destroy()
    {
        for (int i = 0; i < 16; i++)
        {
            Entity e = Entity.Instantiate();
            e.Attach(new TransformComponent()
            {
                Position = this.Transform.Position
            });
            e.Attach(new PhysicsComponent()
            {
                Mass = this.Physics.Mass,
                InertiaMoment = this.Physics.InertiaMoment,
                Force = new Vector3(normal(0, 1), normal(0, 1), normal(0, 1)).Normalize() * 100
            });
            e.Attach(new CollisionComponent()
            {
                Group = CollisionGroupNone,
                OtherGroups = CollisionGroupGround,
                Object = new SphereCollisionObject(new Sphere() { Radius = 5.0f })
            });
            e.Get<CollisionComponent>().Collided += (_, __) => { Entity.Kill(e); };
            e.Attach<GravityObjectComponent>();
            e.Attach<AircraftSmokeComponent>();
            e.Attach<AircraftFlameComponent>();
            e.Attach(new LimitedLifeTimeComponent() { CountSpeed = 0.01f });
        }

        {
            Entity e = Entity.Instantiate();
            e.Name = string.Format("{0}_{1}", this.Owner.Name, "residue");
            e.Attach(new TransformComponent() { Position = this.Transform.Position });
            e.Attach(new SoundComponent(LargeExplosionSound, true));
            e.Attach(new LimitedLifeTimeComponent() { CountSpeed = 0.005f });
        }

        foreach (var weapon in this.Weapons)
        {
            if (weapon.MissileEntity != null)
                Entity.Kill(weapon.MissileEntity);
        }

        Entity.BroadcastMessage(KillMessage, this.Owner);
        Entity.Kill(this.Owner);
    }
}
