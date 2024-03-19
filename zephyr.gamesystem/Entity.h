#pragma once

#include "zephyr\functional.h"
#include "zephyr\map.h"
#include "zephyr\string.h"
#include "zephyr\typeinfo.h"
#include "zephyr\vector.h"
#include "zephyr\type.h"
#include "zephyr\stream.h"

#include "common.h"
#include "EntityComponent.h"

namespace zephyr
{
    namespace gamesystem
    {
        class EntityComponent;

        /// <summary>
        /// ゲーム エンティティを表します。
        /// </summary>
        class Entity
        {
        public:

            /// <summary>
            /// 新規にエンティティを作成します。
            /// </summary>
            static Entity* Instantiate();

            /// <summary>
            /// 指定のエンティティを削除します。エンティティが所持するコンポーネントも一括して削除されます。
            /// </summary>
            /// <param name="entity">削除するエンティティ。</param>
            static void Kill(Entity* entity);

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
            static void Rename(Entity* entity, const string& name);

            /// <summary>
            /// 指定の名前を持つエンティティを検索します。
            /// </summary>
            /// <param name="name">エンティティの名前。</param>
            static Entity* Find(const string& name);

            /// <summary>
            /// 条件に一致する最初のエンティティを取得します。
            /// </summary>
            /// <param name="pred">検索条件。</param>
            static Entity* Find(function<bool(Entity*)> pred);

            /// <summary>
            /// 指定のメッセージを指定のエンティティに対して発行します。
            /// </summary>
            /// <param name="one">エンティティ。</param> 
            /// <param name="message">メッセージ。</param> 
            /// <param name="argument">メッセージ引数。</param> 
            static void SendMessage(Entity* one, const string& message, void* params[]);

            /// <summary>
            /// 指定のメッセージを指定のエンティティに対して発行します。
            /// </summary>
            /// <param name="one">エンティティ。</param> 
            /// <param name="message">メッセージ。</param> 
            static void SendMessage(Entity* one, const string& message)
            {
                SendMessage(one, message, nullptr);
            }

            /// <summary>
            /// 指定のメッセージをすべてのエンティティに対して発行します。
            /// </summary>
            /// <param name="message">メッセージ。</param> 
            /// <param name="argument">メッセージ引数。</param> 
            static void BroadcastMessage(const string& message, void* params[]);

            /// <summary>
            /// 指定のメッセージをすべてのエンティティに対して発行します。
            /// </summary>
            /// <param name="message">メッセージ。</param> 
            static void BroadcastMessage(const string& message)
            {
                BroadcastMessage(message, nullptr);
            }

            /// <summary>
            /// 全てのエンティティに対して処理を行います。
            /// </summary>
            /// <param name="callback">コールバック関数。</param> 
            static void ForEach(function<void(Entity*)> callback);

            /// <summary>
            /// ゲームシステムをシリアルデータに変換します。
            /// </summary>
            /// <param name="stream">シリアルデータを書き込むストリーム。</param> 
            static void Serialize(ostream& stream);

            /// <summary>
            /// シリアルデータをゲームシステムに変換します。
            /// </summary>
            /// <param name="stream">シリアルデータを読み込むストリーム。</param> 
            static void Deserialize(istream& stream);

            /// <summary>
            /// メモリ使用状況を表示します。
            /// </summary>
            static void ShowMemoryStatus();

            /// <summary>
            /// エンティティの総数を取得します。
            /// </summary>
            static const int& EntityCount;

        private:

            static void Delete(Entity* entity);

        public:

            /// <summary>
            /// エンティティに指定のコンポーネントを取り付けます。
            /// </summary>
            /// <param name="component">コンポーネント。</param> 
            EntityComponent* Attach(EntityComponent* component);

            /// <summary>
            /// エンティティに指定のコンポーネントを取り付けます。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            //EntityComponent* Attach(System::Type* type)
            //{
            //    EntityComponent* component = dynamic_cast<EntityComponent*>(System::Activator::CreateInstance(type));
            //    return this->Attach(component);
            //}

            /// <summary>
            /// エンティティから指定のコンポーネントを取り外します。
            /// </summary>
            /// <param name="component">コンポーネント。</param> 
            EntityComponent* Detach(EntityComponent* component);

            /// <summary>
            /// エンティティから指定のコンポーネントを取り外します。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            EntityComponent* Detach(const type_info& type)
            {
                return this->Detach(this->Get(type));
            }

            /// <summary>
            /// 指定のコンポーネントを所持しているか調べます。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            bool Has(const type_info& type)
            {
                return Get(type) != nullptr;
            }

            /// <summary>
            /// 指定のコンポーネントを取得します。
            /// </summary>
            /// <param name="type">コンポーネントのタイプ。</param> 
            EntityComponent* Get(const type_info& type);

            /// <summary>
            /// 指定のメッセージをこのエンティティが持つすべてのコンポーネントに対して発行します。
            /// </summary>
            /// <param name="message">メッセージ。</param> 
            /// <param name="argument">メッセージ引数。</param> 
            void ReceiveMessage(const string& message, void* params[]);

            /// <summary>
            /// エンティティに指定のコンポーネントを取り付けます。
            /// </summary>
            template <typename ComponentType> ComponentType* Attach()
            {
                return (ComponentType*)(this->Attach(new ComponentType()));
            }

            /// <summary>
            /// エンティティから指定のコンポーネントを取り外します。
            /// </summary>
            template <typename ComponentType> ComponentType* Detach()
            {
                return (ComponentType*)(this->Detach(typeid(ComponentType)));
            }

            /// <summary>
            /// 指定のコンポーネントを所持しているか調べます。
            /// </summary>
            template <typename ComponentType> bool Has()
            {
                return this->Has(typeid(ComponentType));
            }

            /// <summary>
            /// 指定のコンポーネントを取得します。
            /// </summary>
            template <typename ComponentType> ComponentType* Get()
            {
                return (ComponentType*)(this->Get(typeid(ComponentType)));
            }

            /// <summary>
            /// 指定のコンポーネントがすでに取り付けられていない場合、エンティティに指定のコンポーネントを取り付けます。
            /// </summary>
            template <typename ComponentType> ComponentType* TryAttach()
            {
                auto component = this->Get<ComponentType>();
                if (component == nullptr)
                    return this->Attach<ComponentType>();
                else
                    return (ComponentType*)component;
            }

            /// <summary>
            /// 指定のコンポーネントがすでに取り付けられている場合、エンティティから指定のコンポーネントを取り外します。
            /// </summary>
            template <typename ComponentType> void TryDetach()
            {
                auto component = this->Get<ComponentType>();
                if (component != nullptr)
                    this->Detach<ComponentType>();
            }

            /// <summary>
            /// コンポーネントの一覧を取得します。
            /// </summary>
            READONLY_PROPERTY(EntityComponent*, BeginComponent, const;);

            /// <summary>
            /// コンポーネントの一覧を取得します。
            /// </summary>
            READONLY_PROPERTY(EntityComponent*, EndComponent, const;);

            /// <summary>
            /// コンポーネントの一覧を取得します。
            /// </summary>
            READONLY_PROPERTY(vector<EntityComponent*>, Components, const;);

        public:

            /// <summary>
            /// エンティティの名前。無名の場合は、null。
            /// </summary>
            READWRITE_PROPERTY(string, Name, { return name; }, { Rename(this, value); });

            /// <summary>
            /// このエンティティの識別番号を取得します。
            /// </summary>
            READONLY_PROPERTY(unsigned long long, ID, { return id; });

            /// <summary>
            /// エンティティが Kill されていないか取得します。
            /// </summary>
            READONLY_PROPERTY(bool, IsAlive, { return !killed; });

        private:

            Entity* back = this;

            Entity* next = this;

            string name;

            EntityComponent* components = new EntityComponent();

            unsigned long long id;

            bool killed = false;

            int component_count = 0;
        };
    }
}
