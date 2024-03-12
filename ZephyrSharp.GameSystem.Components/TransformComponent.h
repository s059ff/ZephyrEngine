#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 3D 空間におけるエンティティの位置を表します。
            /// </summary>
            public ref class TransformComponent : public EntityComponent
            {
            public:

                TransformComponent()
                {
                    this->Matrix.Identity();
                }
                
                /// <summary>
                /// エンティティの姿勢行列を表します。
                /// </summary>
                Matrix4x3 Matrix;

            public:

                /// <summary>
                /// エンティティの +X 方向のベクトルを取得します。
                /// </summary>
                property Vector3 Rightward { Vector3 get() { return Vector3(Matrix.M11, Matrix.M12, Matrix.M13); }};

                /// <summary>
                /// エンティティの +Y 方向のベクトルを取得します。
                /// </summary>
                property Vector3 Upward { Vector3 get() { return Vector3(Matrix.M21, Matrix.M22, Matrix.M23); }};

                /// <summary>
                /// エンティティの +Z 方向のベクトルを取得します。
                /// </summary>
                property Vector3 Forward { Vector3 get() { return Vector3(Matrix.M31, Matrix.M32, Matrix.M33); }};

                /// <summary>
                /// エンティティの位置を表します。
                /// </summary>
                property Vector3 Position
                {
                    Vector3 get() { return Matrix.Position; }

                    void set(Vector3 value) { Matrix.Position = value; }
                }
            };
        }
    }
}
