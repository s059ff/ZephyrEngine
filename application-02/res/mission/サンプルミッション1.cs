#define BEGIN 7
#define END 34
#define P() task.ProgressRate = (float)(__LINE__ - BEGIN) / (END - BEGIN)

void start(LoadingTask task)
{
    P(); Entity player = Entity.Instantiate();
    P(); player.Name = "player";
    P(); player.Attach(new TransformComponent());
    P(); player.Attach(new PhysicsComponent());
    P(); player.Attach(new CollisionComponent());
    P(); player.Attach(new JetComponent());
    P(); player.Attach(new AircraftComponent());
    P(); player.Attach(new AIComponent(Friend));
    P(); player.Attach(new PlayerComponent());
    P(); player.Attach(new SquadronComponent("Mobius"));
    P(); player.Attach(new SoundComponent(JetSound));
    P(); player.Get<TransformComponent>().Position = new Vector3(0, 1000, -2000);
    P(); player.Get<SoundComponent>().LoopPlay();

    P(); Entity enemy1 = Entity.Instantiate();
    P(); enemy1.Name = "enemy";
    P(); enemy1.Attach(new TransformComponent());
    P(); enemy1.Attach(new PhysicsComponent());
    P(); enemy1.Attach(new CollisionComponent());
    P(); enemy1.Attach(new JetComponent());
    P(); enemy1.Attach(new AircraftComponent());
    P(); enemy1.Attach(new AIComponent(Enemy));
    P(); enemy1.Attach(new SquadronComponent("Sorcerer"));
    P(); enemy1.Attach(new NPCAIComponent(true));
    P(); enemy1.Attach(new SoundComponent(JetSound));
    P(); enemy1.Get<TransformComponent>().Matrix.RotateY(PI);
    P(); enemy1.Get<TransformComponent>().Position = new Vector3(0, 1000, 2500);
    P(); enemy1.Get<SoundComponent>().LoopPlay();

    GameOverTimer = 0;
}

int GameOverTimer = 0;

void update()
{
    // 敵が全滅したらゲームクリア
    bool existsEnemy = false;
    Entity.ForEach((e) =>
    {
        if (e.Has<AIComponent>())
        {
            if (e.Get<AIComponent>().Group == Enemy)
            {
                existsEnemy = true;
            }
        }
    });
    if (!existsEnemy)
    {
        SceneManager.FookScene(new GameClearScene());
    }

    // 自機の耐久値が０になったらゲームオーバー
    if (Entity.Find("player").Get<AircraftComponent>().Armor <= 0)
    {
        if (30 < GameOverTimer++)
            SceneManager.FookScene(new GameOverScene());
    }
}
