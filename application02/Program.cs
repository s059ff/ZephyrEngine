using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Graphics;
using ZephyrSharp.Linalg;
using ZephyrSharp.Sound;
using ZephyrTools.CommandRunner;
using ZephyrTools.GameSystemMonitor;
using static EngineScript;
using static GameScript;

class Program
{
    static void Main(string[] args)
    {
        Window window = new Window();
        window.Create("application02", (int)DisplayWidth, (int)DisplayHeight);

        GraphicsDevice.Instance.Create(window, FullScreen);
        SoundDevice.Instance.Create(window.Handle);

#if DEBUG
        var runner = CommandRunner.Execute();
        var monitor = GameSystemMonitor.Execute();
#endif

        System.Func<bool> sceneResetCondition = () =>
        {
            bool condition1 = Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("player"))) == null;
            bool condition2 = Entity.Find(e => (e.Name != null) && (e.Name.StartsWith("enemy"))) == null;
            return condition1 || condition2;
        };

        window.Updated += () =>
        {
            if (sceneResetCondition())
            {
                ResetScene();
            }

            EngineScript.update();
            GameScript.update();

            GraphicsDeviceContext.Instance.Clear(ColorCode.Black);
            Entity.BroadcastMessage(UpdateMessage);
            Entity.BroadcastMessage(RenderMessage);
            Entity.BroadcastMessage(TranslucentRenderMessage);
            Entity.BroadcastMessage(DrawMessage);
            GraphicsDeviceContext.Instance.Present();

            Entity.Update();
        };

        try
        {
            EngineScript.initialize();
            GameScript.initialize();

            ResetScene();

            window.Start();
        }
        finally
        {
#if DEBUG
            GameSystemMonitor.Shutdown(monitor);
            CommandRunner.Shutdown(runner);
#endif

            Entity.Clear();

            EngineScript.finalize();
            GameScript.finalize();

            GraphicsDeviceContext.Instance.Dispose();
            GraphicsDevice.Instance.Dispose();
            SoundDevice.Instance.Dispose();
        }
    }

    static void ResetScene()
    {
        Entity.Clear();

        Entity system = Entity.Instantiate();
        system.Name = "system";
        system.Attach(new SystemComponent());

        Entity debugger = Entity.Instantiate();
        debugger.Name = "debugger";
        debugger.Attach(new LoggerComponent());
        debugger.Attach(new DebugInformationDisplayComponent());

        Entity gamespace = Entity.Instantiate();
        gamespace.Name = "gamespace";
        gamespace.Attach(new GameSpaceComponent(20000));

        Entity camera = Entity.Instantiate();
        camera.Name = "camera";
        camera.Attach(new TransformComponent());
        camera.Attach(new TrackingCameraComponent());
        camera.Attach(new FixedPointCameraComponent());
        camera.Attach(new SoundObserverComponent() { EffectRange = 10000, SonicSpeed = SonicSpeed * 2 });
        camera.Get<TrackingCameraComponent>().Activate();

        Entity camera2d = Entity.Instantiate();
        camera2d.Name = "camera2d";
        camera2d.Attach(new TransformComponent());
        camera2d.Attach(new CameraComponent());

        Entity projector = Entity.Instantiate();
        projector.Name = "projector";
        projector.Attach(new ProjectorComponent());
        projector.Get<ProjectorComponent>().SetPerspectiveMode(PI / 3, DisplayAspect, 1.0f, 4096.0f);

        Entity projector2d = Entity.Instantiate();
        projector2d.Name = "projector2d";
        projector2d.Attach(new ProjectorComponent());
        projector2d.Get<ProjectorComponent>().SetOrthogonalMode(DisplayAspect * 2.0f, 2.0f, 0, 1);

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

#if false
        Entity cloud = Entity.Instantiate();
        cloud.Name = "cloud";
        cloud.Attach(new CloudComponent(randoms(distmap("res/texture/cloud_distribution.png"), 10000).Select(tuple =>
        {
            float x = tuple.Item1 - 0.5f;
            float z = tuple.Item2 - 0.5f;
            var length = Entity.Find("gamespace").Get<GameSpaceComponent>().SpaceLength;
            x *= length;
            z *= length;
            float y = normal(1000, 100);
            return new Vector3(x, y, z);
        }).ToArray()));
#endif

        {
            Entity entity = Entity.Instantiate();
            entity.Name = "player";
            entity.Attach(new TransformComponent());
            entity.Attach(new PhysicsComponent());
            entity.Attach(new CollisionComponent());
            entity.Attach(new AircraftComponent("FA-22_Raptor"));
            entity.Attach(new JetComponent());
            entity.Attach(new SoundComponent(JetSound));
            entity.Attach(new AircraftAvionicsComponent(Friend));
            entity.Attach(new SquadronComponent("Gargoyle"));
            entity.Attach(new PlayerPilotComponent());
            entity.Attach(new WindComponent());
            entity.Attach(new AircraftHUDComponent());

            entity.Get<TransformComponent>().Position = new Vector3(0, 2000, -2000);
            entity.Get<SoundComponent>().LoopPlay();
        }

        for (int i = 0; i < 0; i++)
        {
            Entity entity = Entity.Instantiate();
            entity.Name = string.Format("friend{0}", i + 1);
            entity.Attach(new TransformComponent());
            entity.Attach(new PhysicsComponent());
            entity.Attach(new CollisionComponent());
            entity.Attach(new AircraftComponent("FA-22_Raptor"));
            entity.Attach(new JetComponent());
            entity.Attach(new SoundComponent(JetSound));
            entity.Attach(new AircraftAvionicsComponent(Friend));
            entity.Attach(new SquadronComponent("Gargoyle"));
            entity.Attach(new NonPlayerPilotComponent());

            entity.Get<TransformComponent>().Position = new Vector3(normal(0, 100), 2000, normal(-2000, 100));
            entity.Get<SoundComponent>().LoopPlay();
        }

        for (int i = 0; i < 4; i++)
        {
            Entity entity = Entity.Instantiate();
            entity.Name = string.Format("enemy{0}", i + 1);
            entity.Attach(new TransformComponent());
            entity.Attach(new PhysicsComponent());
            entity.Attach(new CollisionComponent());
            entity.Attach(new AircraftComponent("Su-37_Terminator"));
            entity.Attach(new JetComponent());
            entity.Attach(new SoundComponent(JetSound));
            entity.Attach(new AircraftAvionicsComponent(Enemy));
            entity.Attach(new SquadronComponent("Cyclops"));
            entity.Attach(new NonPlayerPilotComponent());

            entity.Get<TransformComponent>().Matrix.RotateX(uniform(-PI, PI));
            entity.Get<TransformComponent>().Matrix.RotateY(uniform(-PI, PI));
            entity.Get<TransformComponent>().Matrix.RotateZ(uniform(-PI, PI));
            entity.Get<TransformComponent>().Position = new Vector3(normal(0, 100), 2000, normal(1000, 100));
            entity.Get<SoundComponent>().LoopPlay();
        }
    }
}
