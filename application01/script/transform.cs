#include "common.csh"

void identity()
{
    _world.Identity();
}

void translate(float x, float y, float z)
{
    _world.Translate(x, y, z);
}

void translate(float x, float y)
{
    _world.Translate(x, y);
}

void translate(Vector3 v)
{
    _world.Translate(v.X, v.Y, v.Z);
}

void translate(Vector2 v)
{
    _world.Translate(v.X, v.Y, 0);
}

void rotate(float r)
{
    _world.RotateZ(r);
}

void scale(float sx, float sy)
{
    _world.Scale(sx, sy, 1.0f);
}

void scale(float s)
{
    _world.Scale(s);
}

void transform(Matrix4x3 m)
{
    _world.Transform(new Matrix4x4(m));
}

void transform(Matrix4x4 m)
{
    _world.Transform(m);
}

void pushMatrix()
{
    _matrix_stack.Push(_world);
}

void popMatrix()
{
    _world = _matrix_stack.Pop();
}

void loadMatrix(Matrix3x2 m)
{
    _world = new Matrix4x4(m);
}

void loadMatrix(Matrix4x3 m)
{
    _world = new Matrix4x4(m);
}

void loadMatrix(Matrix4x4 m)
{
    _world = m;
}

Matrix4x4 _world = new Matrix4x4().Identity();

Stack<Matrix4x4> _matrix_stack = new Stack<Matrix4x4>();
