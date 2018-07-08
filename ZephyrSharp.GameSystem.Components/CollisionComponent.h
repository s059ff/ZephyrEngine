#pragma once

using namespace System::Collections::Generic;
using namespace ZephyrSharp::Collision;
using namespace ZephyrSharp::Linalg;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        namespace Components
        {
            /// <summary>
            /// �Փ˂����o���ꂽ�Ƃ��ɌĂяo�����f���Q�[�g�ł��B
            /// </summary>
            /// <param name="other">�Փ˂�������̃G���e�B�e�B�B</param> 
            /// <param name="point">�Փ˒n�_�B</param> 
            public delegate void CollideDelegate(Entity^ other, Vector3 point);

            /// <summary>
            /// ���̂̏Փ˔�����s���܂��B
            /// </summary>
            public ref class CollisionComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ���[���h��Ԃɕ��̂�o�^���܂��B
                /// </summary>
                void OnAttach() override;

                /// <summary>
                /// ���[���h��Ԃ���o�^���������܂��B
                /// </summary>
                void OnDetach() override;

                void ReceiveMessage(System::Object^ message, System::Object^ argument) override
                {
                    if (message->ToString() == "update")
                    {
                        this->Update();
                    }
                }

            public:

                /// <summary>
                /// �Փ˂����������Ƃ��ɔ������܂��B
                /// </summary>
                event CollideDelegate^ Collided;

                /// <summary>
                /// �Փ˃I�u�W�F�N�g��ݒ肵�܂��B
                /// </summary>
                property AbstractCollisionObject^ Object;

                /// <summary>
                /// �����̏Փˌ��o�O���[�v��ݒ肵�܂��B
                /// </summary>
                property unsigned long long Group;

                /// <summary>
                /// �Փˌ��o���s������̏Փˌ��o�O���[�v��ݒ肵�܂��B
                /// </summary>
                property unsigned long long OtherGroups;

                /// <summary>
                /// ���̃v���p�e�B�� true �̏ꍇ�́A��t���[�����ɕ����̕��̂ƏՓ˂��������܂��B
                /// </summary>
                property bool Penetration;

                /// <summary>
                /// �Փˌ��o���珜�O����Ώۂ̃��X�g��ݒ肵�܂��B
                /// </summary>
                property System::Collections::Generic::IEnumerable<CollisionComponent^>^ Excludes;

            private:

                void Update();

                static LinkedList<CollisionComponent^>^ s_colliders = gcnew LinkedList<CollisionComponent^>();
            };
        }
    }
}
