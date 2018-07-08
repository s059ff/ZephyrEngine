const int FriendNum = 0;
const int EnemyNum = 8;

for (int i = 0; i<FriendNum; i++)
{
Entity friend = Entity.Instantiate();
friend.Attach(new TransformComponent());
friend.Attach(new PhysicsComponent());
friend.Attach(new CollisionComponent());
friend.Attach(new JetComponent());
friend.Attach(new AircraftComponent());
friend.Attach(new AIComponent(Friend));
friend.Attach(new SquadronComponent("Mobius"));
friend.Attach(new NPCAIComponent());
friend.Attach(new SoundComponent(JetSound));
friend.Get<TransformComponent>().Matrix.RotateY(uniform(0, PI2));
friend.Get<TransformComponent>().Position = new Vector3(uniform(-2500, 2500), 1000, uniform(-2500, 2500));
friend.Get<SoundComponent>().LoopPlay();
}

for (int i = 0; i<EnemyNum; i++)
{
Entity enemy = Entity.Instantiate();
enemy.Attach(new TransformComponent());
enemy.Attach(new PhysicsComponent());
enemy.Attach(new CollisionComponent());
enemy.Attach(new JetComponent());
enemy.Attach(new AircraftComponent());
enemy.Attach(new AIComponent(Enemy));
enemy.Attach(new SquadronComponent("Nemesis"));
enemy.Attach(new NPCAIComponent());
enemy.Attach(new SoundComponent(JetSound));
enemy.Get<TransformComponent>().Matrix.RotateY(uniform(0, PI2));
enemy.Get<TransformComponent>().Position = new Vector3(uniform(-2500, 2500), 1000, uniform(-2500, 2500));
enemy.Get<SoundComponent>().LoopPlay();
}
