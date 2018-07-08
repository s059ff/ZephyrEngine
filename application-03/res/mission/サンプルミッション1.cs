void start()
{
    Entity player = Entity.Instantiate();
    player.Name = "player";
    player.Attach(new TransformComponent());
    player.Attach(new PhysicsComponent());
    player.Attach(new CollisionComponent());
    player.Attach(new JetComponent());
    player.Attach(new AircraftComponent());
    player.Attach(new AIComponent(Friend));
    player.Attach(new PlayerComponent());
    player.Attach(new SquadronComponent("Mobius"));
    player.Attach(new SoundComponent(JetSound));
    player.Get<TransformComponent>().Position = new Vector3(0, 1000, -2000);
    player.Get<SoundComponent>().LoopPlay();

    Entity enemy1 = Entity.Instantiate();
    enemy1.Name = "enemy";
    enemy1.Attach(new TransformComponent());
    enemy1.Attach(new PhysicsComponent());
    enemy1.Attach(new CollisionComponent());
    enemy1.Attach(new JetComponent());
    enemy1.Attach(new AircraftComponent());
    enemy1.Attach(new AIComponent(Enemy));
    enemy1.Attach(new SquadronComponent("Sorcerer"));
    enemy1.Attach(new NPCAIComponent(true));
    enemy1.Attach(new SoundComponent(JetSound));
    enemy1.Get<TransformComponent>().Matrix.RotateY(PI);
    enemy1.Get<TransformComponent>().Position = new Vector3(0, 1000, 2500);
    enemy1.Get<SoundComponent>().LoopPlay();

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
        SceneManager.SetNextScene(new GameClearScene());
    }

    // 自機の耐久値が０になったらゲームオーバー
    if (Entity.Find("player").Get<AircraftComponent>().Armor <= 0)
    {
        if (30 < GameOverTimer++)
            SceneManager.SetNextScene(new GameOverScene());
    }
}
