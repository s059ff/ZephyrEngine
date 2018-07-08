#include "Entity.h"

namespace ZephyrSharp
{
    namespace GameSystem
    {
        Entity^ Entity::Instantiate()
        {
            s_entity_count++;

            Entity^ entity = gcnew Entity();

            s_root->back->next = entity;
            entity->back = s_root->back;

            s_root->back = entity;
            entity->next = s_root;

            entity->id = ++s_next_id;

            return entity;
        }

        void Entity::Kill(Entity^ entity)
        {
            entity->killed = true;

            for each (auto component in entity->Components)
            {
                entity->Detach(component);
                component->OnDestroy();
            }

            if (entity->name != nullptr)
            {
                s_name_entity_map->Remove(entity->name);
                entity->name = nullptr;
            }

            //auto it = entity->components->next;
            //auto end = entity->components;

            //while (it != end)
            //{
            //    auto next = it->next;
            //    entity->Detach(it);
            //    it->OnDestroy();
            //    it = next;
            //}
        }

        void Entity::KillRange(System::Collections::Generic::IEnumerable<Entity^>^ entities)
        {
            for each (Entity^ e in entities)
            {
                Kill(e);
            }
        }

        void Entity::Update()
        {
            auto it = s_root->next;
            auto end = s_root;

            while (it != end)
            {
                auto next = it->next;
                if (it->killed)
                {
                    it->Name = nullptr;

                    it->back->next = it->next;
                    it->next->back = it->back;

                    it->back = nullptr;
                    it->next = nullptr;

                    delete it;

                    s_entity_count--;
                }
                it = next;
            }
        }

        void Entity::Clear()
        {
            auto it = s_root->next;
            auto end = s_root;

            while (it != end)
            {
                auto next = it->next;
                Kill(it);
                it = next;
            }

            Update();

            s_next_id = 0;
        }

        void Entity::Rename(Entity^ entity, String^ name)
        {
            if (name != nullptr)
            {
                entity->name = name;
                runtime_assert(!s_name_entity_map->ContainsKey(name), "すでに同じ名前のエンティティが存在します。");
                s_name_entity_map->Add(name, entity);
            }
            else
            {
                if (entity->name != nullptr)
                {
                    s_name_entity_map->Remove(entity->name);
                }
                entity->name = nullptr;
            }
        }

        Entity^ Entity::Find(String^ name)
        {
            if (s_name_entity_map->ContainsKey(name))
                return s_name_entity_map[name];
            else
                return nullptr;
        }

        Entity^ Entity::Find(System::Func<Entity^, bool>^ pred)
        {
            auto it = s_root->next;
            auto end = s_root;

            while (it != end)
            {
                auto next = it->next;
                if (!it->killed)
                    if (pred(it))
                        return it;
                it = next;
            }
            return nullptr;
        }

        void Entity::SendMessage(Entity^ one, System::Object^ message, System::Object^ argument)
        {
            one->ReceiveMessage(message, argument);
        }

        void Entity::BroadcastMessage(System::Object^ message, System::Object^ argument)
        {
            auto it = s_root->next;
            auto end = s_root;

            while (it != end)
            {
                auto next = it->next;
                if (!it->killed)
                    it->ReceiveMessage(message, argument);
                it = next;
            }
        }

        void Entity::ForEach(System::Action<Entity^>^ callback)
        {
            auto it = s_root->next;
            auto end = s_root;

            while (it != end)
            {
                auto next = it->next;
                if (!it->killed)
                    callback(it);
                it = next;
            }
        }

        EntityComponent^ Entity::Attach(EntityComponent^ component)
        {
            auto type = component->GetType();

            runtime_assert(!component->HasOwner, "一つのコンポーネントを複数のエンティティに取り付けることはできません。");
            runtime_assert(!this->Has(type), "このコンポーネントタイプはすでに対象のエンティティに取り付け済みです。");

            this->components->back->next = component;
            component->back = this->components->back;

            this->components->back = component;
            component->next = this->components;

            component->owner = this;
            component->OnAttach();

            ++component_count;

            return component;
        }

        EntityComponent^ Entity::Detach(EntityComponent^ component)
        {
            component->OnDetach();
            component->owner = nullptr;

            component->back->next = component->next;
            component->next->back = component->back;

            component->back = nullptr;
            component->next = nullptr;

            --component_count;

            return component;
        }

        EntityComponent^ Entity::Get(System::Type^ type)
        {
            auto it = this->components->next;
            auto end = this->components;
            while (it != end)
            {
                auto next = it->next;

                if (it->GetType() == type)
                {
                    return it;
                }

                it = next;
            }

            return nullptr;
        }

        void Entity::ReceiveMessage(System::Object^ message, System::Object^ argument)
        {
            for each (auto component in this->Components)
            {
                if (component->owner == this)
                    component->ReceiveMessage(message, argument);
            }

            //auto it = this->components->next;
            //auto end = this->components;
            //while (it != end)
            //{
            //    auto next = it->next;
            //    it = next;
            //}
        }
    }
}
