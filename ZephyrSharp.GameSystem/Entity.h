#pragma once

#include "common.h"
#include "EntityComponent.h"

#define Map System::Collections::Generic::Dictionary

namespace ZephyrSharp
{
    namespace GameSystem
    {
        ref class EntityComponent;

        /// <summary>
        /// ゲーム エンティティを表します。
        /// </summary>
        public ref class Entity sealed
        {
        public:

            /// <summary>
            /// 新規にエンティティを作成します。
            /// </summary>
            static Entity^ Instantiate();

            /// <summary>
            /// 指定のエンティティを削除します。エンティティが所持するコンポーネントも一括して削除されます。
            /// </summary>
            /// <param name="entity">削除するエンティティ。</param>
            static void Kill(Entity^ entity);

            /// <summary>
            /// 指定の複数のエンティティを削除します。エンティティが所持するコンポーネントも一括して削除されます。
            /// </summary>
            /// <param name="entities">削除するエンティティ。</param>
            static void KillRange(System::Collections::Generic::IEnumerable<Entity^>^ entities);

            /// <summary>
            /// （仮に kill 状態になっているエンティティを完全に削除します。このメソッドはフレーム毎に呼び出す必要があります。）
            /// </summary>
            static void Update();

            /// <summary>
            /// すべてのエンティティを削除します。
            /// </summary>
            static void Clear();

            /// <summary>
            /// エンティティに名前をつけます。
            /// </summary>
            /// <param name="entity">命名対象のエンティティ。</param>
            /// <param name="name">エンティティの名前。</param>
            static void Rename(Entity^ entity, String^ name);

            /// <summary>
            /// 指定の名前を持つエンティティを検索します。
            /// </summary>
            /// <param name="name">エンティティの名前。</param>
            static Entity^ Find(String^ name);

            /// <summary>
            /// 条件に一致する最初のエンティティを取得します。
            /// </summary>
            /// <param name="pred">検索条件。</param>
            static Entity^ Find(System::Func<Entity^, bool>^ pred);

            /// <summary>
            /// 指定のメッセージを指定のエンティティに対して発行します。
            /// </summary>
            /// <param name="one">エンティティ。</param> 
            /// <param name="message">メッセージ。</param> 
            /// <param name="argument">メッセージ引数。</param> 
            static void SendMessage(Entity^ one, System::Object^ message, System::Object^ argument);

            /// <summary>
            /// 指定のメッセージを指定のエンティティに対して発行します。
            /// </summary>
            /// <param name="one">エンティティ。</param> 
            /// <param name="message">メッセージ。</param> 
            static void SendMessage(Entity^ one, System::Object^ message)
            {
                SendMessage(one, message, nullptr);
            }

            /// <summary>
            /// 指定のメッセージをすべてのエンティティに対して発行します。
            /// </summary>
            /// <param name="message">メッセージ。</param> 
            /// <param name="argument">メッセージ引数。</param> 
            static void BroadcastMessage(System::Object^ message, System::Object^ argument);

            /// <summary>
            /// 指定のメッセージをすべてのエンティティに対して発行します。
            /// </summary>
            /// <param name="message">メッセージ。</param> 
            static void BroadcastMessage(System::Object^ message)
            {
                BroadcastMessage(message, nullptr);
            }

            /// <summary>
            /// 全てのエンティティに対して処理を行います。
            /// </summary>
            /// <param name="callback">コールバック関数。</param> 
            static void ForEach(System::Action<Entity^>^ callback);

            /// <summary>
            /// エンティティの総数を取得します。
            /// </summary>
            static property int EntityCount
            {
                int get() { return s_entity_count; }
            }

        public:

            /// <summary>
            /// エンティティに指定のコンポーネントを取り付けます。
            /// </summary>
            /// <param name="component">コンポーネント。</param> 
            EntityComponent^ Attach(EntityComponent^ component);

            /// <summary>
            /// エンティティに指定のコンポーネントを取り付けます。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            EntityComponent^ Attach(System::Type^ type)
            {
                EntityComponent^ component = dynamic_cast<EntityComponent^>(System::Activator::CreateInstance(type));
                return this->Attach(component);
            }

            /// <summary>
            /// エンティティから指定のコンポーネントを取り外します。
            /// </summary>
            /// <param name="component">コンポーネント。</param> 
            EntityComponent^ Detach(EntityComponent^ component);

            /// <summary>
            /// エンティティから指定のコンポーネントを取り外します。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            EntityComponent^ Detach(System::Type^ type)
            {
                return this->Detach(this->Get(type));
            }

            /// <summary>
            /// 指定のコンポーネントを所持しているか調べます。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            bool Has(System::Type^ type)
            {
                return Get(type) != nullptr;
            }

            /// <summary>
            /// 指定のコンポーネントを取得します。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            EntityComponent^ Get(System::Type^ type);

            /// <summary>
            /// 指定のメッセージをこのエンティティが持つすべてのコンポーネントに対して発行します。
            /// </summary>
            /// <param name="message">メッセージ。</param> 
            /// <param name="argument">メッセージ引数。</param> 
            void ReceiveMessage(System::Object^ message, System::Object^ argument);

            /// <summary>
            /// エンティティに指定のコンポーネントを取り付けます。
            /// </summary>
            generic <typename ComponentType> where ComponentType : gcnew() ComponentType Attach()
            {
                return (ComponentType)(this->Attach((EntityComponent^)gcnew ComponentType()));
            }

            /// <summary>
            /// エンティティから指定のコンポーネントを取り外します。
            /// </summary>
            generic <typename ComponentType> ComponentType Detach()
            {
                return (ComponentType)(this->Detach(ComponentType::typeid));
            }

            /// <summary>
            /// 指定のコンポーネントを所持しているか調べます。
            /// </summary>
            generic <typename ComponentType> bool Has()
            {
                return this->Has(ComponentType::typeid);
            }

            /// <summary>
            /// 指定のコンポーネントを取得します。
            /// </summary>
            generic <typename ComponentType> ComponentType Get()
            {
                return (ComponentType)(this->Get(ComponentType::typeid));
            }

            ///// <summary>
            ///// 指定のコンポーネントがすでに取り付けられていない場合、エンティティに指定のコンポーネントを取り付けます。
            ///// </summary>
            //generic <typename ComponentType> where ComponentType : gcnew() ComponentType TryAttach()
            //{
            //    auto component = this->Get<ComponentType>();
            //    if (component == nullptr)
            //        this->Attach((EntityComponent^)component);
            //    else
            //        return nullptr;
            //}

            ///// <summary>
            ///// 指定のコンポーネントがすでに取り付けられている場合、エンティティから指定のコンポーネントを取り外します。
            ///// </summary>
            //generic <typename ComponentType> where ComponentType : gcnew() ComponentType TryDetach()
            //{
            //    auto component = this->Get<ComponentType>();
            //    if (component != nullptr)
            //        return this->Detach((EntityComponent^)component);
            //    else
            //        return nullptr;
            //}

            /// <summary>
            /// コンポーネントの一覧を取得します。
            /// </summary>
            property List<EntityComponent^>^ Components
            {
                List<EntityComponent^>^ get()
                {
                    if (component_count > 0)
                    {
                        List<EntityComponent^>^ out = gcnew List<EntityComponent^>(component_count);

                        auto begin = this->components->next;
                        auto end = this->components;
                        auto it = begin;
                        int k = 0;
                        while (it != end)
                        {
                            auto next = it->next;
                            out->Add(it);
                            it = next;
                        }
                        return out;
                    }
                    else
                    {
                        return empty_components;
                    }
                }
            }

        public:

            /// <summary>
            /// エンティティの名前。無名の場合は、null。
            /// </summary>
            property String^ Name
            {
                String^ get() { return name; }
                void set(String^ name) { Rename(this, name); }
            }

            /// <summary>
            /// このエンティティの識別番号を取得します。
            /// </summary>
            property unsigned long long ID { unsigned long long get() { return id; } }

            /// <summary>
            /// エンティティが Kill されていないか取得します。
            /// </summary>
            property bool IsAlive { bool get() { return !killed; } }

        private:

            Entity() {}

        private:

            Entity^ back = this;

            Entity^ next = this;

            String^ name = nullptr;

            EntityComponent^ components = gcnew EntityComponent();

            unsigned long long id;

            bool killed = false;

            int component_count = 0;

        private:

            static Entity^ s_root = gcnew Entity();

            static Map<String^, Entity^>^ s_name_entity_map = gcnew Map<String^, Entity^>();

            static int s_entity_count = 0;

            static unsigned long long s_next_id = 0;

            static List<EntityComponent^>^ empty_components = gcnew List<EntityComponent^>();
        };
    }
}
