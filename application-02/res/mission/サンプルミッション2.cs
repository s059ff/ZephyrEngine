#define BEGIN 7
#define END 162
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
    P(); enemy1.Name = "enemy1";
    P(); enemy1.Attach(new TransformComponent());
    P(); enemy1.Attach(new PhysicsComponent());
    P(); enemy1.Attach(new CollisionComponent());
    P(); enemy1.Attach(new JetComponent());
    P(); enemy1.Attach(new AircraftComponent());
    P(); enemy1.Attach(new AIComponent(Enemy));
    P(); enemy1.Attach(new SquadronComponent("Sorcerer"));
    P(); enemy1.Attach(new NPCAIComponent());
    P(); enemy1.Attach(new SoundComponent(JetSound));
    P(); enemy1.Get<TransformComponent>().Matrix.RotateY(PI);
    P(); enemy1.Get<TransformComponent>().Position = new Vector3(1000, 1000, 2500);
    P(); enemy1.Get<SoundComponent>().LoopPlay();

    P(); Entity enemy2 = Entity.Instantiate();
    P(); enemy2.Name = "enemy2";
    P(); enemy2.Attach(new TransformComponent());
    P(); enemy2.Attach(new PhysicsComponent());
    P(); enemy2.Attach(new CollisionComponent());
    P(); enemy2.Attach(new JetComponent());
    P(); enemy2.Attach(new AircraftComponent());
    P(); enemy2.Attach(new AIComponent(Enemy));
    P(); enemy2.Attach(new SquadronComponent("Sorcerer"));
    P(); enemy2.Attach(new NPCAIComponent());
    P(); enemy2.Attach(new SoundComponent(JetSound));
    P(); enemy2.Get<TransformComponent>().Matrix.RotateY(PI);
    P(); enemy2.Get<TransformComponent>().Position = new Vector3(1050, 1000, 2520);
    P(); enemy2.Get<SoundComponent>().LoopPlay();

    P(); Entity enemy3 = Entity.Instantiate();
    P(); enemy3.Name = "enemy3";
    P(); enemy3.Attach(new TransformComponent());
    P(); enemy3.Attach(new PhysicsComponent());
    P(); enemy3.Attach(new CollisionComponent());
    P(); enemy3.Attach(new JetComponent());
    P(); enemy3.Attach(new AircraftComponent());
    P(); enemy3.Attach(new AIComponent(Enemy));
    P(); enemy3.Attach(new SquadronComponent("Sorcerer"));
    P(); enemy3.Attach(new NPCAIComponent());
    P(); enemy3.Attach(new SoundComponent(JetSound));
    P(); enemy3.Get<TransformComponent>().Matrix.RotateY(PI);
    P(); enemy3.Get<TransformComponent>().Position = new Vector3(1000 - 50, 1000, 2520);
    P(); enemy3.Get<SoundComponent>().LoopPlay();
    P();
    P(); Entity enemy4 = Entity.Instantiate();
    P(); enemy4.Attach(new TransformComponent());
    P(); enemy4.Attach(new PhysicsComponent());
    P(); enemy4.Attach(new CollisionComponent());
    P(); enemy4.Attach(new JetComponent());
    P(); enemy4.Attach(new AircraftComponent());
    P(); enemy4.Attach(new AIComponent(Enemy));
    P(); enemy4.Attach(new SquadronComponent("Giant"));
    P(); enemy4.Attach(new NPCAIComponent());
    P(); enemy4.Attach(new SoundComponent(JetSound));
    P(); enemy4.Get<TransformComponent>().Matrix.RotateY(PI);
    P(); enemy4.Get<TransformComponent>().Position = new Vector3(-1000, 2000, 2500);
    P(); enemy4.Get<SoundComponent>().LoopPlay();

    P(); Entity enemy5 = Entity.Instantiate();
    P(); enemy5.Attach(new TransformComponent());
    P(); enemy5.Attach(new PhysicsComponent());
    P(); enemy5.Attach(new CollisionComponent());
    P(); enemy5.Attach(new JetComponent());
    P(); enemy5.Attach(new AircraftComponent());
    P(); enemy5.Attach(new AIComponent(Enemy));
    P(); enemy5.Attach(new SquadronComponent("Giant"));
    P(); enemy5.Attach(new NPCAIComponent());
    P(); enemy5.Attach(new SoundComponent(JetSound));
    P(); enemy5.Get<TransformComponent>().Position = new Vector3(-1050, 2000, 2500);
    P(); enemy5.Get<SoundComponent>().LoopPlay();

    P(); Entity friend1 = Entity.Instantiate();
    P(); friend1.Name = "friend1";
    P(); friend1.Attach(new TransformComponent());
    P(); friend1.Attach(new PhysicsComponent());
    P(); friend1.Attach(new CollisionComponent());
    P(); friend1.Attach(new JetComponent());
    P(); friend1.Attach(new AircraftComponent());
    P(); friend1.Attach(new AIComponent(Friend));
    P(); friend1.Attach(new SquadronComponent("Mobius"));
    P(); friend1.Attach(new NPCAIComponent());
    P(); friend1.Attach(new SoundComponent(JetSound));
    P(); friend1.Get<TransformComponent>().Position = new Vector3(-50, 1000, -2050);
    P(); friend1.Get<SoundComponent>().LoopPlay();

    P(); Entity friend2 = Entity.Instantiate();
    P(); friend2.Name = "friend2";
    P(); friend2.Attach(new TransformComponent());
    P(); friend2.Attach(new PhysicsComponent());
    P(); friend2.Attach(new CollisionComponent());
    P(); friend2.Attach(new JetComponent());
    P(); friend2.Attach(new AircraftComponent());
    P(); friend2.Attach(new AIComponent(Friend));
    P(); friend2.Attach(new SquadronComponent("Mobius"));
    P(); friend2.Attach(new NPCAIComponent());
    P(); friend2.Attach(new SoundComponent(JetSound));
    P(); friend2.Get<TransformComponent>().Position = new Vector3(50, 1000, -2050);
    P(); friend2.Get<SoundComponent>().LoopPlay();

    P(); Entity friend3 = Entity.Instantiate();
    P(); friend3.Name = "friend3";
    P(); friend3.Attach(new TransformComponent());
    P(); friend3.Attach(new PhysicsComponent());
    P(); friend3.Attach(new CollisionComponent());
    P(); friend3.Attach(new JetComponent());
    P(); friend3.Attach(new AircraftComponent());
    P(); friend3.Attach(new AIComponent(Friend));
    P(); friend3.Attach(new SquadronComponent("Venom"));
    P(); friend3.Attach(new NPCAIComponent());
    P(); friend3.Attach(new SoundComponent(JetSound));
    P(); friend3.Get<TransformComponent>().Position = new Vector3(0, 1000, -2500);
    P(); friend3.Get<SoundComponent>().LoopPlay();

    P(); Entity friend4 = Entity.Instantiate();
    P(); friend4.Name = "friend4";
    P(); friend4.Attach(new TransformComponent());
    P(); friend4.Attach(new PhysicsComponent());
    P(); friend4.Attach(new CollisionComponent());
    P(); friend4.Attach(new JetComponent());
    P(); friend4.Attach(new AircraftComponent());
    P(); friend4.Attach(new AIComponent(Friend));
    P(); friend4.Attach(new SquadronComponent("Venom"));
    P(); friend4.Attach(new NPCAIComponent());
    P(); friend4.Attach(new SoundComponent(JetSound));
    P(); friend4.Get<TransformComponent>().Position = new Vector3(-50, 1000, -2550);
    P(); friend4.Get<SoundComponent>().LoopPlay();

    P(); Entity friend5 = Entity.Instantiate();
    P(); friend5.Name = "friend5";
    P(); friend5.Attach(new TransformComponent());
    P(); friend5.Attach(new PhysicsComponent());
    P(); friend5.Attach(new CollisionComponent());
    P(); friend5.Attach(new JetComponent());
    P(); friend5.Attach(new AircraftComponent());
    P(); friend5.Attach(new AIComponent(Friend));
    P(); friend5.Attach(new SquadronComponent("Venom"));
    P(); friend5.Attach(new NPCAIComponent());
    P(); friend5.Attach(new SoundComponent(JetSound));
    P(); friend5.Get<TransformComponent>().Position = new Vector3(50, 1000, -2550);
    P(); friend5.Get<SoundComponent>().LoopPlay();

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
