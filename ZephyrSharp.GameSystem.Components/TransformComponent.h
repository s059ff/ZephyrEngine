#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// 3D ��Ԃɂ�����G���e�B�e�B�̈ʒu��\���܂��B
            /// </summary>
            public ref class TransformComponent : public EntityComponent
            {
            public:

                TransformComponent()
                {
                    this->Matrix.Identity();
                }
                
                /// <summary>
                /// �G���e�B�e�B�̎p���s���\���܂��B
                /// </summary>
                Matrix4x3 Matrix;

            public:

                /// <summary>
                /// �G���e�B�e�B�� +X �����̃x�N�g�����擾���܂��B
                /// </summary>
                property Vector3 Rightward { Vector3 get() { return Vector3(Matrix.M11, Matrix.M12, Matrix.M13); }};

                /// <summary>
                /// �G���e�B�e�B�� +Y �����̃x�N�g�����擾���܂��B
                /// </summary>
                property Vector3 Upward { Vector3 get() { return Vector3(Matrix.M21, Matrix.M22, Matrix.M23); }};

                /// <summary>
                /// �G���e�B�e�B�� +Z �����̃x�N�g�����擾���܂��B
                /// </summary>
                property Vector3 Forward { Vector3 get() { return Vector3(Matrix.M31, Matrix.M32, Matrix.M33); }};

                /// <summary>
                /// �G���e�B�e�B�̈ʒu��\���܂��B
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
