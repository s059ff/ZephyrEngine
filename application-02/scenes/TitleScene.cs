using System.Linq;
using System.Runtime.CompilerServices;
using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static Script;

class TitleScene : AbstractScene
{
    static void P(LoadingTask task, [CallerLineNumber] int __LINE__ = 0)
    {
        const int BEGIN = 19;
        const int END = 176;
        task.ProgressRate = (float)(__LINE__ - BEGIN) / (END - BEGIN);
    }

    public override void MakeScene(LoadingTask task, object[] args)
    {
        P(task); Entity system = Entity.Instantiate();
        P(task); system.Name = "system";
        P(task); system.Attach(new SystemComponent());

        P(task); Entity gamespace = Entity.Instantiate();
        P(task); gamespace.Name = "gamespace";
        P(task); gamespace.Attach(new GameSpaceComponent(10000.0f));

        P(task); Entity camera = Entity.Instantiate();
        P(task); camera.Name = "camera";
        P(task); camera.Attach(new TransformComponent());
        P(task); camera.Attach(new CameraComponent());
        P(task); camera.Attach(new CustomCameraComponent());
        P(task); camera.Attach(new SoundObserverComponent() { EffectRange = 10000, SonicSpeed = SonicSpeed * 2 });
        P(task); camera.Get<CameraComponent>().LookAt(new Vector3(52, 1004, -900), new Vector3(0, 1000, 0));
        P(task); camera.Attach<TransformControlComponent>();

        P(task); Entity camera2d = Entity.Instantiate();
        P(task); camera2d.Name = "camera2d";
        P(task); camera2d.Attach(new TransformComponent());
        P(task); camera2d.Attach(new CameraComponent());

        P(task); Entity projector = Entity.Instantiate();
        P(task); projector.Name = "projector";
        P(task); projector.Attach(new ProjectorComponent());
        P(task); projector.Attach(new CustomProjectorComponent());
        P(task); projector.Get<ProjectorComponent>().SetPerspectiveMode(PI / 3, DisplayAspect, 1.0f, 4096.0f);

        P(task); Entity projector2d = Entity.Instantiate();
        P(task); projector2d.Name = "projector2d";
        P(task); projector2d.Attach(new ProjectorComponent());
        P(task); projector2d.Get<ProjectorComponent>().SetOrthogonalMode(DisplayAspect * 2.0f, 2.0f, 0, 1);

        P(task); Entity light = Entity.Instantiate();
        P(task); light.Name = "light";
        P(task); light.Attach(new TransformComponent());
        P(task); light.Attach(new LightComponent());
        P(task); light.Get<LightComponent>().LookAt(new Vector3(-1, 1, -1), new Vector3(0, 0, 0));

        P(task); Entity title = Entity.Instantiate();
        P(task); title.Attach<TitleComponent>();

        P(task); Entity sky = Entity.Instantiate();
        P(task); sky.Attach(new TransformComponent());
        P(task); sky.Attach(new SkyComponent());

        P(task); Entity ground = Entity.Instantiate();
        P(task); ground.Name = "ground";
        P(task); ground.Attach(new TransformComponent());
        P(task); ground.Attach(new CollisionComponent());
        P(task); ground.Attach(new GroundComponent());

        P(task); Entity cloud = Entity.Instantiate();
        P(task); cloud.Name = "cloud";
        P(task); cloud.Attach(new CloudComponent(randoms(distmap("res/texture/cloud_distribution.png"), 10000).Select(tuple =>
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
            P(task); Entity enemy1 = Entity.Instantiate();
            P(task); enemy1.Name = "enemy1";
            P(task); enemy1.Attach(new TransformComponent());
            P(task); enemy1.Attach(new PhysicsComponent());
            P(task); enemy1.Attach(new CollisionComponent());
            P(task); enemy1.Attach(new JetComponent());
            P(task); enemy1.Attach(new SoundComponent(JetSound));
            P(task); enemy1.Attach(new AircraftComponent());
            P(task); enemy1.Attach(new AIComponent(Enemy));
            P(task); enemy1.Attach(new SquadronComponent("Enemy1"));
            P(task); enemy1.Attach(new NPCAIComponent());
            P(task); enemy1.Get<TransformComponent>().Matrix.RotateY(PI);
            P(task); enemy1.Get<TransformComponent>().Position = new Vector3(0, 1000, 1000);
            P(task); enemy1.Get<SoundComponent>().LoopPlay();
        }
        {
            P(task); Entity enemy2 = Entity.Instantiate();
            P(task); enemy2.Name = "enemy2";
            P(task); enemy2.Attach(new TransformComponent());
            P(task); enemy2.Attach(new PhysicsComponent());
            P(task); enemy2.Attach(new CollisionComponent());
            P(task); enemy2.Attach(new JetComponent());
            P(task); enemy2.Attach(new SoundComponent(JetSound));
            P(task); enemy2.Attach(new AircraftComponent());
            P(task); enemy2.Attach(new AIComponent(Enemy));
            P(task); enemy2.Attach(new SquadronComponent("Enemy2"));
            P(task); enemy2.Attach(new NPCAIComponent());
            P(task); enemy2.Get<TransformComponent>().Matrix.RotateY(PI);
            P(task); enemy2.Get<TransformComponent>().Position = new Vector3(50, 1000, 1050);
            P(task); enemy2.Get<SoundComponent>().LoopPlay();
        }
        {
            P(task); Entity enemy3 = Entity.Instantiate();
            P(task); enemy3.Name = "enemy3";
            P(task); enemy3.Attach(new TransformComponent());
            P(task); enemy3.Attach(new PhysicsComponent());
            P(task); enemy3.Attach(new CollisionComponent());
            P(task); enemy3.Attach(new JetComponent());
            P(task); enemy3.Attach(new SoundComponent(JetSound));
            P(task); enemy3.Attach(new AircraftComponent());
            P(task); enemy3.Attach(new AIComponent(Enemy));
            P(task); enemy3.Attach(new SquadronComponent("Enemy3"));
            P(task); enemy3.Attach(new NPCAIComponent());
            P(task); enemy3.Get<TransformComponent>().Matrix.RotateY(PI);
            P(task); enemy3.Get<TransformComponent>().Position = new Vector3(-50, 1000, 1050);
            P(task); enemy3.Get<SoundComponent>().LoopPlay();
        }

        {
            P(task); Entity friend1 = Entity.Instantiate();
            P(task); friend1.Name = "friend1";
            P(task); friend1.Attach(new TransformComponent());
            P(task); friend1.Attach(new PhysicsComponent());
            P(task); friend1.Attach(new CollisionComponent());
            P(task); friend1.Attach(new JetComponent());
            P(task); friend1.Attach(new SoundComponent(JetSound));
            P(task); friend1.Attach(new AircraftComponent());
            P(task); friend1.Attach(new AIComponent(Friend));
            P(task); friend1.Attach(new SquadronComponent("Friend1"));
            P(task); friend1.Attach(new NPCAIComponent());
            P(task); friend1.Get<TransformComponent>().Position = new Vector3(0, 1000, -1000);
            P(task); friend1.Get<SoundComponent>().LoopPlay();
        }
        {
            P(task); Entity friend2 = Entity.Instantiate();
            P(task); friend2.Name = "friend2";
            P(task); friend2.Attach(new TransformComponent());
            P(task); friend2.Attach(new PhysicsComponent());
            P(task); friend2.Attach(new CollisionComponent());
            P(task); friend2.Attach(new JetComponent());
            P(task); friend2.Attach(new SoundComponent(JetSound));
            P(task); friend2.Attach(new AircraftComponent());
            P(task); friend2.Attach(new AIComponent(Friend));
            P(task); friend2.Attach(new SquadronComponent("Friend2"));
            P(task); friend2.Attach(new NPCAIComponent());
            P(task); friend2.Get<TransformComponent>().Position = new Vector3(50, 1000, -1050);
            P(task); friend2.Get<SoundComponent>().LoopPlay();
        }
        {
            P(task); Entity friend3 = Entity.Instantiate();
            P(task); friend3.Name = "friend3";
            P(task); friend3.Attach(new TransformComponent());
            P(task); friend3.Attach(new PhysicsComponent());
            P(task); friend3.Attach(new CollisionComponent());
            P(task); friend3.Attach(new JetComponent());
            P(task); friend3.Attach(new SoundComponent(JetSound));
            P(task); friend3.Attach(new AircraftComponent());
            P(task); friend3.Attach(new AIComponent(Friend));
            P(task); friend3.Attach(new SquadronComponent("Friend3"));
            P(task); friend3.Attach(new NPCAIComponent());
            P(task); friend3.Get<TransformComponent>().Position = new Vector3(-50, 1000, -1050);
            P(task); friend3.Get<SoundComponent>().LoopPlay();
        }
    }
}
