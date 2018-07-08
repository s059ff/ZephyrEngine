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
            /// 衝突が検出されたときに呼び出されるデリゲートです。
            /// </summary>
            /// <param name="other">衝突した相手のエンティティ。</param> 
            /// <param name="point">衝突地点。</param> 
            public delegate void CollideDelegate(Entity^ other, Vector3 point);

            /// <summary>
            /// 物体の衝突判定を行います。
            /// </summary>
            public ref class CollisionComponent : public EntityComponent
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

                void ReceiveMessage(System::Object^ message, System::Object^ argument) override
                {
                    if (message->ToString() == "update")
                    {
                        this->Update();
                    }
                }

            public:

                /// <summary>
                /// 衝突が発生したときに発生します。
                /// </summary>
                event CollideDelegate^ Collided;

                /// <summary>
                /// 衝突オブジェクトを設定します。
                /// </summary>
                property AbstractCollisionObject^ Object;

                /// <summary>
                /// 自分の衝突検出グループを設定します。
                /// </summary>
                property unsigned long long Group;

                /// <summary>
                /// 衝突検出を行う相手の衝突検出グループを設定します。
                /// </summary>
                property unsigned long long OtherGroups;

                /// <summary>
                /// このプロパティが true の場合は、一フレーム中に複数の物体と衝突が発生します。
                /// </summary>
                property bool Penetration;

                /// <summary>
                /// 衝突検出から除外する対象のリストを設定します。
                /// </summary>
                property System::Collections::Generic::IEnumerable<CollisionComponent^>^ Excludes;

            private:

                void Update();

                static LinkedList<CollisionComponent^>^ s_colliders = gcnew LinkedList<CollisionComponent^>();
            };
        }
    }
}
