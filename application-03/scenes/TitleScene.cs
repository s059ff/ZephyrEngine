using System.Linq;
using System.Runtime.CompilerServices;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class TitleScene : AbstractScene
{
    void P([CallerLineNumber] int __LINE__ = 0)
    {
        const int BEGIN = 19;
        const int END = 176;
        this.LoadingProgress = (float)(__LINE__ - BEGIN) / (END - BEGIN);
    }

    public override void LoadScene(object argument)
    {
        P(); Entity system = Entity.Instantiate();
        P(); system.Name = "system";
        P(); system.Attach(new SystemComponent());

        P(); Entity gamespace = Entity.Instantiate();
        P(); gamespace.Name = "gamespace";
        P(); gamespace.Attach(new GameSpaceComponent(10000.0f));

        P(); Entity camera = Entity.Instantiate();
        P(); camera.Name = "camera";
        P(); camera.Attach(new TransformComponent());
        P(); camera.Attach(new CameraComponent());
        P(); camera.Attach(new CustomCameraComponent());
        P(); camera.Attach(new SoundObserverComponent() { EffectRange = 10000, SonicSpeed = SonicSpeed * 2 });
        P(); camera.Get<CameraComponent>().LookAt(new Vector3(52, 1004, -900), new Vector3(0, 1000, 0));
        P(); camera.Attach<TransformControlComponent>();

        P(); Entity camera2d = Entity.Instantiate();
        P(); camera2d.Name = "camera2d";
        P(); camera2d.Attach(new TransformComponent());
        P(); camera2d.Attach(new CameraComponent());

        P(); Entity projector = Entity.Instantiate();
        P(); projector.Name = "projector";
        P(); projector.Attach(new ProjectorComponent());
        P(); projector.Attach(new CustomProjectorComponent());
        P(); projector.Get<ProjectorComponent>().SetPerspectiveMode(PI / 3, DisplayAspect, 1.0f, 4096.0f);

        P(); Entity projector2d = Entity.Instantiate();
        P(); projector2d.Name = "projector2d";
        P(); projector2d.Attach(new ProjectorComponent());
        P(); projector2d.Get<ProjectorComponent>().SetOrthogonalMode(DisplayAspect * 2.0f, 2.0f, 0, 1);

        P(); Entity light = Entity.Instantiate();
        P(); light.Name = "light";
        P(); light.Attach(new TransformComponent());
        P(); light.Attach(new LightComponent());
        P(); light.Get<LightComponent>().LookAt(new Vector3(-1, 1, -1), new Vector3(0, 0, 0));

        P(); Entity title = Entity.Instantiate();
        P(); title.Attach<TitleComponent>();

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

        {
            P(); Entity enemy1 = Entity.Instantiate();
            P(); enemy1.Name = "enemy1";
            P(); enemy1.Attach(new TransformComponent());
            P(); enemy1.Attach(new PhysicsComponent());
            P(); enemy1.Attach(new CollisionComponent());
            P(); enemy1.Attach(new JetComponent());
            P(); enemy1.Attach(new SoundComponent(JetSound));
            P(); enemy1.Attach(new AircraftComponent());
            P(); enemy1.Attach(new AIComponent(Enemy));
            P(); enemy1.Attach(new SquadronComponent("Enemy1"));
            P(); enemy1.Attach(new NPCAIComponent());
            P(); enemy1.Get<TransformComponent>().Matrix.RotateY(PI);
            P(); enemy1.Get<TransformComponent>().Position = new Vector3(0, 1000, 1000);
            P(); enemy1.Get<SoundComponent>().LoopPlay();
        }
        {
            P(); Entity enemy2 = Entity.Instantiate();
            P(); enemy2.Name = "enemy2";
            P(); enemy2.Attach(new TransformComponent());
            P(); enemy2.Attach(new PhysicsComponent());
            P(); enemy2.Attach(new CollisionComponent());
            P(); enemy2.Attach(new JetComponent());
            P(); enemy2.Attach(new SoundComponent(JetSound));
            P(); enemy2.Attach(new AircraftComponent());
            P(); enemy2.Attach(new AIComponent(Enemy));
            P(); enemy2.Attach(new SquadronComponent("Enemy2"));
            P(); enemy2.Attach(new NPCAIComponent());
            P(); enemy2.Get<TransformComponent>().Matrix.RotateY(PI);
            P(); enemy2.Get<TransformComponent>().Position = new Vector3(50, 1000, 1050);
            P(); enemy2.Get<SoundComponent>().LoopPlay();
        }
        {
            P(); Entity enemy3 = Entity.Instantiate();
            P(); enemy3.Name = "enemy3";
            P(); enemy3.Attach(new TransformComponent());
            P(); enemy3.Attach(new PhysicsComponent());
            P(); enemy3.Attach(new CollisionComponent());
            P(); enemy3.Attach(new JetComponent());
            P(); enemy3.Attach(new SoundComponent(JetSound));
            P(); enemy3.Attach(new AircraftComponent());
            P(); enemy3.Attach(new AIComponent(Enemy));
            P(); enemy3.Attach(new SquadronComponent("Enemy3"));
            P(); enemy3.Attach(new NPCAIComponent());
            P(); enemy3.Get<TransformComponent>().Matrix.RotateY(PI);
            P(); enemy3.Get<TransformComponent>().Position = new Vector3(-50, 1000, 1050);
            P(); enemy3.Get<SoundComponent>().LoopPlay();
        }

        {
            P(); Entity friend1 = Entity.Instantiate();
            P(); friend1.Name = "friend1";
            P(); friend1.Attach(new TransformComponent());
            P(); friend1.Attach(new PhysicsComponent());
            P(); friend1.Attach(new CollisionComponent());
            P(); friend1.Attach(new JetComponent());
            P(); friend1.Attach(new SoundComponent(JetSound));
            P(); friend1.Attach(new AircraftComponent());
            P(); friend1.Attach(new AIComponent(Friend));
            P(); friend1.Attach(new SquadronComponent("Friend1"));
            P(); friend1.Attach(new NPCAIComponent());
            P(); friend1.Get<TransformComponent>().Position = new Vector3(0, 1000, -1000);
            P(); friend1.Get<SoundComponent>().LoopPlay();
        }
        {
            P(); Entity friend2 = Entity.Instantiate();
            P(); friend2.Name = "friend2";
            P(); friend2.Attach(new TransformComponent());
            P(); friend2.Attach(new PhysicsComponent());
            P(); friend2.Attach(new CollisionComponent());
            P(); friend2.Attach(new JetComponent());
            P(); friend2.Attach(new SoundComponent(JetSound));
            P(); friend2.Attach(new AircraftComponent());
            P(); friend2.Attach(new AIComponent(Friend));
            P(); friend2.Attach(new SquadronComponent("Friend2"));
            P(); friend2.Attach(new NPCAIComponent());
            P(); friend2.Get<TransformComponent>().Position = new Vector3(50, 1000, -1050);
            P(); friend2.Get<SoundComponent>().LoopPlay();
        }
        {
            P(); Entity friend3 = Entity.Instantiate();
            P(); friend3.Name = "friend3";
            P(); friend3.Attach(new TransformComponent());
            P(); friend3.Attach(new PhysicsComponent());
            P(); friend3.Attach(new CollisionComponent());
            P(); friend3.Attach(new JetComponent());
            P(); friend3.Attach(new SoundComponent(JetSound));
            P(); friend3.Attach(new AircraftComponent());
            P(); friend3.Attach(new AIComponent(Friend));
            P(); friend3.Attach(new SquadronComponent("Friend3"));
            P(); friend3.Attach(new NPCAIComponent());
            P(); friend3.Get<TransformComponent>().Position = new Vector3(-50, 1000, -1050);
            P(); friend3.Get<SoundComponent>().LoopPlay();
        }
    }
}
