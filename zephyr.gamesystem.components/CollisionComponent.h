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
            /// 物体の衝突判定を行います。
            /// </summary>
            class CollisionComponent : public EntityComponent
            {
            public:

                /// <summary>
                /// ワールド空間に物体を登録します。
                /// </summary>
                void OnAttach() override;

                /// <summary>
                /// ワールド空間から登録を解除します。
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
                /// 衝突が発生したときに発生します。
                /// </summary>
                event<Entity*, linalg::Vector3> Collided;

                /// <summary>
                /// 物体の形状を設定します。
                /// </summary>
                collision::AbstractCollisionObject* Shape;

                /// <summary>
                /// 自分の衝突検出グループを設定します。
                /// </summary>
                unsigned long long Group;

                /// <summary>
                /// 衝突検出を行う相手の衝突検出グループを設定します。
                /// </summary>
                unsigned long long OtherGroups;

                /// <summary>
                /// このプロパティが true の場合は、一フレーム中に複数の物体と衝突が発生します。
                /// </summary>
                bool Penetration;

                /// <summary>
                /// 衝突検出から除外する対象のリストを設定します。
                /// </summary>
                set<CollisionComponent*> Excludes;

            private:

                void Update();

                static set<CollisionComponent*> s_colliders;
            };
        }
    }
}
