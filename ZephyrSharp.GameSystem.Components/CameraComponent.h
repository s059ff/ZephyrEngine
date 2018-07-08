#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// �J������\���܂��B
            /// </summary>
            public ref class CameraComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ����n�_����ʂ̂���n�_�𒍎�����悤�ɃJ�����̌�����ݒ肵�܂��B
                /// </summary>
                /// <param name="eye">�J�����̍��W�B</param> 
                /// <param name="at">������̍��W�B</param> 
                void LookAt(Vector3 eye, Vector3 at);

                /// <summary>
                /// �r���[�C���O�s����擾���܂��B
                /// </summary>
                property Matrix4x3 ViewingMatrix { Matrix4x3 get(); }
            };
        }
    }
}
