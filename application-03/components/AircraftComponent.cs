using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using CsvHelper;
using CsvHelper.Configuration;
using ZephyrSharp.Collision;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class AircraftComponent : CustomEntityComponent
{
    static VertexShader VertexShader = new VertexShader();
    static PixelShader PixelShader = new PixelShader();
    static VertexLayout VertexLayout = new VertexLayout();

    const float ReloadSpeed = 0.01f;
    const float GunReloadSpeed = 0.15f;
    public const float Radius = 5.0f;

    public readonly string Name;
    readonly float Weight;
    readonly float InertiaMoment;
    readonly float Thrust;
    readonly Vector3 CanardPos;
    readonly Vector3 ElevatorPos;
    readonly Vector3 EdgePos;
    public readonly Vector3 CockpitPos;
    readonly Vector3 JetPos;
    readonly Vector3 GunPos;
    readonly GraphicsModel Body = new GraphicsModel();
    readonly GraphicsModel LeftCanard = null;
    readonly GraphicsModel RightCanard = null;
    readonly GraphicsModel LeftElevator = null;
    readonly GraphicsModel RightElevator = null;
    readonly Texture2D Texture = new Texture2D();
    readonly Texture2D NormalMapTexture = new Texture2D();
    readonly Entity LeftSmokeGeneratorEntity;
    readonly Entity RightSmokeGeneratorEntity;
    readonly Weapon[] Weapons = new Weapon[8];

    public MissileComponent ActiveMissile
    {
        get
        {
            var entity = this.Weapons[this.NextUseWeapon].MissileEntity;
            if (entity != null)
                return entity.Get<MissileComponent>();
            else
                return null;
        }
    }
    public bool Locking { get { return (ActiveMissile != null) && (ActiveMissile.Locking); } }
    public float[] ReloadTimes { get { return this.Weapons.Select(w => w.ReloadTime).ToArray(); } }
    public float DesiredPower { get; set; } = 0.5f;
    public float Armor { get; set; } = 1.0f;
    public bool Firing { private get; set; } = false;

    public bool Visible = true;
    public float Opacity = 0;

    float Power = 0.5f;
    float Stability = 1.0f;
    float GunReloadTime = 0;
    List<Entity> GunFlushs = new List<Entity>();

    class Weapon
    {
        public float ReloadTime;
        public Vector3 WeaponPos;
        public Entity MissileEntity;
    }
    int NextUseWeapon = 0;

    public class AircraftSettings
    {
        public string Name;
        public float Weight;
        public float InertiaMoment;
        public float Thrust;
        public Vector3 JetPos;
        public Vector3 CanardPos;
        public Vector3 ElevatorPos;
        public Vector3 WeaponPos0;
        public Vector3 WeaponPos1;
        public Vector3 WeaponPos2;
        public Vector3 WeaponPos3;
        public Vector3 EdgePos;
        public Vector3 CockpitPos;
        public Vector3 GunPos;
    }

    public class CsvVector3Converter : CsvHelper.TypeConversion.DateTimeConverter
    {
        public override object ConvertFromString(string text, IReaderRow row, MemberMapData memberMapData)
        {
            return Vector3.Parse(text);
        }
    }

    public sealed class AircraftSettingsMap : CsvHelper.Configuration.ClassMap<AircraftSettings>
    {
        public AircraftSettingsMap()
        {
            Map(x => x.Name).Index(0);
            Map(x => x.Weight).Index(1);
            Map(x => x.InertiaMoment).Index(2);
            Map(x => x.Thrust).Index(3);
            Map(x => x.JetPos).Index(4).TypeConverter<CsvVector3Converter>();
            Map(x => x.CanardPos).Index(5).TypeConverter<CsvVector3Converter>();
            Map(x => x.ElevatorPos).Index(6).TypeConverter<CsvVector3Converter>();
            Map(x => x.WeaponPos0).Index(7).TypeConverter<CsvVector3Converter>();
            Map(x => x.WeaponPos1).Index(8).TypeConverter<CsvVector3Converter>();
            Map(x => x.WeaponPos2).Index(9).TypeConverter<CsvVector3Converter>();
            Map(x => x.WeaponPos3).Index(10).TypeConverter<CsvVector3Converter>();
            Map(x => x.EdgePos).Index(11).TypeConverter<CsvVector3Converter>();
            Map(x => x.CockpitPos).Index(12).TypeConverter<CsvVector3Converter>();
            Map(x => x.GunPos).Index(13).TypeConverter<CsvVector3Converter>();
        }
    }

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

        //var table = CsvParserExtensions.Parse("res/data/aircrafts.csv", '\t');

        //foreach (var model in table)
        //{
        //    ResourceManager.Register(model["Name"], (name) =>
        //    {
        //        return new AircraftComponent(model);
        //    });
        //}
    }

    public AircraftComponent()
    {
        AircraftSettings settings = null;

        using (var csv = new CsvHelper.CsvReader(new StreamReader("res/data/aircrafts.csv")))
        {
            csv.Configuration.HasHeaderRecord = true;
            csv.Configuration.RegisterClassMap<AircraftSettingsMap>();
            csv.Configuration.Delimiter = "\t";
            var records = csv.GetRecords<AircraftSettings>();
            foreach (var record in records)
            {
                settings = record;
            }
        }

        this.Name = settings.Name.Replace(' ', '_');
        this.Weight = settings.Weight;
        this.InertiaMoment = settings.InertiaMoment;
        this.Thrust = settings.Thrust;
        this.CanardPos = settings.CanardPos;
        this.ElevatorPos = settings.ElevatorPos;
        this.JetPos = settings.JetPos;
        for (int i = 0; i < 8; i++)
        {
            this.Weapons[i] = new Weapon();
        }
        this.Weapons[0].WeaponPos = settings.WeaponPos0;
        this.Weapons[1].WeaponPos = reverseX(settings.WeaponPos0);
        this.Weapons[2].WeaponPos = settings.WeaponPos1;
        this.Weapons[3].WeaponPos = reverseX(settings.WeaponPos1);
        this.Weapons[4].WeaponPos = settings.WeaponPos2;
        this.Weapons[5].WeaponPos = reverseX(settings.WeaponPos2);
        this.Weapons[6].WeaponPos = settings.WeaponPos3;
        this.Weapons[7].WeaponPos = reverseX(settings.WeaponPos3);

        this.EdgePos = settings.EdgePos;
        this.CockpitPos = settings.CockpitPos;
        this.GunPos = settings.GunPos;

        this.Body.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_Body.cx", this.Name));
        if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_LeftCanard.cx", this.Name)))
        {
            this.LeftCanard = new GraphicsModel();
            this.LeftCanard.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_LeftCanard.cx", this.Name));
        }
        if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_RightCanard.cx", this.Name)))
        {
            this.RightCanard = new GraphicsModel();
            this.RightCanard.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_RightCanard.cx", this.Name));
        }
        if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_LeftElevator.cx", this.Name)))
        {
            this.LeftElevator = new GraphicsModel();
            this.LeftElevator.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_LeftElevator.cx", this.Name));
        }
        if (File.Exists(string.Format("res/mesh/aircraft/{0}/{0}_RightElevator.cx", this.Name)))
        {
            this.RightElevator = new GraphicsModel();
            this.RightElevator.CreateFromCX(string.Format("res/mesh/aircraft/{0}/{0}_RightElevator.cx", this.Name));
        }

        this.Texture.Create(string.Format("res/mesh/aircraft/{0}/{0}_P01.png", this.Name), Accessibility.None);
        this.NormalMapTexture.Create(string.Format("res/mesh/aircraft/{0}/{0}_N.png", this.Name), Accessibility.None);

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
                if (this.Opacity == 0.0f)
                    this.Render();
                break;

            case TranslucentRenderMessage:
                if (this.Opacity != 0.0f)
                    this.Render();
                break;

            default:
                break;
        }
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        Collision.Object = new SphereCollisionObject(new Sphere() { Radius = AircraftComponent.Radius });
        Collision.Group = 1;
        Collision.OtherGroups = 4;
        Collision.Collided += Collided;

        this.Owner.Get<JetComponent>().OffsetPosition = this.JetPos;
    }

    private void Collided(Entity other, Vector3 point)
    {
        if (this.Owner.Name == "player")
            return;

        if (other.Has<GroundComponent>() && this.Armor == 0)
        {
            this.Destroy();
        }
    }

    protected override void OnDestroy()
    {
        base.OnDestroy();

        this.Body.Dispose();
        if (this.LeftCanard != null)
            this.LeftCanard.Dispose();
        if (this.RightCanard != null)
            this.RightCanard.Dispose();
        if (this.LeftElevator != null)
            this.LeftElevator.Dispose();
        if (this.RightElevator != null)
            this.RightElevator.Dispose();
        this.Texture.Dispose();
        this.NormalMapTexture.Dispose();
    }

    public void Pitch(float power)
    {
        power = clamp(power, -1.0f, 1.0f);
        if (power > 0) power = 0.5f * power;
        float x = Physics.Velocity.Magnitude;
        float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
        Physics.Torque += Transform.Rightward * 0.003f * power * this.Stability * k;
    }

    public void Roll(float power)
    {
        power = clamp(power, -1.0f, 1.0f);
        float x = Physics.Velocity.Magnitude;
        float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
        Physics.Torque += Transform.Forward * -0.025f * power * this.Stability * k;
    }

    public void Yaw(float power)
    {
        power = clamp(power, -1.0f, 1.0f);
        float x = Physics.Velocity.Magnitude;
        float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
        Physics.Torque += Transform.Upward * 0.00075f * power * this.Stability * k;
    }

    public void YawY(float power)
    {
        power = clamp(power, -1.0f, 1.0f);
        float x = Physics.Velocity.Magnitude;
        float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
        Physics.Torque += Transform.Rightward * 0.00075f * power * this.Stability * k;
    }

    public void AutoPilot(Vector3 destination)
    {
        var p = destination * Transform.Matrix.Inverse;
        var z = Vector3.Angle(p, new Vector3(0, 0, 1));

        var y = Vector3.Angle(new Vector3(p.X, p.Y, 0), new Vector3(0, 1, 0));
        if ((deg2rad(20) < y) && (deg2rad(2) < z))
        {
            var power = clamp(y / 2, 0.2f, 1);
            this.Roll(power * ((p.X > 0) ? 1 : -1));
        }
        else
        {
            this.Yaw((p.X > 0) ? 1 : -1);

            if (deg2rad(5) < z)
            {
                var power = clamp(z * 6, 0.5f, 1);
                this.Pitch(power * ((p.Y > 0) ? -1 : 1));
            }
            else
            {
                this.YawY((p.Y > 0) ? -1 : 1);
            }
        }
    }

    public void AutoPilot(Entity target)
    {
        Vector3 destination = GunBulletComponent.ComputeOptimalAimPosition(this.Owner, target);
        this.AutoPilot(destination);
    }

    public void AutoFire(Entity target)
    {
        var viewing = ViewingMatrix;
        var projection = ProjectionMatrix;
        var time = GunBulletComponent.ComputeHitTime(this.Owner, target);

        var p1 = new Vector3(0, 0, time * GunBulletComponent.BulletSpeed) * this.Transform.Matrix;
        var p2 = target.Get<TransformComponent>().Position + time * target.Get<PhysicsComponent>().Velocity;

        if ((p2 - p1).SquaredMagnitude < square(Radius))
            this.Fire();
    }

    public void Launch()
    {
        var weapon = this.Weapons[this.NextUseWeapon];
        if (weapon.ReloadTime == 1.0f)
        {
            weapon.MissileEntity.Get<MissileComponent>().Launch();
            weapon.MissileEntity.Attach(new SoundComponent(JetSound));
            weapon.MissileEntity.Get<SoundComponent>().LoopPlay();
            weapon.MissileEntity = null;
            weapon.ReloadTime = 0;

            NextUseWeapon = (NextUseWeapon + 1) % 8;
        }
    }

    public void Fire()
    {
        this.Firing = true;
    }

    public void Avoid()
    {
        //this.Pitch(pow(this.Stability, 10) * -400.0f);
        float x = Physics.Velocity.Magnitude;
        float k = sin(1.05f * x - 2.75f) * 0.5f + 0.5f;
        Physics.Torque += Transform.Rightward * 0.003f * -400.0f * this.Stability * k;
        this.Stability = 0;
    }

    void Update()
    {
        this.DesiredPower = clamp(this.DesiredPower, 0.5f, 1);
        this.Power = close(this.Power, this.DesiredPower, 0.004f);

        Physics.Mass = this.Weight;
        Physics.InertiaMoment = this.InertiaMoment;
        Physics.Force += Transform.Forward * (this.Thrust * this.Power * max(1.0f, (this.Power - 0.9f) * 10.0f * 1.5f));

        for (int i = 0; i < 8; i++)
        {
            this.Weapons[i].ReloadTime = min(this.Weapons[i].ReloadTime + ReloadSpeed, 1.0f);

            if (this.Weapons[i].ReloadTime >= 1.0f && this.Weapons[i].MissileEntity == null)
            {
                Entity e = Entity.Instantiate();
                e.Attach(new TransformComponent());
                e.Attach(new PhysicsComponent());
                e.Attach(new MissileComponent(this.Owner));
                this.Weapons[i].MissileEntity = e;
            }
        }

        this.LeftSmokeGeneratorEntity.Get<TransformComponent>().Matrix = Transform.Matrix;
        this.LeftSmokeGeneratorEntity.Get<TransformComponent>().Matrix.Translate(this.EdgePos);
        this.RightSmokeGeneratorEntity.Get<TransformComponent>().Matrix = Transform.Matrix;
        this.RightSmokeGeneratorEntity.Get<TransformComponent>().Matrix.Translate(reverseX(this.EdgePos));

        this.Owner.Get<JetComponent>().Power = this.Power;

        if (this.Armor <= 0.5f)
        {
            if (!this.Owner.Has<AircraftSmokeComponent>())
                if (this.Visible)
                    this.Owner.Attach<AircraftSmokeComponent>();
        }
        else
        {
            if (this.Owner.Has<AircraftSmokeComponent>())
            {
                if (this.Visible)
                {
                    Entity e = Entity.Instantiate();
                    e.Attach(this.Owner.Detach<AircraftSmokeComponent>());
                }
            }
        }

        if (this.Armor == 0)
        {
            if (!this.Owner.Has<AircraftFlameComponent>())
                this.Owner.Attach<AircraftFlameComponent>();
        }
        else
        {
            if (this.Owner.Has<AircraftFlameComponent>())
            {
                if (this.Visible)
                {
                    Entity e = Entity.Instantiate();
                    e.Attach(this.Owner.Detach<AircraftFlameComponent>());
                }
            }
        }

        if (this.Owner.Name == "player")
        {
            var vibration = Entity.Find("camera").Get<VibrationComponent>();
            if (vibration != null)
                vibration.VibrationPower = (this.Power > 0.9f) ? 0.01f : 0.007f;
        }

        if ((this.Owner.Name == "player") && (this.Armor != 0))
            this.Armor += 0.0002f;

        this.Armor = clamp(this.Armor, 0, 1);

        #region 耐久力が０のとき、地面に落下
        if (this.Armor == 0)
        {
            this.DesiredPower = 0.6f;

            Vector3 axis = Transform.Rightward;
            axis.Y = 0;
            axis.Normalize();
            axis *= 0.001f;
            if (Transform.Upward.Y < 0)
                axis *= -1;
            Physics.Torque += axis;
        }
        #endregion

        #region サウンドの設定
        {
            if (this.Owner.Name == "player")
                this.Owner.Get<SoundComponent>().VolumeFactor = square(this.Power);
            else
                this.Owner.Get<SoundComponent>().VolumeFactor = 1.0f;
        }
        #endregion

        #region ロックオンサウンドの設定
        {
            if (this.Owner.Name == "player")
            {
                if (ActiveMissile != null)
                {
                    if (ActiveMissile.Locking)
                    {
                        if (!LockonSound.Playing)
                            LockonSound.LoopPlay();
                    }
                    else
                    {
                        if (ActiveMissile.Seeking)
                        {
                            if ((frame % 30) < 15)
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

        this.Stability = clamp(this.Stability + 0.01f, 0, 1);

        this.GunReloadTime = close(this.GunReloadTime, 1.0f, GunReloadSpeed);

        #region マズルフラッシュの座標の更新
        {
            foreach (var e in this.GunFlushs.Where(e => !e.IsAlive).ToArray())
            {
                this.GunFlushs.Remove(e);
            }
            foreach (var e in this.GunFlushs)
            {
                e.Get<TransformComponent>().Position = Transform.Position + this.GunPos * Transform.Matrix._Matrix3x3;
            }
        }
        #endregion

        #region 機銃発射
        if (this.Firing)
        {
            if (this.GunReloadTime == 1)
            {
                {
                    Entity e = Entity.Instantiate();
                    e.Attach(new TransformComponent() { Matrix = Transform.Matrix });
                    e.Get<TransformComponent>().Position = Transform.Position + this.GunPos * Transform.Matrix._Matrix3x3;
                    e.Get<TransformComponent>().Matrix.RotateAroundAxis(new Vector3(uniform(-1.0f, 1.0f), uniform(-1.0f, 1.0f), uniform(-1.0f, 1.0f)).Normalize(), normal(0, 0.005f));
                    e.Attach(new CollisionComponent() { Object = new PointCollisionObject(new Point()), OtherGroups = 1 | 4, Excludes = new CollisionComponent[] { Collision } });
                    e.Attach(new GunBulletComponent(this.Owner));
                    e.Attach(new SoundComponent(BulletSound));
                    e.Get<SoundComponent>().VolumeFactor = 0.8f;
                    e.Get<SoundComponent>().Play();
                    e.Attach(new LimitedLifeTimeComponent()
                    {
                        CountSpeed = 0.01f
                    });
                }

                if (this.Visible)
                {
                    Entity e = Entity.Instantiate();
                    e.Attach(new TransformComponent() { Matrix = Transform.Matrix });
                    e.Get<TransformComponent>().Position = Transform.Position + this.GunPos * Transform.Matrix._Matrix3x3;
                    e.Attach<GunFlushComponent>();
                    e.Attach(new LimitedLifeTimeComponent()
                    {
                        CountSpeed = 0.2f
                    });
                    this.GunFlushs.Add(e);
                }
                this.GunReloadTime = 0f;
            }

            this.Firing = false;
        }
        #endregion
    }

    public void Damage(float damage)
    {
        this.Armor -= damage;

        if (this.Armor <= 0)
        {
            if (this.Owner.Name != "player")
            {
                if (!this.Owner.Has<TimerComponent>())
                {
                    this.Owner.Attach(new TimerComponent() { CountSpeed = 0.001f });
                    this.Owner.Get<TimerComponent>().Ticked += this.Destroy;
                }

                if (this.Owner.Has<AIComponent>())
                    this.Owner.Detach<AIComponent>();
                if (this.Owner.Has<SquadronComponent>())
                    this.Owner.Detach<SquadronComponent>();
                if (this.Owner.Has<NPCAIComponent>())
                    this.Owner.Detach<NPCAIComponent>();
            }
        }
    }

    void Render()
    {
        GraphicsDeviceContext device = GraphicsDeviceContext.Instance;
        device.SetBlendState(this.Opacity == 0 ? NoBlend : AlphaBlend);
        device.SetRasterizerState(CullingOn);
        device.SetDepthStencilState(this.Opacity == 0 ? ZTestOn : ZTestOnWriteOff);
        device.SetVertexLayout(VertexLayout);
        device.SetPrimitiveTopology(PrimitiveTopology.TriangleList);
        device.SetVertexShader(VertexShader);
        device.SetPixelShader(PixelShader);

        PixelShader.SetSamplerState(Wrap, 0);
        PixelShader.SetTexture(Texture, 0);
        PixelShader.SetTexture(NormalMapTexture, 1);

        PixelShader.SetConstantBuffer(new Vector4(Entity.Find("camera").Get<TransformComponent>().Position, 1), 2);
        PixelShader.SetConstantBuffer(new Vector4(Entity.Find("light").Get<TransformComponent>().Forward, 0), 3);
        PixelShader.SetConstantBuffer(new Color(1, 1, 1, 1.0f - this.Opacity), 4);

        {
            VertexShader.SetConstantBuffer(WVPMatrix, 0);
            PixelShader.SetConstantBuffer(WorldMatrix, 0);
            PixelShader.SetConstantBuffer(WorldMatrix.Inverse, 1);

            device.SetVertexBuffer(this.Body.VertexPositions, 0);
            device.SetVertexBuffer(this.Body.VertexNormals, 1);
            device.SetVertexBuffer(this.Body.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.Body.VertexTangents, 3);
            device.SetVertexBuffer(this.Body.VertexBinormals, 4);
            device.SetIndexBuffer(this.Body.VertexIndices);
            device.DrawIndexed(this.Body.VertexIndices.Count);
        }

        var angular = new Vector4(Physics.AngularVelocity, 0) * Transform.Matrix.Inverse;

        if (this.LeftCanard != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(this.CanardPos);
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp(angular.X * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.LeftCanard.VertexPositions, 0);
            device.SetVertexBuffer(this.LeftCanard.VertexNormals, 1);
            device.SetVertexBuffer(this.LeftCanard.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.LeftCanard.VertexTangents, 3);
            device.SetVertexBuffer(this.LeftCanard.VertexBinormals, 4);
            device.SetIndexBuffer(this.LeftCanard.VertexIndices);
            device.DrawIndexed(this.LeftCanard.VertexIndices.Count);
        }

        if (this.RightCanard != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(reverseX(this.CanardPos));
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp(angular.X * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.RightCanard.VertexPositions, 0);
            device.SetVertexBuffer(this.RightCanard.VertexNormals, 1);
            device.SetVertexBuffer(this.RightCanard.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.RightCanard.VertexTangents, 3);
            device.SetVertexBuffer(this.RightCanard.VertexBinormals, 4);
            device.SetIndexBuffer(this.RightCanard.VertexIndices);
            device.DrawIndexed(this.RightCanard.VertexIndices.Count);
        }

        if (this.LeftElevator != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(this.ElevatorPos);
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp((-angular.X * 2 + angular.Z * 0.5f) * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.LeftElevator.VertexPositions, 0);
            device.SetVertexBuffer(this.LeftElevator.VertexNormals, 1);
            device.SetVertexBuffer(this.LeftElevator.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.LeftElevator.VertexTangents, 3);
            device.SetVertexBuffer(this.LeftElevator.VertexBinormals, 4);
            device.SetIndexBuffer(this.LeftElevator.VertexIndices);
            device.DrawIndexed(this.LeftElevator.VertexIndices.Count);
        }

        if (this.RightElevator != null)
        {
            Matrix4x4 move = new Matrix4x4().Identity().Translate(reverseX(this.ElevatorPos));
            Matrix4x4 rot = new Matrix4x4().Identity().RotateX(clamp((-angular.X * 2 - angular.Z * 0.5f) * 10, -0.3f, 0.3f));
            Matrix4x4 adjustment = move.Inverse * rot * move;

            VertexShader.SetConstantBuffer(adjustment * WVPMatrix, 0);
            PixelShader.SetConstantBuffer(adjustment * WorldMatrix, 0);
            PixelShader.SetConstantBuffer((adjustment * WorldMatrix).Inverse, 1);

            device.SetVertexBuffer(this.RightElevator.VertexPositions, 0);
            device.SetVertexBuffer(this.RightElevator.VertexNormals, 1);
            device.SetVertexBuffer(this.RightElevator.VertexTextureCoords, 2);
            device.SetVertexBuffer(this.RightElevator.VertexTangents, 3);
            device.SetVertexBuffer(this.RightElevator.VertexBinormals, 4);
            device.SetIndexBuffer(this.RightElevator.VertexIndices);
            device.DrawIndexed(this.RightElevator.VertexIndices.Count);
        }

        #region ミサイル更新
        for (int i = 0; i < 8; i++)
        {
            if (this.Weapons[i].MissileEntity != null)
            {
                Entity e = this.Weapons[i].MissileEntity;
                e.Get<TransformComponent>().Matrix = Transform.Matrix;
                e.Get<TransformComponent>().Matrix.Translate(this.Weapons[i].WeaponPos);
                e.Get<PhysicsComponent>().Velocity = Physics.Velocity;
                e.Get<MissileComponent>().TargetEntity = (this.Owner.Has<AIComponent>()) ? this.Owner.Get<AIComponent>().TargetEntity : null;
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
                Position = Transform.Position
            });
            e.Attach(new PhysicsComponent()
            {
                Mass = Physics.Mass,
                InertiaMoment = Physics.InertiaMoment,
                Force = new Vector3(normal(0, 1), normal(0, 1), normal(0, 1)).Normalize() * 100
            });
            e.Attach(new CollisionComponent()
            {
                Group = 0,
                OtherGroups = 4,
                Object = new SphereCollisionObject(new Sphere() { Radius = 5.0f })
            });
            e.Get<CollisionComponent>().Collided += (_, __) => { Entity.Kill(e); };
            e.Attach<GravityObjectComponent>();
            e.Attach<AircraftSmokeComponent>();
            e.Attach<AircraftFlameComponent>();
            e.Attach(new TimerComponent() { CountSpeed = 0.01f });
            e.Get<TimerComponent>().Ticked += () => Entity.Kill(e);
        }

        {
            Entity e = Entity.Instantiate();
            e.Attach(new TransformComponent() { Position = Transform.Position });
            e.Attach(new SoundComponent(LargeExplosionSound, true));
            e.Attach(new TimerComponent() { CountSpeed = 0.001f, Repeat = false });
            e.Get<TimerComponent>().Ticked += () => { Entity.Kill(e); };
        }

        foreach (var weapon in Weapons)
        {
            if (weapon.MissileEntity != null)
                Entity.Kill(weapon.MissileEntity);
        }

        Entity.BroadcastMessage(KillMessage, this.Owner);
        Entity.Kill(this.Owner);
    }

    static Vector3 reverseX(Vector3 v) { return new Vector3(-v.X, v.Y, v.Z); }
}
