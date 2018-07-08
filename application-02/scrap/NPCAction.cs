using System;
using XepherSharp.AI;
using XepherSharp.Collision;
using XepherSharp.GameSystem;
using XepherSharp.GameSystem.Components;
using XepherSharp.Math;
using static Script;

class NPCAction : AIAction
{
    const int N = 64;
    const int S = 3;
    const int A = 1;

    QNetwork QNetwork = new QNetwork(N, S, A);

    MatrixXd s, a, s_, a_;
    RowVectorXd r;

    Vector3 destination;

    LineSegment ray1 = new LineSegment();
    LineSegment ray2 = new LineSegment();

    public NPCAction()
    {
        s = MatrixXd.Zero(S, N);
        a = MatrixXd.Zero(A, N);
        s_ = MatrixXd.Zero(S, N);
        a_ = MatrixXd.Zero(A, N);
        r = RowVectorXd.Zero(N);
    }

    double computeState0(AIInput input)
    {
        var transform = input.Myself.Get<TransformComponent>();

        Vector3 v1 = transform.Forward;
        Vector3 v2 = new Vector3(v1.X, 0, v1.Z);
        return Vector3.Angle(v1, v2);
    }

    double computeState1(AIInput input)
    {
        var transform = input.Myself.Get<TransformComponent>();

        LineSegment segment = new LineSegment();
        segment.Matrix.Identity();
        segment.Matrix.Translate(transform.Position);
        segment.Direction = transform.Forward * 300;
        var point = Entity.Find("ground").Get<CollisionComponent>().Shape.Collide((AbstractShape)segment);
        if (float.IsNaN(point.X))
            return 300;
        else
        {
            return (transform.Position - point).Magnitude;
        }
    }

    double computeState2(AIInput input)
    {
        var transform = input.Myself.Get<TransformComponent>();

        LineSegment segment = new LineSegment();
        segment.Matrix.Identity();
        segment.Matrix.Translate(transform.Position);
        segment.Direction = new Vector3(0, -300, 0);
        var point = Entity.Find("ground").Get<CollisionComponent>().Shape.Collide((AbstractShape)segment);
        if (float.IsNaN(point.X))
            return 300;
        else
        {
            return (transform.Position - point).Magnitude;
        }
    }

    double computeReward(AIInput input)
    {
        Vector3 point;

        var collision1 = input.Myself.Get<CollisionComponent>().Shape;
        if (collision1.Velocity.Magnitude == 0)
        {
            var transform = input.Myself.Get<TransformComponent>();

            LineSegment segment = new LineSegment();
            segment.Matrix.Identity();
            segment.Matrix.Translate(transform.Position);
            segment.Direction = new Vector3(0, -300, 0);
            point = Entity.Find("ground").Get<CollisionComponent>().Shape.Collide((AbstractShape)segment);
            if (float.IsNaN(point.X))
                return 1.0f / 300.0f;
            else
            {
                return 1.0f / (transform.Position - point).Magnitude;
            }
        }
        var collision2 = Entity.Find("ground").Get<CollisionComponent>().Shape;
        point = collision2.Collide(collision1);
        if (!float.IsNaN(point.X))
        {
            return -100;
        }
        else
        {
            var transform = input.Myself.Get<TransformComponent>();

            LineSegment segment = new LineSegment();
            segment.Matrix.Identity();
            segment.Matrix.Translate(transform.Position);
            segment.Direction = new Vector3(0, -300, 0);
            point = Entity.Find("ground").Get<CollisionComponent>().Shape.Collide((AbstractShape)segment);
            if (float.IsNaN(point.X))
                return 1.0f / 300.0f;
            else
            {
                return 1.0f / (transform.Position - point).Magnitude;
            }
        }
    }

    public override void Update(AIInput input)
    {
        var ai = input.Myself.Get<AIComponent>();
        var aircraft = input.Myself.Get<AircraftComponent>();
        var transform = input.Myself.Get<TransformComponent>();

        if (aircraft.Armor == 0.0f)
            return;

        int n = frame % N;
        for (int i = 0; i < A; i++)
        {
            a[i, n] = a_[i, n];
        }
        for (int i = 0; i < S; i++)
        {
            s[i, n] = s_[i, n];
        }
        r[n] = computeReward(input);

        s[0, n] = computeState0(input);
        s[1, n] = computeState1(input);
        s[2, n] = computeState2(input);

        float q1 = (float)QNetwork.Value(s.Col(n), new VectorXd(new double[] { 0 }));
        float q2 = (float)QNetwork.Value(s.Col(n), new VectorXd(new double[] { 1 }));
        float min_ = min(q1, q2);
        q1 += -min_;
        q2 += -min_;
        if (q1 == 0 && q2 == 0)
        {
            q1 = q2 = 1;
        }

        double _a = random(new float[] { q1, q2 });
        a[0, n] = _a;

        destination = transform.Position;
        destination.Y += _a == 0 ? 1 : -1;

        ai.AutoPilot(destination);

        if (n == N - 1)
        {
            QNetwork.Update(s, a, s_, a_, r);
        }
    }
}
