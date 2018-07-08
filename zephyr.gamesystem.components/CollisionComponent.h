#pragma once

#include "zephyr\event.h"
#include "zephyr\functional.h"
#include "zephyr\string.h"
#include "zephyr\set.h"
#include "zephyr.collision\CollisionObject.h"
#include "zephyr.gamesystem\Entity.h"
#include "zephyr.linalg\Vector3.h"

namespace zephyr
{
    namespace gamesystem
    {
        namespace components
        {
            /// <summary>
            /// ���̂̏Փ˔�����s���܂��B
            /// </summary>
            class CollisionComponent : public EntityComponent
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

                void ReceiveMessage(const string& message, void* params[]) override
                {
                    if (message == "update")
                    {
                        this->Update();
                    }
                }

            public:

                /// <summary>
                /// �Փ˂����������Ƃ��ɔ������܂��B
                /// </summary>
                event<Entity*, linalg::Vector3> Collided;

                /// <summary>
                /// ���̂̌`���ݒ肵�܂��B
                /// </summary>
                collision::AbstractCollisionObject* Shape;

                /// <summary>
                /// �����̏Փˌ��o�O���[�v��ݒ肵�܂��B
                /// </summary>
                unsigned long long Group;

                /// <summary>
                /// �Փˌ��o���s������̏Փˌ��o�O���[�v��ݒ肵�܂��B
                /// </summary>
                unsigned long long OtherGroups;

                /// <summary>
                /// ���̃v���p�e�B�� true �̏ꍇ�́A��t���[�����ɕ����̕��̂ƏՓ˂��������܂��B
                /// </summary>
                bool Penetration;

                /// <summary>
                /// �Փˌ��o���珜�O����Ώۂ̃��X�g��ݒ肵�܂��B
                /// </summary>
                set<CollisionComponent*> Excludes;

            private:

                void Update();

                static set<CollisionComponent*> s_colliders;
            };
        }
    }
}
