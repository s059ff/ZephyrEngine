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
    enemy1.Name = "enemy1";
    enemy1.Attach(new TransformComponent());
    enemy1.Attach(new PhysicsComponent());
    enemy1.Attach(new CollisionComponent());
    enemy1.Attach(new JetComponent());
    enemy1.Attach(new AircraftComponent());
    enemy1.Attach(new AIComponent(Enemy));
    enemy1.Attach(new SquadronComponent("Sorcerer"));
    enemy1.Attach(new NPCAIComponent());
    enemy1.Attach(new SoundComponent(JetSound));
    enemy1.Get<TransformComponent>().Matrix.RotateY(PI);
    enemy1.Get<TransformComponent>().Position = new Vector3(1000, 1000, 2500);
    enemy1.Get<SoundComponent>().LoopPlay();

    Entity enemy2 = Entity.Instantiate();
    enemy2.Name = "enemy2";
    enemy2.Attach(new TransformComponent());
    enemy2.Attach(new PhysicsComponent());
    enemy2.Attach(new CollisionComponent());
    enemy2.Attach(new JetComponent());
    enemy2.Attach(new AircraftComponent());
    enemy2.Attach(new AIComponent(Enemy));
    enemy2.Attach(new SquadronComponent("Sorcerer"));
    enemy2.Attach(new NPCAIComponent());
    enemy2.Attach(new SoundComponent(JetSound));
    enemy2.Get<TransformComponent>().Matrix.RotateY(PI);
    enemy2.Get<TransformComponent>().Position = new Vector3(1050, 1000, 2520);
    enemy2.Get<SoundComponent>().LoopPlay();

    Entity enemy3 = Entity.Instantiate();
    enemy3.Name = "enemy3";
    enemy3.Attach(new TransformComponent());
    enemy3.Attach(new PhysicsComponent());
    enemy3.Attach(new CollisionComponent());
    enemy3.Attach(new JetComponent());
    enemy3.Attach(new AircraftComponent());
    enemy3.Attach(new AIComponent(Enemy));
    enemy3.Attach(new SquadronComponent("Sorcerer"));
    enemy3.Attach(new NPCAIComponent());
    enemy3.Attach(new SoundComponent(JetSound));
    enemy3.Get<TransformComponent>().Matrix.RotateY(PI);
    enemy3.Get<TransformComponent>().Position = new Vector3(1000 - 50, 1000, 2520);
    enemy3.Get<SoundComponent>().LoopPlay();
    
    Entity enemy4 = Entity.Instantiate();
    enemy4.Attach(new TransformComponent());
    enemy4.Attach(new PhysicsComponent());
    enemy4.Attach(new CollisionComponent());
    enemy4.Attach(new JetComponent());
    enemy4.Attach(new AircraftComponent());
    enemy4.Attach(new AIComponent(Enemy));
    enemy4.Attach(new SquadronComponent("Giant"));
    enemy4.Attach(new NPCAIComponent());
    enemy4.Attach(new SoundComponent(JetSound));
    enemy4.Get<TransformComponent>().Matrix.RotateY(PI);
    enemy4.Get<TransformComponent>().Position = new Vector3(-1000, 2000, 2500);
    enemy4.Get<SoundComponent>().LoopPlay();

    Entity enemy5 = Entity.Instantiate();
    enemy5.Attach(new TransformComponent());
    enemy5.Attach(new PhysicsComponent());
    enemy5.Attach(new CollisionComponent());
    enemy5.Attach(new JetComponent());
    enemy5.Attach(new AircraftComponent());
    enemy5.Attach(new AIComponent(Enemy));
    enemy5.Attach(new SquadronComponent("Giant"));
    enemy5.Attach(new NPCAIComponent());
    enemy5.Attach(new SoundComponent(JetSound));
    enemy5.Get<TransformComponent>().Position = new Vector3(-1050, 2000, 2500);
    enemy5.Get<SoundComponent>().LoopPlay();

    Entity friend1 = Entity.Instantiate();
    friend1.Name = "friend1";
    friend1.Attach(new TransformComponent());
    friend1.Attach(new PhysicsComponent());
    friend1.Attach(new CollisionComponent());
    friend1.Attach(new JetComponent());
    friend1.Attach(new AircraftComponent());
    friend1.Attach(new AIComponent(Friend));
    friend1.Attach(new SquadronComponent("Mobius"));
    friend1.Attach(new NPCAIComponent());
    friend1.Attach(new SoundComponent(JetSound));
    friend1.Get<TransformComponent>().Position = new Vector3(-50, 1000, -2050);
    friend1.Get<SoundComponent>().LoopPlay();

    Entity friend2 = Entity.Instantiate();
    friend2.Name = "friend2";
    friend2.Attach(new TransformComponent());
    friend2.Attach(new PhysicsComponent());
    friend2.Attach(new CollisionComponent());
    friend2.Attach(new JetComponent());
    friend2.Attach(new AircraftComponent());
    friend2.Attach(new AIComponent(Friend));
    friend2.Attach(new SquadronComponent("Mobius"));
    friend2.Attach(new NPCAIComponent());
    friend2.Attach(new SoundComponent(JetSound));
    friend2.Get<TransformComponent>().Position = new Vector3(50, 1000, -2050);
    friend2.Get<SoundComponent>().LoopPlay();

    Entity friend3 = Entity.Instantiate();
    friend3.Name = "friend3";
    friend3.Attach(new TransformComponent());
    friend3.Attach(new PhysicsComponent());
    friend3.Attach(new CollisionComponent());
    friend3.Attach(new JetComponent());
    friend3.Attach(new AircraftComponent());
    friend3.Attach(new AIComponent(Friend));
    friend3.Attach(new SquadronComponent("Venom"));
    friend3.Attach(new NPCAIComponent());
    friend3.Attach(new SoundComponent(JetSound));
    friend3.Get<TransformComponent>().Position = new Vector3(0, 1000, -2500);
    friend3.Get<SoundComponent>().LoopPlay();

    Entity friend4 = Entity.Instantiate();
    friend4.Name = "friend4";
    friend4.Attach(new TransformComponent());
    friend4.Attach(new PhysicsComponent());
    friend4.Attach(new CollisionComponent());
    friend4.Attach(new JetComponent());
    friend4.Attach(new AircraftComponent());
    friend4.Attach(new AIComponent(Friend));
    friend4.Attach(new SquadronComponent("Venom"));
    friend4.Attach(new NPCAIComponent());
    friend4.Attach(new SoundComponent(JetSound));
    friend4.Get<TransformComponent>().Position = new Vector3(-50, 1000, -2550);
    friend4.Get<SoundComponent>().LoopPlay();

    Entity friend5 = Entity.Instantiate();
    friend5.Name = "friend5";
    friend5.Attach(new TransformComponent());
    friend5.Attach(new PhysicsComponent());
    friend5.Attach(new CollisionComponent());
    friend5.Attach(new JetComponent());
    friend5.Attach(new AircraftComponent());
    friend5.Attach(new AIComponent(Friend));
    friend5.Attach(new SquadronComponent("Venom"));
    friend5.Attach(new NPCAIComponent());
    friend5.Attach(new SoundComponent(JetSound));
    friend5.Get<TransformComponent>().Position = new Vector3(50, 1000, -2550);
    friend5.Get<SoundComponent>().LoopPlay();

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
