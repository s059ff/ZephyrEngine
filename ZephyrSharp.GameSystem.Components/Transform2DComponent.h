#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 2D 空間におけるエンティティの位置を表します。
            /// </summary>
            public ref class Transform2DComponent : public EntityComponent
            {
            public:

                Transform2DComponent()
                {
                    this->Matrix.Identity();
                }

                /// <summary>
                /// エンティティの姿勢行列を表します。
                /// </summary>
                Matrix3x2 Matrix;

            public:

                /// <summary>
                /// エンティティの +X 方向のベクトルを取得します。
                /// </summary>
                property Vector2 Rightward { Vector2 get() { return Vector2(Matrix.M11, Matrix.M12); }};

                /// <summary>
                /// エンティティの +Y 方向のベクトルを取得します。
                /// </summary>
                property Vector2 Upward { Vector2 get() { return Vector2(Matrix.M21, Matrix.M22); }};

                /// <summary>
                /// エンティティの位置を表します。
                /// </summary>
                property Vector2 Position
                {
                    Vector2 get() { return Matrix.Position; }

                    void set(Vector2 value) { Matrix.Position = value; }
                }
            };
        }
    }
}
