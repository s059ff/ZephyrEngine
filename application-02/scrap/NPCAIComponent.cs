using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XepherSharp.AI;
using XepherSharp.Collision;
using XepherSharp.GameSystem;
using XepherSharp.GameSystem.Components;
using XepherSharp.Math;
using static Script;

class NPCAIComponent : CustomEntityComponent
{
    NeuralNetwork CollisionPredictionNetwork = new NeuralNetwork();

    MatrixXd X = MatrixXd.Zero(3, 8192);
    MatrixXd D = MatrixXd.Zero(1, 8192);

    int N = 0;

    public double Loss = 0;
    public double RiskPredict = 0;
    public float Distance;
    public float Height;
    public float UpwardY;
    public double ε { get { return CollisionPredictionNetwork.ε; } set { CollisionPredictionNetwork.ε = value; } }

    StreamWriter sw = new StreamWriter("error.txt");

    /**
     * input
     * [0] distance (forward ----> ground)
     * [1] height from ground
     * [2] theta (roll angle)
     */

    public NPCAIComponent()
    {
        if (!File.Exists("network.bin"))
        {
            CollisionPredictionNetwork.Load("network.bin");
        }
        else
        {
            CollisionPredictionNetwork.Attach(3, "linear", "dlinear");
            CollisionPredictionNetwork.Attach(6, "relu", "drelu");
            CollisionPredictionNetwork.Attach(1, "linear", "dlinear");
            CollisionPredictionNetwork.ε = 0.1f;
        }
    }

    protected override void OnAttach()
    {
        base.OnAttach();

        Owner.Get<CollisionComponent>().Collided += Collided;

        this.Reposition();
    }

    protected override void OnDestroy()
    {
        base.OnDestroy();

        CollisionPredictionNetwork.Save("network.bin");
    }

    private void Collided(Entity other, Vector3 point)
    {
        this.Train();
        this.Reposition();
    }

    private void Train()
    {
        if (N == 0)
            return;

        CollisionPredictionNetwork.Train(X.Block(0, 0, 3, N), D.Block(0, 0, 1, N));

        this.N = 0;
        this.Loss = 0.9 * this.Loss + 0.1 * CollisionPredictionNetwork.Loss;

        sw.WriteLine(this.Loss);
        Console.WriteLine(this.Loss);
    }

    private void Reposition()
    {
        var curvedSurface = (Entity.Find("ground").Get<CollisionComponent>().Shape as CurvedSurface);
        curvedSurface.Matrix = Entity.Find("ground").Get<TransformComponent>().Matrix;

        Transform.Matrix.Identity();
        Transform.Matrix.Translate(normal(0, 10), 0, normal(0, 10));
        float height = curvedSurface.ComputeHeight(Transform.Position);
        Transform.Matrix.Translate(0, -height + uniform(250, 400), 0);
        Transform.Matrix.RotateY(uniform(0, PI * 2));
        Transform.Matrix.RotateX(uniform(PI / 6, PI / 3));
    }

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        if (message as string == UpdateMessage)
        {
            this.Update();
        }
    }

    private void Update()
    {
        Owner.Get<AircraftComponent>().Accelerate();

        //var destination = Transform.Position + new Vector3(0, 1, 0);
        //Owner.Get<AIComponent>().AutoPilot(destination);

        var curvedSurface = (Entity.Find("ground").Get<CollisionComponent>().Shape as CurvedSurface);

        float distance = 0;
        {
            Point ray = new Point()
            {
                Matrix = new Matrix4x3().Identity().Translate(Transform.Position),
                Velocity = Transform.Forward * 1000
            };
            var point = curvedSurface.Collide(ray);
            if (float.IsNaN(point.X))
                distance = 1;
            else
                distance = (Transform.Position - point).Magnitude / 1000;
        }

        float height = curvedSurface.ComputeHeight(Transform.Position) / 500;

        float upwardY = Transform.Upward.Y;

        if (frame % 10 == 0)
        {
            X[0, N] = distance;
            X[1, N] = height;
            X[2, N] = upwardY;
            D[0, N] = distance;
            N++;
        }
        assert(N < 8192);

        MatrixXd x = MatrixXd.Zero(3, 1);
        x[0, 0] = distance;
        x[1, 0] = height;
        X[2, N] = upwardY;
        this.RiskPredict = CollisionPredictionNetwork.Forward(x)[0, 0];
        this.Distance = distance;
        this.Height = height;
        this.UpwardY = upwardY;
    }

#if false
    public override void Update__(AIInput input)
    {
        var aircraft = input.Myself.Get<AircraftComponent>();
        var transform = input.Myself.Get<TransformComponent>();

        if (aircraft.Armor == 0.0f)
            return;

        if (input.Target != null)
        {
            Vector3 destination = input.Target.Get<TransformComponent>().Position;

            // (逃げる)
            if (frame % 2400 > 1200)
            //if (false)
            {
                aircraft.Decelerate();
            }
            else
            {
                // （攻撃する）
                if (uniform(0, 1000) == 0 && aircraft.Locking)
                {
                    aircraft.Attack();
                }

                aircraft.Accelerate();
            }

            // (自動操縦)
            var p = destination * transform.Matrix.Inverse;

            if (0.2f < Vector3.Angle(new Vector3(p.X, p.Y, 0), new Vector3(0, 1, 0)))
            {
                aircraft.Roll((p.X > 0) ? 0.5f : -0.5f);
            }
            else
            {
                // 上に曲がる
                if (0.2f < abs(Vector3.Angle(p, new Vector3(0, 0, 1))))
                {
                    aircraft.Pitch(-1.0f);
                }
            }
        }
        else
        {
        }
    } 
#endif
}
