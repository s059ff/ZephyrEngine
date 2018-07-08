using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using static Script;

public class GameOverScene : AbstractScene
{
    public override void MakeScene(LoadingTask task, object[] args)
    {
        Entity system = Entity.Instantiate();
        system.Name = "system";
        system.Attach(new SystemComponent());

        task.ProgressRate = 0.25f;

        Entity camera2d = Entity.Instantiate();
        camera2d.Name = "camera2d";
        camera2d.Attach(new TransformComponent());
        camera2d.Attach(new CameraComponent());

        task.ProgressRate = 0.5f;

        Entity projector2d = Entity.Instantiate();
        projector2d.Name = "projector2d";
        projector2d.Attach(new ProjectorComponent());
        projector2d.Get<ProjectorComponent>().SetOrthogonalMode(DisplayAspect * 2.0f, 2.0f, 0, 1);

        task.ProgressRate = 0.75f;

        Entity entity = Entity.Instantiate();
        entity.Attach<GameOverComponent>();

        task.ProgressRate = 1.0f;
    }
}
