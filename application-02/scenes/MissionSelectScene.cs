using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static Script;

class MissionSelectScene : AbstractScene
{
    public override void MakeScene(LoadingTask task, object[] args)
    {
        Entity system = Entity.Instantiate();
        system.Name = "system";
        system.Attach(new SystemComponent());

        task.ProgressRate = 0.1f;

        Entity gamespace = Entity.Instantiate();
        gamespace.Name = "gamespace";
        gamespace.Attach(new GameSpaceComponent(10000.0f));

        task.ProgressRate = 0.2f;

        Entity camera = Entity.Instantiate();
        camera.Name = "camera";
        camera.Attach(new TransformComponent());
        camera.Attach(new CameraComponent());
        camera.Attach(new SoundObserverComponent() { EffectRange = 10000, SonicSpeed = SonicSpeed * 2 });
        camera.Get<CameraComponent>().LookAt(new Vector3(52, 1004, -900), new Vector3(0, 1000, 0));
        camera.Attach<TransformControlComponent>();

        task.ProgressRate = 0.3f;

        Entity camera2d = Entity.Instantiate();
        camera2d.Name = "camera2d";
        camera2d.Attach(new TransformComponent());
        camera2d.Attach(new CameraComponent());

        task.ProgressRate = 0.4f;

        Entity projector = Entity.Instantiate();
        projector.Name = "projector";
        projector.Attach(new ProjectorComponent());
        projector.Get<ProjectorComponent>().SetPerspectiveMode(PI / 3, DisplayAspect, 1.0f, 4096.0f);

        task.ProgressRate = 0.5f;

        Entity projector2d = Entity.Instantiate();
        projector2d.Name = "projector2d";
        projector2d.Attach(new ProjectorComponent());
        projector2d.Get<ProjectorComponent>().SetOrthogonalMode(DisplayAspect * 2.0f, 2.0f, 0, 1);

        task.ProgressRate = 0.6f;

        Entity light = Entity.Instantiate();
        light.Name = "light";
        light.Attach(new TransformComponent());
        light.Attach(new LightComponent());
        light.Get<LightComponent>().LookAt(new Vector3(-1, 1, -1), new Vector3(0, 0, 0));

        task.ProgressRate = 0.7f;

        Entity missionSelect = Entity.Instantiate();
        missionSelect.Attach<MissionSelectComponent>();

        task.ProgressRate = 0.8f;
    }
}
