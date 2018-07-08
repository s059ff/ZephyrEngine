/**
 * ゲームシステムモニターテスト
 */

using System;
using System.Threading;
using System.Windows.Forms;
using ZephyrSharp.GameSystem;
using ZephyrSharp.Linalg;
using ZephyrTools.GameSystemMonitor;

class A : EntityComponent
{
    public Matrix4x3 Matrix;
    public Vector3 Position
    {
        get { return Matrix.Position; }
        set { Matrix.Position = value; }
    }
}

class B : EntityComponent
{
    public string Member = "Hello, world!!!";
}

class Program
{
    static GameSystemMonitor viewer;

    static void Main(string[] args)
    {
        new Thread(() =>
        {
            viewer = GameSystemMonitor.Execute();
            Application.Run(viewer);
        }).Start();

        while (true)
        {
            var key = Console.Read();
            if (key == 'A')
            {
                var e = Entity.Instantiate();
                e.Name = new System.Random().Next().ToString();
            }
            if (key == 'B')
            {
                Entity.ForEach(e =>
                {
                    if (e.ID == 1)
                    {
                        if (!e.Has<A>())
                            e.Attach(new A());
                    }
                    if (e.ID == 2)
                    {
                        if (!e.Has<A>())
                            e.Attach(new A());
                        if (!e.Has<B>())
                            e.Attach(new B());
                    }
                });
            }
            if (key == 'E')
            {
                Entity.ForEach(e =>
                {
                });
            }
            if (key == 'C')
            {
                Entity.Clear();
            }
            if (key == 'Q')
                break;

            Entity.Update();
        }
    }
}
