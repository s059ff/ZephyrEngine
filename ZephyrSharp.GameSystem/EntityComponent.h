#pragma once

using namespace System::Collections::Generic;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        ref class Entity;
        ref class EntityComponent;

        /// <summary>
        /// ゲーム エンティティの構成要素であるエンティティ コンポーネントを表します。
        /// </summary>
        public ref class EntityComponent
        {
        public:

            /// <summary>
            /// コンポーネントがエンティティに取り付けられているか調べます。
            /// </summary>
            property bool HasOwner { bool get() { return owner != nullptr; } }

            /// <summary>
            /// コンポーネントを所持しているエンティティ。
            /// </summary>
            property Entity^ Owner
            {
                Entity^ get() { return owner; }

                void set(Entity^ value);
            }

            /// <summary>
            /// 外部コンポーネントにメッセージを送信します。
            /// </summary>
            /// <param name="message">メッセージデータ。</param> 
            void SendMessage(EntityComponent^ one, System::Object^ message, System::Object^ argument)
            {
                one->ReceiveMessage(message, argument);
            }
            
        protected public:

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
            virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) {}

        internal:

            EntityComponent^ back = this;

            EntityComponent^ next = this;

            Entity^ owner = nullptr;
        };
    }
}
