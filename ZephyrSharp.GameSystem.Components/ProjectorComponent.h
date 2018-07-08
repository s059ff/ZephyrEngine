#pragma once

using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// �v���W�F�N�^�[��\���܂��B
            /// </summary>
            public ref class ProjectorComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ���̃N���X�̐V�����C���X�^���X���쐬���܂��B
                /// </summary>
                ProjectorComponent();

                /// <summary>
                /// �������e���[�h��ݒ肵�܂��B
                /// </summary>
                /// <param name="fovY">����p�B</param> 
                /// <param name="aspect">���e�̈�̃A�X�y�N�g��B</param> 
                /// <param name="zn">���e�̈�� Z Near �l�B</param> 
                /// <param name="zf">���e�̈�� Z Far �l�B</param> 
                void SetPerspectiveMode(float fovY, float aspect, float zn, float zf);

                /// <summary>
                /// ���s���e���[�h��ݒ肵�܂��B
                /// </summary>
                /// <param name="width">���e�̈�̕��B</param> 
                /// <param name="height">���e�̈�̍����B</param> 
                /// <param name="zn">���e�̈�� Z Near �l�B</param> 
                /// <param name="zf">���e�̈�� Z Far �l�B</param> 
                void SetOrthogonalMode(float width, float height, float zn, float zf);

                /// <summary>
                /// �v���W�F�N�V�����s����擾���܂��B
                /// </summary>
                Matrix4x4 ProjectionMatrix;
            };
        }
    }
}
