using ZephyrSharp.GameSystem;
using ZephyrSharp.GameSystem.Components;
using ZephyrSharp.Linalg;
using static Script;

class Scene
{
    public static void MakeScene()
    {
        Entity system = Entity.Instantiate();
        system.Name = "system";
        system.Attach(new SystemComponent());

        Entity camera = Entity.Instantiate();
        camera.Name = "camera";
        camera.Attach(new TransformComponent());
        camera.Attach(new CameraComponent());
        camera.Get<CameraComponent>().LookAt(new Vector3(sin(0.3f), 1, -cos(0.3f)) * 12, new Vector3(0, 4, 0));

        Entity projector = Entity.Instantiate();
        projector.Name = "projector";
        projector.Attach(new ProjectorComponent());
        projector.Get<ProjectorComponent>().SetPerspectiveMode(PI / 3, 4.0f / 3.0f, 0.5f, 256.0f);

        Entity light = Entity.Instantiate();
        light.Name = "light";
        light.Attach(new TransformComponent());
        light.Attach(new LightComponent());
        light.Get<LightComponent>().LookAt(new Vector3(sin(-0.4f), 1.25f, -cos(-0.4f)) * 10, new Vector3(0, 4, 0));

        Entity projector_light = Entity.Instantiate();
        projector_light.Name = "projector_light";
        projector_light.Attach(new ProjectorComponent());
        projector_light.Get<ProjectorComponent>().SetOrthogonalMode(20, 20, 0, 64);

        Entity floor = Entity.Instantiate();
        floor.Name = "floor";
        floor.Attach(new TransformComponent());
        floor.Attach(new FloorComponent());

        Entity wall1 = Entity.Instantiate();
        wall1.Name = "wall1";
        wall1.Attach(new TransformComponent());
        wall1.Attach(new WallComponent());
        wall1.Get<TransformComponent>().Matrix = new Matrix4x3().Identity().Translate(0, 5, 5).Scale(10);

        Entity wall2 = Entity.Instantiate();
        wall2.Name = "wall2";
        wall2.Attach(new TransformComponent());
        wall2.Attach(new WallComponent());
        wall2.Get<TransformComponent>().Matrix = new Matrix4x3().Identity().Translate(0, 5, -5).RotateY(PI).Scale(10);

        Entity wall3 = Entity.Instantiate();
        wall3.Name = "wall3";
        wall3.Attach(new TransformComponent());
        wall3.Attach(new WallComponent());
        wall3.Get<TransformComponent>().Matrix = new Matrix4x3().Identity().Translate(5, 5, 0).RotateY(PIOver2).Scale(10);

        Entity wall4 = Entity.Instantiate();
        wall4.Name = "wall4";
        wall4.Attach(new TransformComponent());
        wall4.Attach(new WallComponent());
        wall4.Get<TransformComponent>().Matrix = new Matrix4x3().Identity().Translate(-5, 5, 0).RotateY(-PIOver2).Scale(10);

        for (int i = 0; i < 10; i++)
        {
            Entity ball = Entity.Instantiate();
            ball.Attach(new TransformComponent());
            ball.Attach(new PhysicsComponent());
            ball.Attach(new BallComponent());
            ball.Get<TransformComponent>().Matrix = new Matrix4x3().Identity().Translate(uniform(-5.0f, 5.0f), uniform(3.0f, 5.0f), uniform(-5.0f, 5.0f));
            ball.Get<PhysicsComponent>().Mass = 10.0f;
            ball.Get<PhysicsComponent>().Force = new Vector3(uniform(-1.0f, 1.0f), 0, uniform(-1.0f, 1.0f));
        }
    }
}
