#pragma once

#include "zephyr\property.h"
#include "zephyr\typeinfo.h"
#include "zephyr\string.h"

namespace zephyr
{
    namespace gamesystem
    {
        class Entity;
        class EntityComponent;

        /// <summary>
        /// ゲーム エンティティの構成要素であるエンティティ コンポーネントを表します。
        /// </summary>
        class EntityComponent
        {
        public:

            /// <summary>
            /// コンポーネントがエンティティに取り付けられているか調べます。
            /// </summary>
            READONLY_PROPERTY(bool, HasOwner, const{ return owner != nullptr; });

            /// <summary>
            /// コンポーネントを所持しているエンティティ。
            /// </summary>
            READWRITE_PROPERTY(Entity*, Owner, const{ return owner; }, ;);

            /// <summary>
            /// 外部コンポーネントにメッセージを送信します。
            /// </summary>
            /// <param name="message">メッセージデータ。</param> 
            void SendMessage(EntityComponent* one, const string& message, void* params[])
            {
                one->ReceiveMessage(message, params);
            }

            /// <summary>
            /// このインスタンスのtype_infoを返します。
            /// </summary>
            const type_info& GetType() const 
            {
                return typeid(*this);
            }

        public:

            /// <summary>
            /// コンポーネントがエンティティにアタッチされたときに呼び出されます。
            /// </summary>
            virtual void OnAttach() {}

            /// <summary>
            /// コンポーネントがエンティティからデタッチされたときに呼び出されます。
            /// </summary>
            virtual void OnDetach() {}

            /// <summary>
            /// このコンポーネントを所持しているエンティティが破棄されるときに呼び出されます。リソースの解放処理を行います。このメソッド内で親エンティティにアクセスすることはできません。
            /// </summary>
            virtual void OnDestroy() {}

            /// <summary>
            /// 外部コンポーネントからのメッセージを受信して処理を行います。
            /// </summary>
            /// <param name="message">メッセージデータ。</param> 
            virtual void ReceiveMessage(const string& message, void* params[]) {}

        private:

            friend class Entity;

            EntityComponent* back = this;

            EntityComponent* next = this;

            Entity* owner = nullptr;
        };
    }
}
