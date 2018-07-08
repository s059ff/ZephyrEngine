#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 2D ��Ԃɂ�����G���e�B�e�B�̈ʒu��\���܂��B
            /// </summary>
            public ref class Transform2DComponent : public EntityComponent
            {
            public:

                Transform2DComponent()
                {
                    this->Matrix.Identity();
                }

                /// <summary>
                /// �G���e�B�e�B�̎p���s���\���܂��B
                /// </summary>
                Matrix3x2 Matrix;

            public:

                /// <summary>
                /// �G���e�B�e�B�� +X �����̃x�N�g�����擾���܂��B
                /// </summary>
                property Vector2 Rightward { Vector2 get() { return Vector2(Matrix.M11, Matrix.M12); }};

                /// <summary>
                /// �G���e�B�e�B�� +Y �����̃x�N�g�����擾���܂��B
                /// </summary>
                property Vector2 Upward { Vector2 get() { return Vector2(Matrix.M21, Matrix.M22); }};

                /// <summary>
                /// �G���e�B�e�B�̈ʒu��\���܂��B
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
