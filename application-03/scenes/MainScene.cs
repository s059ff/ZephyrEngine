using System.Linq;
using System.Reflection;
using System.Runtime.CompilerServices;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class MainScene : AbstractScene
{
    void P([CallerLineNumber] int __LINE__ = 0)
    {
        const int BEGIN = 25;
        const int END = 115;
        this.LoadingProgress = (float)(__LINE__ - BEGIN) / (END - BEGIN);
    }

    public override void LoadScene(object argument)
    {
        var assembly = argument as Assembly;

        P(); this.LoadingProgress = 0.0f;

        P(); Entity system = Entity.Instantiate();
        P(); system.Name = "system";
        P(); system.Attach(new SystemComponent());

        P(); this.LoadingProgress = 0.1f;

        P(); Entity gamespace = Entity.Instantiate();
        P(); gamespace.Name = "gamespace";
        P(); gamespace.Attach(new GameSpaceComponent(10000.0f));

        P(); this.LoadingProgress = 0.2f;

        P(); Entity camera = Entity.Instantiate();
        P(); camera.Name = "camera";
        P(); camera.Attach(new TransformComponent());
        P(); camera.Attach(new CameraComponent());
        P(); camera.Attach(new CustomCameraComponent());
        P(); camera.Attach(new SoundObserverComponent() { EffectRange = 10000, SonicSpeed = SonicSpeed * 2 });
        P(); camera.Get<CameraComponent>().LookAt(new Vector3(sin(0.5f), 0.5f, -cos(0.5f)) * 2000, new Vector3(0, 0, 0));
        P();
        P(); Entity camera2d = Entity.Instantiate();
        P(); camera2d.Name = "camera2d";
        P(); camera2d.Attach(new TransformComponent());
        P(); camera2d.Attach(new CameraComponent());

        P(); this.LoadingProgress = 0.3f;

        P(); Entity projector = Entity.Instantiate();
        P(); projector.Name = "projector";
        P(); projector.Attach(new ProjectorComponent());
        P(); projector.Attach(new CustomProjectorComponent());
        P(); projector.Get<ProjectorComponent>().SetPerspectiveMode(PI / 3, DisplayAspect, 1.0f, 4096.0f);

        P(); Entity projector2d = Entity.Instantiate();
        P(); projector2d.Name = "projector2d";
        P(); projector2d.Attach(new ProjectorComponent());
        P(); projector2d.Get<ProjectorComponent>().SetOrthogonalMode(DisplayAspect * 2.0f, 2.0f, 0, 1);

        P(); this.LoadingProgress = 0.4f;

        P(); Entity light = Entity.Instantiate();
        P(); light.Name = "light";
        P(); light.Attach(new TransformComponent());
        P(); light.Attach(new LightComponent());
        P(); light.Get<LightComponent>().LookAt(new Vector3(-1, 1, -1), new Vector3(0, 0, 0));

        P(); this.LoadingProgress = 0.5f;

        P(); Entity sky = Entity.Instantiate();
        P(); sky.Attach(new TransformComponent());
        P(); sky.Attach(new SkyComponent());

        P(); Entity ground = Entity.Instantiate();
        P(); ground.Name = "ground";
        P(); ground.Attach(new TransformComponent());
        P(); ground.Attach(new CollisionComponent());
        P(); ground.Attach(new GroundComponent());

        P(); Entity cloud = Entity.Instantiate();
        P(); cloud.Name = "cloud";
        P(); cloud.Attach(new CloudComponent(randoms(distmap("res/texture/cloud_distribution.png"), 10000).Select(tuple =>
        {
            float x = tuple.Item1 - 0.5f;
            float z = tuple.Item2 - 0.5f;
            var length = Entity.Find("gamespace").Get<GameSpaceComponent>().AreaLength;
            x *= length;
            z *= length;
            float y = normal(1000, 100);
            return new Vector3(x, y, z);
        }).ToArray()));

#if true
        P(); camera.Attach(new WindComponent());
        P(); camera.Attach(new VibrationComponent());

        P(); Entity ui = Entity.Instantiate();
        P(); ui.Name = "ui";
        P(); ui.Attach(new UIComponent());
        P(); ui.Attach(new DamageViewComponent());

#else
P(task);        camera.Attach<TransformControlComponent>();
#endif

        P(); this.LoadingProgress = 0.6f;

        P(); Entity missionController = Entity.Instantiate();
        P(); missionController.Attach(new MissionControllerComponent(assembly));

        //#if true
        //        Entity player = Entity.Instantiate();
        //        player.Name = "player";
        //        player.Attach(new TransformComponent());
        //        player.Attach(new PhysicsComponent());
        //        player.Attach(new CollisionComponent());
        //        player.Attach(new JetComponent());
        //        player.Attach(new AircraftComponent());
        //        player.Attach(new AIComponent(Friend));
        //        player.Attach(new PlayerComponent());
        //        player.Attach(new SquadronComponent("Mobius"));
        //        player.Attach(new SoundComponent(JetSound));
        //        player.Get<TransformComponent>().Position = new Vector3(0, 1000, -2000);
        //        player.Get<SoundComponent>().LoopPlay();
        //#endif
        //        {
        //            Entity enemy1 = Entity.Instantiate();
        //            enemy1.Name = "enemy1";
        //            enemy1.Attach(new TransformComponent());
        //            enemy1.Attach(new PhysicsComponent());
        //            enemy1.Attach(new CollisionComponent());
        //            enemy1.Attach(new JetComponent());
        //            enemy1.Attach(new AircraftComponent());
        //            enemy1.Attach(new AIComponent(Enemy));
        //            enemy1.Attach(new SquadronComponent("Sorcerer"));
        //            enemy1.Attach(new NPCAIComponent());
        //            enemy1.Attach(new SoundComponent(JetSound));
        //            enemy1.Get<TransformComponent>().Matrix.RotateY(PI);
        //            enemy1.Get<TransformComponent>().Position = new Vector3(1000, 1000, 2500);
        //            //enemy1.Get<TransformComponent>().Position = new Vector3(100, 1000, 0);
        //            enemy1.Get<SoundComponent>().LoopPlay();
        //        }

        //        //camera.Get<CameraComponent>().Mode = CameraComponent.CameraMode.Tracking;
        //        //camera.Get<CameraComponent>().TrackingTarget = enemy1;
        //        //camera.Get<CameraComponent>().Offset = new Vector3(0, 4, -18);

        //#if true
        //        {
        //            Entity enemy2 = Entity.Instantiate();
        //            enemy2.Name = "enemy2";
        //            enemy2.Attach(new TransformComponent());
        //            enemy2.Attach(new PhysicsComponent());
        //            enemy2.Attach(new CollisionComponent());
        //            enemy2.Attach(new JetComponent());
        //            enemy2.Attach(new AircraftComponent());
        //            enemy2.Attach(new AIComponent(Enemy));
        //            enemy2.Attach(new SquadronComponent("Sorcerer"));
        //            enemy2.Attach(new NPCAIComponent());
        //            enemy2.Attach(new SoundComponent(JetSound));
        //            enemy2.Get<TransformComponent>().Matrix.RotateY(PI);
        //            enemy2.Get<TransformComponent>().Position = new Vector3(1050, 1000, 2520);
        //            enemy2.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity enemy3 = Entity.Instantiate();
        //            enemy3.Name = "enemy3";
        //            enemy3.Attach(new TransformComponent());
        //            enemy3.Attach(new PhysicsComponent());
        //            enemy3.Attach(new CollisionComponent());
        //            enemy3.Attach(new JetComponent());
        //            enemy3.Attach(new AircraftComponent());
        //            enemy3.Attach(new AIComponent(Enemy));
        //            enemy3.Attach(new SquadronComponent("Sorcerer"));
        //            enemy3.Attach(new NPCAIComponent());
        //            enemy3.Attach(new SoundComponent(JetSound));
        //            enemy3.Get<TransformComponent>().Matrix.RotateY(PI);
        //            enemy3.Get<TransformComponent>().Position = new Vector3(1000 - 50, 1000, 2520);
        //            enemy3.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity enemy4 = Entity.Instantiate();
        //            enemy4.Attach(new TransformComponent());
        //            enemy4.Attach(new PhysicsComponent());
        //            enemy4.Attach(new CollisionComponent());
        //            enemy4.Attach(new JetComponent());
        //            enemy4.Attach(new AircraftComponent());
        //            enemy4.Attach(new AIComponent(Enemy));
        //            enemy4.Attach(new SquadronComponent("Giant"));
        //            enemy4.Attach(new NPCAIComponent());
        //            enemy4.Attach(new SoundComponent(JetSound));
        //            enemy4.Get<TransformComponent>().Matrix.RotateY(PI);
        //            enemy4.Get<TransformComponent>().Position = new Vector3(-1000, 2000, 2500);
        //            enemy4.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity enemy5 = Entity.Instantiate();
        //            enemy5.Attach(new TransformComponent());
        //            enemy5.Attach(new PhysicsComponent());
        //            enemy5.Attach(new CollisionComponent());
        //            enemy5.Attach(new JetComponent());
        //            enemy5.Attach(new AircraftComponent());
        //            enemy5.Attach(new AIComponent(Enemy));
        //            enemy5.Attach(new SquadronComponent("Giant"));
        //            enemy5.Attach(new NPCAIComponent());
        //            enemy5.Attach(new SoundComponent(JetSound));
        //            enemy5.Get<TransformComponent>().Position = new Vector3(-1050, 2000, 2500);
        //            enemy5.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity friend1 = Entity.Instantiate();
        //            friend1.Name = "friend1";
        //            friend1.Attach(new TransformComponent());
        //            friend1.Attach(new PhysicsComponent());
        //            friend1.Attach(new CollisionComponent());
        //            friend1.Attach(new JetComponent());
        //            friend1.Attach(new AircraftComponent());
        //            friend1.Attach(new AIComponent(Friend));
        //            friend1.Attach(new SquadronComponent("Mobius"));
        //            friend1.Attach(new NPCAIComponent());
        //            friend1.Attach(new SoundComponent(JetSound));
        //            friend1.Get<TransformComponent>().Position = new Vector3(-50, 1000, -2050);
        //            friend1.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity friend2 = Entity.Instantiate();
        //            friend2.Name = "friend2";
        //            friend2.Attach(new TransformComponent());
        //            friend2.Attach(new PhysicsComponent());
        //            friend2.Attach(new CollisionComponent());
        //            friend2.Attach(new JetComponent());
        //            friend2.Attach(new AircraftComponent());
        //            friend2.Attach(new AIComponent(Friend));
        //            friend2.Attach(new SquadronComponent("Mobius"));
        //            friend2.Attach(new NPCAIComponent());
        //            friend2.Attach(new SoundComponent(JetSound));
        //            friend2.Get<TransformComponent>().Position = new Vector3(50, 1000, -2050);
        //            friend2.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity friend3 = Entity.Instantiate();
        //            friend3.Name = "friend3";
        //            friend3.Attach(new TransformComponent());
        //            friend3.Attach(new PhysicsComponent());
        //            friend3.Attach(new CollisionComponent());
        //            friend3.Attach(new JetComponent());
        //            friend3.Attach(new AircraftComponent());
        //            friend3.Attach(new AIComponent(Friend));
        //            friend3.Attach(new SquadronComponent("Venom"));
        //            friend3.Attach(new NPCAIComponent());
        //            friend3.Attach(new SoundComponent(JetSound));
        //            friend3.Get<TransformComponent>().Position = new Vector3(0, 1000, -2500);
        //            friend3.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity friend4 = Entity.Instantiate();
        //            friend4.Name = "friend4";
        //            friend4.Attach(new TransformComponent());
        //            friend4.Attach(new PhysicsComponent());
        //            friend4.Attach(new CollisionComponent());
        //            friend4.Attach(new JetComponent());
        //            friend4.Attach(new AircraftComponent());
        //            friend4.Attach(new AIComponent(Friend));
        //            friend4.Attach(new SquadronComponent("Venom"));
        //            friend4.Attach(new NPCAIComponent());
        //            friend4.Attach(new SoundComponent(JetSound));
        //            friend4.Get<TransformComponent>().Position = new Vector3(-50, 1000, -2550);
        //            friend4.Get<SoundComponent>().LoopPlay();
        //        }
        //        {
        //            Entity friend5 = Entity.Instantiate();
        //            friend5.Name = "friend5";
        //            friend5.Attach(new TransformComponent());
        //            friend5.Attach(new PhysicsComponent());
        //            friend5.Attach(new CollisionComponent());
        //            friend5.Attach(new JetComponent());
        //            friend5.Attach(new AircraftComponent());
        //            friend5.Attach(new AIComponent(Friend));
        //            friend5.Attach(new SquadronComponent("Venom"));
        //            friend5.Attach(new NPCAIComponent());
        //            friend5.Attach(new SoundComponent(JetSound));
        //            friend5.Get<TransformComponent>().Position = new Vector3(50, 1000, -2550);
        //            friend5.Get<SoundComponent>().LoopPlay();
        //        }
        //#endif
    }
}
