using System.Collections.Generic;
using ZephyrSharp.Linalg;
using static EngineScript;
using static GameScript;

class CameraComponent : CustomEntityComponent
{
    public void LookAt(Vector3 eye, Vector3 at)
    {
        this.Transform.Matrix.LookAt(eye, at);
    }

    public new Matrix4x3 ViewingMatrix { get { return this.Transform.Matrix.Inverse; } }

    public Matrix4x3 TrackingPose { get; set; } = new Matrix4x3().Identity();

    public Matrix3x3 AngleOffset = new Matrix3x3().Identity();

    public Vector3 GazingPoint { get; set; }

    public Vector3 TrackingOffset { get; set; }

    public bool EnableTracking { get; set; } = false;

    public bool EnableGazing { get; set; } = false;

    public int TrackingLatency = 12;

    protected override void ReceiveMessage(object message, object argument)
    {
        base.ReceiveMessage(message, argument);

        switch (message as string)
        {
            case UpdateMessage:
                this.Update();
                break;

            default:
                break;
        }
    }

    void Update()
    {
        if (this.EnableTracking)
        {
            if (this.TrackingLatency > this.targetPoses.Count)
            {
                for (int i = 0; i < this.TrackingLatency - this.targetPoses.Count; i++)
                {
                    if (0 < this.targetPoses.Count)
                        this.targetPoses.AddFirst(this.targetPoses.First.Value);
                    else
                        this.targetPoses.AddFirst(new Matrix4x3().Identity());
                }
            }
            else if (this.TrackingLatency < this.targetPoses.Count)
            {
                for (int i = 0; i < this.targetPoses.Count - this.TrackingLatency; i++)
                {
                    this.targetPoses.RemoveFirst();
                }
            }
            if (this.TrackingLatency > 0)
            {
                this.Transform.Matrix = this.targetPoses.Last.Value;
            }
            else
                this.Transform.Matrix = this.TrackingPose;
        }
        else
        {
            this.Transform.Matrix._Matrix3x3 *= new Matrix3x3(this.angleAdjustment).Inverse;
        }

        if (this.EnableGazing)
        {
            var f = this.Transform.Forward;
            var r = (this.GazingPoint - this.Transform.Position).Normalize();
            var a = Vector3.Outer(f, r).Normalize();
            var theta = Vector3.Angle(f, r);
            this.angleAdjustment = Quaternion.Slerp(this.angleAdjustment, new Quaternion(a, theta), 0.1f);
        }
        else
        {
            if (abs(this.angleAdjustment.W) < .9999f)
                this.angleAdjustment = Quaternion.Slerp(this.angleAdjustment, new Quaternion(this.angleAdjustment.Axis.Normalize(), 0), 0.1f);
        }

        this.Transform.Matrix._Matrix3x3 = this.AngleOffset * this.Transform.Matrix._Matrix3x3;
        this.Transform.Matrix._Matrix3x3 *= new Matrix3x3(this.angleAdjustment);

        if (this.EnableTracking)
        {
            this.Transform.Position = Vector3.Zero;
            this.Transform.Matrix.Translate(this.TrackingOffset);
            this.Transform.Position += this.TrackingPose.Position;

            if (this.TrackingLatency > 0)
            {
                this.targetPoses.RemoveLast();
                this.targetPoses.AddFirst(this.TrackingPose);
            }
        }
    }

    LinkedList<Matrix4x3> targetPoses = new LinkedList<Matrix4x3>();

    Quaternion angleAdjustment = new Quaternion().Identity();
}
