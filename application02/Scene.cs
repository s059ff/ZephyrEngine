using System;
using ZephyrSharp;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;

using static EngineScript;
using static GameScript;

class Scene
{
    public static void ResetScene(Program.Arguments args)
    {
        Entity.Clear();
        GC.Collect();

        Entity system = Entity.Instantiate();
        system.Name = "system";
        system.Attach(new SystemComponent());
        system.Attach(new CheatComponent()
        {
            NoAttack = args.CheatNoAttack,
            FreezePosition = args.CheatFreezePosition
        });

        Entity debugger = Entity.Instantiate();
        debugger.Name = "debugger";
        //debugger.Attach(new LoggerComponent());
        debugger.Attach(new DebugInformationDisplayComponent());

        Entity gamespace = Entity.Instantiate();
        gamespace.Name = "gamespace";
        gamespace.Attach(new GameSpaceComponent(20000));

        Entity camera = Entity.Instantiate();
        camera.Name = "camera";
        camera.Attach(new TransformComponent());
        camera.Attach(new TrackingCameraComponent());
        camera.Attach(new FixedPointCameraComponent());
        camera.Attach(new GunCameraComponent());
        camera.Attach(new SoundObserverComponent() { EffectRange = 10000, SonicSpeed = 340.0 / 60.0 * 2 });
        camera.Get<TrackingCameraComponent>().Activate();

        Entity camera2d = Entity.Instantiate();
        camera2d.Name = "camera2d";
        camera2d.Attach(new TransformComponent());
        camera2d.Attach(new CameraComponent());

        Entity projector = Entity.Instantiate();
        projector.Name = "projector";
        projector.Attach(new ProjectorComponent());
        projector.Get<ProjectorComponent>().SetPerspectiveMode(PI / 3, WindowAspectRatio, 1.0f, 4096.0f);

        Entity projector2d = Entity.Instantiate();
        projector2d.Name = "projector2d";
        projector2d.Attach(new ProjectorComponent());
        projector2d.Get<ProjectorComponent>().SetOrthogonalMode(WindowAspectRatio * 2.0f, 2.0f, 0, 1);

        Entity light = Entity.Instantiate();
        light.Name = "light";
        light.Attach(new TransformComponent());
        light.Attach(new LightComponent());
        light.Get<LightComponent>().LookAt(new Vector3(-1, 1, -1), new Vector3(0, 0, 0));

        Entity sky = Entity.Instantiate();
        sky.Name = "sky";
        sky.Attach(new TransformComponent());
        sky.Attach(new SkyComponent());

        Entity ground = Entity.Instantiate();
        ground.Name = "ground";
        ground.Attach(new TransformComponent());
        ground.Attach(new CollisionComponent());
        ground.Attach(new GroundComponent());

        {
            Entity entity = Entity.Instantiate();
            entity.Name = "player";
            entity.Attach(new TransformComponent());
            entity.Attach(new PhysicsComponent());
            entity.Attach(new CollisionComponent());
            entity.Attach(new AircraftComponent("FA-22_Raptor"));
            entity.Attach(new JetComponent());
            entity.Attach(new SoundComponent(JetSound));
            entity.Attach(new AircraftAvionicsComponent(OrganizationFriend));
            entity.Attach(new SquadronComponent("Gargoyle"));
            entity.Attach(new EnvironmentObservationComponent());
            entity.Attach(new AircraftHUDComponent());
            entity.Attach(new WindComponent());
            switch (args.ExecutionMode)
            {
                case "play":
                    entity.Attach(new PlayerPilotComponent());
                    break;
                case "demo":
                    entity.Attach(new NonPlayerPilotComponent());
                    break;
                case "training":
                    entity.Attach(new LearnablePilotComponent());
                    break;
                case "evaluation":
                    entity.Attach(new LearnablePilotComponent());
                    break;
                default:
                    throw new RuntimeException();
            }

            entity.Get<TransformComponent>().Matrix.Position = new Vector3(0, 2000, -2000);
            entity.Get<SoundComponent>().LoopPlay();
        }

        for (int i = 0; i < args.FriendCount; i++)
        {
            Entity entity = Entity.Instantiate();
            entity.Name = string.Format("friend{0}", i + 1);
            entity.Attach(new TransformComponent());
            entity.Attach(new PhysicsComponent());
            entity.Attach(new CollisionComponent());
            entity.Attach(new AircraftComponent("FA-22_Raptor"));
            entity.Attach(new JetComponent());
            entity.Attach(new SoundComponent(JetSound));
            entity.Attach(new AircraftAvionicsComponent(OrganizationFriend));
            entity.Attach(new SquadronComponent("Gargoyle"));
            entity.Attach(new NonPlayerPilotComponent());

            entity.Get<TransformComponent>().Position = new Vector3(normal(0, 100), 2000, normal(-2000, 100));
            entity.Get<SoundComponent>().LoopPlay();
        }

        var x = linspace(-1000, +1000, args.EnemyCount);
        for (int i = 0; i < args.EnemyCount; i++)
        {
            Entity entity = Entity.Instantiate();
            entity.Name = string.Format("enemy{0}", i + 1);
            entity.Attach(new TransformComponent());
            entity.Attach(new PhysicsComponent());
            entity.Attach(new CollisionComponent());
            entity.Attach(new AircraftComponent("Su-37_Terminator"));
            entity.Attach(new JetComponent());
            entity.Attach(new SoundComponent(JetSound));
            entity.Attach(new AircraftAvionicsComponent(OrganizationEnemy));
            entity.Attach(new SquadronComponent("Cyclops"));
            entity.Attach(new NonPlayerPilotComponent());

            entity.Get<TransformComponent>().Matrix.RotateX(uniform(-PI, PI));
            entity.Get<TransformComponent>().Matrix.RotateY(uniform(-PI, PI));
            entity.Get<TransformComponent>().Matrix.RotateZ(uniform(-PI, PI));
            entity.Get<TransformComponent>().Position = new Vector3(x[i], 2000, 2000);
            entity.Get<SoundComponent>().LoopPlay();
        }
    }
}
