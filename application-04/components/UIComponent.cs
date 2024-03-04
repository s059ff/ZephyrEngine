using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

public class UIComponent : CustomEntityComponent
{
    static Texture2D CourseTexture = new Texture2D();
    static Texture2D CoursePointerTexture = new Texture2D();
    static Texture2D PitchscaleTexture = new Texture2D();
    static Texture2D SpeedMeterTexture = new Texture2D();
    static Texture2D RadarTexture = new Texture2D();
    static Texture2D AircraftMarkerTexture = new Texture2D();
    static Texture2D MissileMarkerTexture = new Texture2D();
    static Texture2D TargetTexture = new Texture2D();
    static Texture2D TargetDirectionTexture = new Texture2D();
    static Texture2D ReloadTimeTexture = new Texture2D();
    static Texture2D ReloadTimeFrameTexture = new Texture2D();
    static Texture2D GunReticleTexture = new Texture2D();

    float RadarRange = 1000;

    float NoticeDisplayTime = 0;
    string NoticeMessage = string.Empty;

    static UIComponent()
    {
        CourseTexture.Create("res/texture/course.png", Accessibility.None);
        CoursePointerTexture.Create("res/texture/course_pointer.png", Accessibility.None);
        PitchscaleTexture.Create("res/texture/pitchscale.png", Accessibility.None);
        SpeedMeterTexture.Create("res/texture/speedmeter.png", Accessibility.None);
        RadarTexture.Create("res/texture/radar.dds", Accessibility.None);
        AircraftMarkerTexture.Create("res/texture/marker_aircraft.dds", Accessibility.None);
        MissileMarkerTexture.Create("res/texture/marker_missile.dds", Accessibility.None);
        TargetTexture.Create("res/texture/target.dds", Accessibility.None);
        TargetDirectionTexture.Create("res/texture/direction.dds", Accessibility.None);
        ReloadTimeTexture.Create("res/texture/reload.dds", Accessibility.None);
        ReloadTimeFrameTexture.Create("res/texture/reload_frame.dds", Accessibility.None);
        GunReticleTexture.Create("res/texture/reticle.dds", Accessibility.None);
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case DrawMessage:
                this.Draw();
                break;

            case "notice":
                this.NoticeDisplayTime = 1;
                this.NoticeMessage = argument as string;
                break;

            default:
                break;
        }
    }

    protected override void OnDestroy()
    {
        base.OnDestroy();

        AlertSound.Stop();
    }

    private void Draw()
    {
        var player = Entity.Find("player");
        if (player == null || player.Get<AircraftComponent>().Armor == 0)
            return;

        var aircraft = player.Get<AircraftComponent>();
        if (aircraft == null || aircraft.Armor == 0)
            return;

        var transform = player.Get<TransformComponent>();
        var physics = player.Get<PhysicsComponent>();
        var target = player.Get<AircraftAvionicsComponent>().TargetEntity;

        bool lockonAlert = false;
        bool missileAlert = false;
        Entity.ForEach((e) =>
        {
            var missile = e.Get<MissileComponent>();
            if (missile != null && missile.TargetEntity == player && missile.Locking)
            {
                if (missile.Launched)
                    missileAlert = true;
                else
                    lockonAlert = true;
            }
        });

        bool playAlertSound = missileAlert || (lockonAlert && (frame % 60) < 30);

        if (playAlertSound && !AlertSound.Playing)
            AlertSound.LoopPlay();

        if (!playAlertSound && AlertSound.Playing)
            AlertSound.Stop();

        {
            Color Red = new Color(0.8f, 0, 0, 0.8f);
            Color Blue = new Color(0, 0.4f, 0.8f, 0.8f);
            Color Black = new Color(0, 0, 0, 0.8f);
            Color Yellow = new Color(0.6f, 0.6f, 0, 0.8f);
            Color Green = new Color(0, 0.8f, 0, 0.8f);

            identity();

            blend(HalfAddition);
            color(Green);

            #region 耐久値
            if (true)
            {
                pushMatrix();
                {
                    translate(-1.0f, 0.75f, 0.0f);

                    pushMatrix();
                    {
                        scale(0.08f);
                        write(string.Format("{0:p}", aircraft.Armor), TextAlignment.Center, TextAlignment.Center);
                    }
                    popMatrix();
                }
                popMatrix();
            }
            #endregion

            #region 速度計と高度計
            if (true)
            {
                pushMatrix();
                {
                    var velocity = ToKmPerHour(physics.Velocity.Magnitude);

                    translate(-0.55f, 0.0f, 0.0f);

                    pushMatrix();
                    {
                        translate(-0.15f, 0.0f, 0.0f);
                        scale(0.08f);
                        write(floor(velocity).ToString().PadLeft(4), TextAlignment.Center, TextAlignment.Center);
                    }
                    popMatrix();

                    pushMatrix();
                    {
                        scale(0.1f, 0.4f);
                        float v = -velocity / 100;
                        draw(SpeedMeterTexture, 1, v, 0, v + 1);
                    }
                    popMatrix();
                }
                popMatrix();

                pushMatrix();
                {
                    var altitude = transform.Position.Y;

                    translate(0.55f, 0.0f, 0.0f);

                    pushMatrix();
                    {
                        translate(0.15f, 0.0f, 0.0f);
                        scale(0.08f);
                        write(floor(altitude).ToString().PadLeft(4), TextAlignment.Center, TextAlignment.Center);
                    }
                    popMatrix();

                    pushMatrix();
                    {
                        scale(0.1f, 0.4f);
                        float v = -altitude / 100;
                        draw(SpeedMeterTexture, 0, v, 1, v + 1);
                    }
                    popMatrix();
                }
                popMatrix();
            }
            #endregion

            #region 針路計
            if (true)
            {
                pushMatrix();
                {
                    Vector3 front = transform.Forward;
                    float angle = atan2(front.X, front.Z);
                    float u = angle / PI;

                    translate(0, 0.75f);
                    scale(0.8f, 0.2f);

                    draw(CourseTexture, u - 0.25f, 0.0f, u + 0.25f, 1.0f);
                }
                popMatrix();

                pushMatrix();
                {
                    translate(0, 0.75f);
                    scale(0.05f, 0.05f);
                    translate(0, -1);

                    draw(CoursePointerTexture);
                }
                popMatrix();
            }
            #endregion

            #region ピッチスケール
            if (true)
            {
                pushMatrix();
                {
                    Vector3 front = transform.Forward;
                    float pitch = atan2(front.Y, sqrt(front.X * front.X + front.Z * front.Z));
                    float v = -1.0f / PI * (pitch - PIOver2);

                    Matrix4x3 matrix = transform.Matrix;
                    matrix.Position = Vector3.Zero;
                    matrix.Invert();
                    Vector3 direction = new Vector3(0, 1, 0) * matrix;
                    float angle = -atan2(direction.X, direction.Y);

                    rotate(angle);
                    scale(0.75f, 0.75f);

                    addressing(Mirror);
                    draw(PitchscaleTexture, 0.0f, v - 0.1f, 2.0f, v + 0.1f);
                    addressing(Wrap);
                }
                popMatrix();
            }
            #endregion

            #region ターゲットディレクション
            if (target != null)
            {
                var transform2 = target.Get<TransformComponent>();
                Vector3 relative = transform2.Position - transform.Position;
                if (relative.Magnitude < SearchOperationRange && Vector3.Angle(relative, transform.Forward) / PIOver2 > 0.2f)
                {
                    Matrix4x3 matrix = transform.Matrix;
                    matrix.Position = Vector3.Zero;
                    matrix.Invert();
                    relative = relative * matrix;
                    relative.Z = 0;
                    float theta = atan2(relative.Y, relative.X);
                    float x = 0.5f * cos(theta);
                    float y = 0.5f * sin(theta);

                    pushMatrix();
                    {
                        translate(x, y);
                        rotate(theta);
                        scale(0.15f, 0.075f);
                        draw(TargetDirectionTexture);
                    }
                    popMatrix();

                    pushMatrix();
                    {
                        translate(x * 0.7f, y * 0.7f);
                        scale(0.06f);
                        write(((int)(transform2.Position - transform.Position).Magnitude).ToString(), TextAlignment.Center, TextAlignment.Center);
                    }
                    popMatrix();
                }
            }
            #endregion

            #region ミサイルディレクション
            Entity.ForEach(e =>
            {
                color(Red);
                var missile = e.Get<MissileComponent>();
                if (missile != null && missile.TargetEntity == player && missile.Locking && missile.Launched)
                {
                    var transform2 = e.Get<TransformComponent>();
                    Vector3 relative = transform2.Position - transform.Position;
                    if (relative.Magnitude < SearchOperationRange && Vector3.Angle(relative, transform.Forward) / PIOver2 > 0.2f)
                    {
                        Matrix4x3 matrix = transform.Matrix;
                        matrix.Position = Vector3.Zero;
                        matrix.Invert();
                        relative = relative * matrix;
                        relative.Z = 0;
                        float theta = atan2(relative.Y, relative.X);
                        float x = 0.5f * cos(theta);
                        float y = 0.5f * sin(theta);

                        pushMatrix();
                        {
                            translate(x, y);
                            rotate(theta);
                            scale(0.15f, 0.075f);
                            draw(TargetDirectionTexture);
                        }
                        popMatrix();

                        pushMatrix();
                        {
                            translate(x * 0.7f, y * 0.7f);
                            scale(0.06f);
                            write(((int)relative.Magnitude).ToString(), TextAlignment.Center, TextAlignment.Center);
                        }
                        popMatrix();
                    }
                }
            });
            #endregion

            #region ターゲットマーカー
            Entity.ForEach((e) =>
            {
                if (e.Has<AircraftAvionicsComponent>() && e.Get<AircraftComponent>().Armor > 0 && e.Name != "player")
                {
                    var missile = player.Get<AircraftComponent>().ActiveMissile;
                    {
                        var world = e.Get<TransformComponent>().Matrix;
                        var viewing = Entity.Find("camera").Get<CameraComponent>().ViewingMatrix;
                        var projection = Entity.Find("projector").Get<ProjectorComponent>().ProjectionMatrix;

                        Vector4 v = new Vector4(Vector3.Zero, 1) * world * viewing * projection;
                        if (0 <= v.W && v.W <= SearchOperationRange)
                        {
                            pushMatrix();
                            {
                                var x = v.X / v.W;
                                var y = v.Y / v.W;
                                translate(x * DisplayAspect, y);
                                scale(0.06f);

                                if (e.Get<AircraftAvionicsComponent>().Organization == Enemy)
                                {
                                    if ((missile != null) && (missile.TargetEntity == e) && (missile.Locking))
                                    {
                                        color(Red);
                                        draw(TargetTexture);
                                    }
                                    else if ((target == e) && (frame % 30 < 15))
                                    {
                                        color(Green);
                                        draw(TargetTexture);
                                    }
                                    else if (target != e)
                                    {
                                        color(Green);
                                        draw(TargetTexture);
                                    }
                                }
                                else
                                {
                                    color(Blue);
                                    draw(TargetTexture);
                                }

                                translate(0.5f, 0);
                                scale(0.75f);
                                string text = string.Format(
                                        "{0}\n{1}",
                                        e.Get<AircraftComponent>().Name,
                                        e.Get<SquadronComponent>().SquadronName + " " + (e.Get<SquadronComponent>().UnitNumber + 1)
                                    );
                                write(text, TextAlignment.Left, TextAlignment.Bottom);

                                float distance = (transform.Position - e.Get<TransformComponent>().Position).Magnitude;
                                string text2 = string.Format("{0}", (int)distance);
                                write(text2, TextAlignment.Left, TextAlignment.Top);
                            }
                            popMatrix();
                        }
                    }
                }
            });
            #endregion

            #region ガンレティクル
            if (target != null)
            {
                var viewing = ViewingMatrix;
                var projection = ProjectionMatrix;
                var time = GunBulletComponent.ComputeHitTime(player, target);

                var p1 = new Vector3(0, 0, time * GunBulletComponent.BulletSpeed) * transform.Matrix;
                var v1 = new Vector4(p1, 1) * viewing * projection;

                var p2 = target.Get<TransformComponent>().Position + time * target.Get<PhysicsComponent>().Velocity;
                var v2 = new Vector4(p2, 1) * viewing * projection;

                if (0 <= v2.W && v2.W <= 800)
                {
                    pushMatrix();
                    {
                        Vector2 u1 = new Vector2(v1.X / v1.W, v1.Y / v1.W);
                        Vector2 u2 = new Vector2(v2.X / v2.W, v2.Y / v2.W);
                        Vector2 u3 = u1 + (u1 - u2);
                        translate(u3.X * DisplayAspect, u3.Y);
                        scale(0.1f);

                        color(((p2 - p1).SquaredMagnitude < square(AircraftComponent.Radius)) ? Red : Green);
                        draw(GunReticleTexture);
                    }
                    popMatrix();
                }
            }
            #endregion

#if false
            #region デバッグゾーン
            {
                var viewing = ViewingMatrix;
                var projection = ProjectionMatrix;
                var v2 = new Vector4(PlayerComponent.AimPoint, 1) * viewing * projection;

                if (0 <= v2.W)
                {
                    pushMatrix();
                    {
                        translate(new Vector2(v2.X / v2.W * DisplayAspect, v2.Y / v2.W));
                        scale(0.1f);

                        color(Red);
                        draw(GunReticleTexture);
                    }
                    popMatrix();
                }
            }
            #endregion  
#endif

            #region シーカー
            {
                var missile = player.Get<AircraftComponent>().ActiveMissile;
                if (missile != null && missile.TargetEntity != null)
                {
                    var viewing = Entity.Find("camera").Get<CameraComponent>().ViewingMatrix;
                    var projection = Entity.Find("projector").Get<ProjectorComponent>().ProjectionMatrix;

                    if (missile.Locking)
                    {
                        color(Red);

                        var world = missile.TargetEntity.Get<TransformComponent>().Matrix;
                        Vector4 p = new Vector4(Vector3.Zero, 1) * world * viewing * projection;
                        if (0 <= p.W && p.W <= SearchOperationRange)
                        {
                            pushMatrix();
                            {
                                var x = p.X / p.W;
                                var y = p.Y / p.W;
                                translate(x * DisplayAspect, y);
                                rotate(deg2rad(45.0f));
                                scale(0.06f / sqrt(2));
                                draw(TargetTexture);
                            }
                            popMatrix();
                        }
                    }
                    else if (missile.Seeking)
                    {
                        color(Green);

                        float dist = (missile.TargetEntity.Get<TransformComponent>().Position - transform.Position).Magnitude;

                        var world = missile.SeekerAngle * transform.Matrix;
                        Vector4 p = new Vector4(0, 0, dist, 1) * world * viewing * projection;
                        pushMatrix();
                        {
                            var x = p.X / p.W;
                            var y = p.Y / p.W;
                            translate(x * DisplayAspect, y);
                            rotate(deg2rad(45.0f));
                            scale(0.06f / sqrt(2));
                            draw(TargetTexture);
                        }
                        popMatrix();
                    }
                }
            }
            #endregion

            #region レーダー
            if (true)
            {
                color(Green);

                pushMatrix();
                {
                    translate(-1.25f, -0.7f, 0);
                    scale(0.5f, 0.5f);
                    draw(RadarTexture);

                }
                popMatrix();

                pushMatrix();
                {
                    translate(-1.25f, -0.7f, 0);
                    scale(0.5f, 0.5f);
                    translate(0.5f / sqrt(2), -0.5f / sqrt(2), 0);
                    scale(0.1f);
                    write(RadarRange.ToString());
                }
                popMatrix();

                Matrix4x3 local = new Matrix4x3().Identity();
                {
                    Vector3 direction = transform.Forward;
                    float theta = atan2(direction.X, direction.Z);
                    local.RotateY(theta);
                    local.Position = transform.Position;
                    local.Invert();
                }

                color(Red);

                Entity.ForEach((e) =>
                {
                    if (e.Has<AircraftAvionicsComponent>() && (e.Name != "player"))
                    {
                        color((e.Get<AircraftAvionicsComponent>().Organization == Friend) ? Blue : Red);

                        if (!((e == target) && (frame % 60 < 30)))
                        {
                            var transform2 = e.Get<TransformComponent>();
                            Matrix4x3 matrix = transform2.Matrix * local;
                            if (matrix.Position.Magnitude < SearchOperationRange)
                            {
                                Vector3 point = new Vector3(matrix.M41, 0, matrix.M43);
                                point /= max(RadarRange, point.Magnitude);

                                Vector2 point2D;
                                point2D.X = point.X * 0.5f / 2;
                                point2D.Y = point.Z * 0.5f / 2;
                                point2D += new Vector2(-1.25f, -0.7f);
                                float theta = atan2(matrix.M31, matrix.M33);

                                pushMatrix();
                                {
                                    translate(point2D);
                                    rotate(-theta);
                                    scale(0.07f);

                                    draw(AircraftMarkerTexture);
                                }
                                popMatrix();
                            }
                        }
                    }
                    else if (e.Has<MissileComponent>() && e.Get<MissileComponent>().Launched)
                    {
                        color(Red);

                        var transform2 = e.Get<TransformComponent>();
                        Matrix4x3 matrix = transform2.Matrix * local;
                        Vector3 point = new Vector3(matrix.M41, 0, matrix.M43);
                        if (point.Magnitude < SearchOperationRange)
                        {
                            point /= max(RadarRange, point.Magnitude);

                            Vector2 point2D;
                            point2D.X = point.X * 0.5f / 2;
                            point2D.Y = point.Z * 0.5f / 2;
                            point2D += new Vector2(-1.25f, -0.7f);

                            pushMatrix();
                            {
                                translate(point2D);
                                scale(0.05f);

                                draw(MissileMarkerTexture);
                            }
                            popMatrix();
                        }
                    }
                });
            }
            #endregion

            #region リロード
            {
                pushMatrix();
                translate(-1.25f, -0.2f);
                scale(0.15f / 4, 0.15f);
                {
                    var times = player.Get<AircraftComponent>().ReloadTimes;

                    for (int i = 0; i < AircraftComponent.WeaponCount; i++)
                    {
                        var time = times[i];
                        pushMatrix();
                        {
                            switch (i)
                            {
                                case 0: translate(-0.75f, 0); break;
                                case 1: translate(0.75f, 0); break;
                                case 2: translate(-1.75f, -0.25f); break;
                                case 3: translate(1.75f, -0.25f); break;
                                case 4: translate(-2.75f, -0.5f); break;
                                case 5: translate(2.75f, -0.5f); break;
                                case 6: translate(-3.75f, -0.75f); break;
                                case 7: translate(3.75f, -0.75f); break;
                            }
                            color(time == 1 ? Green : Red);
                            drawThreshold(ReloadTimeTexture, 0, 1 - time, 1.0f, 1.0f);
                            draw(ReloadTimeFrameTexture);
                        }
                        popMatrix();
                    }
                }
                popMatrix();
            }
            #endregion

            #region 全体マップ
            if (true)
            {
                pushMatrix();
                {
                    translate(1.25f, -0.7f, 0);
                    scale(0.5f, 0.5f);
                    color(Black);
                    rectangle();
                }
                popMatrix();

                Entity.ForEach((e) =>
                {
                    if (e.Has<AircraftAvionicsComponent>())
                    {
                        if (!((target == e) && (frame % 60 < 30)))
                        {
                            color((e.Get<AircraftAvionicsComponent>().Organization == Friend) ? (e.Name == "player") ? Green : Blue : Red);

                            var transform2 = e.Get<TransformComponent>();
                            Matrix4x3 matrix = transform2.Matrix;
                            Vector3 point = new Vector3(matrix.M41, 0, matrix.M43);
                            point /= Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength * 0.5f;
                            if (point.Magnitude <= 1.0f)
                            {
                                Vector2 point2D;
                                point2D.X = point.X * 0.5f / 2;
                                point2D.Y = point.Z * 0.5f / 2;
                                point2D += new Vector2(1.25f, -0.7f);
                                float theta = atan2(matrix.M31, matrix.M33);

                                pushMatrix();
                                {
                                    translate(point2D);
                                    rotate(-theta);
                                    scale(0.05f);

                                    draw(AircraftMarkerTexture);
                                }
                                popMatrix();
                            }
                        }
                    }
                });
            }
            #endregion

            #region アラートメッセージ
            {
                if (missileAlert)
                {
                    color(Red);
                    pushMatrix();
                    {
                        scale(0.07f);
                        write("Missile Alert", TextAlignment.Center, TextAlignment.Center);
                    }
                    popMatrix();
                }
                else if (lockonAlert && playAlertSound)
                {
                    color(Yellow);
                    pushMatrix();
                    {
                        scale(0.07f);
                        write("Lockon Caution", TextAlignment.Center, TextAlignment.Center);
                    }
                    popMatrix();
                }

            }
            #endregion

            #region 通知
            {
                if (this.NoticeDisplayTime > 0)
                {
                    blend(Addition);
                    Color c = Green;
                    c.R *= square(this.NoticeDisplayTime);
                    c.G *= square(this.NoticeDisplayTime);
                    c.B *= square(this.NoticeDisplayTime);
                    color(c);
                    pushMatrix();
                    {
                        scale(0.07f);
                        translate(0, 1);
                        write(this.NoticeMessage, TextAlignment.Center, TextAlignment.Center);
                    }
                    popMatrix();

                    this.NoticeDisplayTime = clamp(this.NoticeDisplayTime - 0.005f, 0, 1);
                }
            }
            #endregion
        }
    }

    public void ChangeRadarRange()
    {
        if (RadarRange == 1000)
            RadarRange = 2000;
        else if (RadarRange == 2000)
            RadarRange = 4000;
        else if (RadarRange == 4000)
            RadarRange = 1000;
    }
}
