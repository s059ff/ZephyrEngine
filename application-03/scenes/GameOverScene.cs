using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using static EngineScript;
using static GameScript;

public class GameOverScene : AbstractScene
{
    public override void LoadScene(object argument)
    {
        Entity system = Entity.Instantiate();
        system.Name = "system";
        system.Attach(new SystemComponent());

        this.LoadingProgress = 0.25f;

        Entity camera2d = Entity.Instantiate();
        camera2d.Name = "camera2d";
        camera2d.Attach(new TransformComponent());
        camera2d.Attach(new CameraComponent());

        this.LoadingProgress = 0.5f;

        Entity projector2d = Entity.Instantiate();
        projector2d.Name = "projector2d";
        projector2d.Attach(new ProjectorComponent());
        projector2d.Get<ProjectorComponent>().SetOrthogonalMode(DisplayAspect * 2.0f, 2.0f, 0, 1);

        this.LoadingProgress = 0.75f;

        Entity entity = Entity.Instantiate();
        entity.Attach<GameOverComponent>();

        this.LoadingProgress = 1.0f;
    }
}
