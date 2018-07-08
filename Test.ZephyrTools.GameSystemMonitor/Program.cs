/**
 * ゲームシステムモニターテスト
 */

using System;
using System.Linq;
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

        Console.WriteLine("===============================");
        Console.WriteLine("Usage:");
        Console.WriteLine("instantiate %1 [%2 %3 ...]");
        Console.WriteLine("\tCreate a new entity which named %1, %2, %3....");
        Console.WriteLine("kill %1 [%2 %3 ...]");
        Console.WriteLine("\tKill a entity which named %1, %2, %3....");
        Console.WriteLine("clear");
        Console.WriteLine("\tClear all entities.");
        Console.WriteLine("attach %1 to %2");
        Console.WriteLine("\tAttach %1(component) to %2(entity).");
        Console.WriteLine("detach %1 to %2");
        Console.WriteLine("\tDetach %1(component) from %2(entity).");
        Console.WriteLine("quit | q");
        Console.WriteLine("\tQuit this program.");
        Console.WriteLine("===============================");
        Console.WriteLine();

        while (true)
        {
            Console.Write(">");
            var words = Console.ReadLine().ToLower().Trim().Split(' ');
            var command = words[0];
            var arguments = (words.Length > 0) ? words.Skip(1).ToArray() : null;
            switch (command)
            {
                case "instantiate":
                    if (arguments == null)
                    {
                        Console.WriteLine("Error: Not specified entity name.");
                        break;
                    }
                    else
                    {
                        foreach (var name in arguments)
                        {
                            if (Entity.Find(e => e.Name == name) != null)
                            {
                                Console.WriteLine("Error: Already exists entity which same name.");
                                break;
                            }
                            var entity = Entity.Instantiate();
                            entity.Name = name;
                        }
                    }
                    break;

                case "kill":
                    if (arguments == null)
                    {
                        Console.WriteLine("Error: Not specified entity name.");
                        break;
                    }
                    else
                    {
                        foreach (var name in arguments)
                        {
                            var entity = Entity.Find(e => e.Name == name);
                            if (entity == null)
                            {
                                Console.WriteLine("Error: Not exists specified entity.");
                                break;
                            }
                            Entity.Kill(entity);
                        }
                    }
                    break;

                case "clear":
                    Entity.Clear();
                    break;

                case "attach":
                    if (arguments.Length != 3)
                    {
                        Console.WriteLine("Error: Wrong command.");
                        break;
                    }
                    if (arguments[1] != "to")
                    {
                        Console.WriteLine("Error: Wrong command.");
                        break;
                    }
                    {
                        var componentName = arguments[0];
                        var entityName = arguments[2];
                        var entity = Entity.Find(e => e.Name == entityName);
                        var component = (componentName == "a") ? new A() : ((componentName == "b") ? new B() : null as EntityComponent);
                        if (entity == null)
                        {
                            Console.WriteLine("Error: Not exists specified entity.");
                            break;
                        }
                        if (component == null)
                        {
                            Console.WriteLine("Error: Not exists specified component.");
                            break;
                        }
                        if (!entity.Has(component.GetType()))
                            entity.Attach(component);
                    }
                    break;

                case "detach":
                    if (arguments.Length != 3)
                    {
                        Console.WriteLine("Error: Wrong command.");
                        break;
                    }
                    if (arguments[1] != "from")
                    {
                        Console.WriteLine("Error: Wrong command.");
                        break;
                    }
                    {
                        var componentName = arguments[0];
                        var entityName = arguments[2];
                        var entity = Entity.Find(e => e.Name == entityName);
                        var componentType = (componentName == "a") ? typeof(A) : ((componentName == "b") ? typeof(B) : null as Type);
                        if (entity == null)
                        {
                            Console.WriteLine("Error: Not exists specified entity.");
                            break;
                        }
                        if (componentType == null)
                        {
                            Console.WriteLine("Error: Not exists specified component.");
                        }
                        if (entity.Has(componentType))
                            entity.Detach(componentType);
                    }
                    break;

                case "quit":
                    Application.Exit();
                    break;

                case "q":
                    Application.Exit();
                    break;

                default:
                    Console.WriteLine("Error: Wrong command.");
                    break;
            }

            Entity.Update();
        }
    }
}
