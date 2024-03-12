#include "Entity.h"

#include "zephyr\print.h"
#include "zephyr\smart_ptr.h"
#include "zephyr\pool.h"

#define MAX_ENTITY 8192

namespace zephyr
{
    namespace gamesystem
    {
        namespace
        {
            Entity* s_root = new Entity();

            map<string, Entity*> s_name_entity_map;

            int s_entity_count;

            unsigned __int64 s_next_id;

            pool s_entity_memory_pool(sizeof(Entity), MAX_ENTITY);
        }

        const int& Entity::EntityCount = s_entity_count;

        Entity* Entity::Instantiate()
        {

            s_entity_count++;

            Entity* entity = s_entity_memory_pool.alloc<Entity>();

            s_root->back->next = entity;
            entity->back = s_root->back;

            s_root->back = entity;
            entity->next = s_root;

            entity->id = ++s_next_id;

            return entity;
        }

        void Entity::Kill(Entity* entity)
        {
            entity->killed = true;

            vector<EntityComponent*> _components = entity->Components;
            for (auto component : _components)
            {
                entity->Detach(component);
                component->OnDestroy();

                delete component;
            }

            if (!entity->name.empty())
            {
                s_name_entity_map.erase(entity->name);
                entity->name.clear();
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

        void Entity::Update()
        {
            auto it = s_root->next;
            auto end = s_root;

            while (it != end)
            {
                auto next = it->next;
                if (it->killed)
                {
                    Delete(it);
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
                Delete(it);
                it = next;
            }

            Update();

            s_next_id = 0;
        }

        void Entity::Rename(Entity* entity, const string& name)
        {
            if (!name.empty())
            {
                runtime_assert(s_name_entity_map.find(name) == s_name_entity_map.end(), "すでに同じ名前のエンティティが存在します。");
                entity->name = name;
                s_name_entity_map[name] = entity;
            }
            else
            {
                if (!entity->name.empty())
                {
                    s_name_entity_map.erase(entity->name);
                }
                entity->name.clear();
            }
        }

        Entity* Entity::Find(const string& name)
        {
            return (s_name_entity_map.find(name) != s_name_entity_map.end()) ? s_name_entity_map[name] : nullptr;
        }

        Entity* Entity::Find(function<bool(Entity*)> pred)
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

        void Entity::SendMessage(Entity* one, const string& message, void* params[])
        {
            one->ReceiveMessage(message, params);
        }

        void Entity::BroadcastMessage(const string& message, void* params[])
        {
            auto it = s_root->next;
            auto end = s_root;

            while (it != end)
            {
                auto next = it->next;
                if (!it->killed)
                    it->ReceiveMessage(message, params);
                it = next;
            }
        }

        void Entity::ForEach(function<void(Entity*)> callback)
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

        void Entity::Serialize(ostream& stream)
        {
            write(stream, s_entity_count);
            write(stream, s_next_id);

            auto begin = s_root->next;
            auto end = s_root;
            auto it = begin;

            while (it != end)
            {
                auto next = it->next;
                {
                    auto begin = it->components->next;
                    auto end = it->components;
                    auto _it = begin;
                    while (_it != end)
                    {
                        auto next = _it->next;
                        _it = next;
                    }
                }
                it = next;
            }
        }

        void Entity::Deserialize(istream& stream)
        {
            read(stream, s_entity_count);
            read(stream, s_next_id);

        }

        void Entity::ShowMemoryStatus()
        {
            s_entity_memory_pool.show_status();
            println("Entity count: {0}", EntityCount);
        }

        void Entity::Delete(Entity* entity)
        {
            delete entity->components;
            entity->components = nullptr;

            entity->Name.empty();

            entity->back->next = entity->next;
            entity->next->back = entity->back;

            entity->back = nullptr;
            entity->next = nullptr;

            s_entity_memory_pool.free(entity);

            s_entity_count--;
        }

        EntityComponent* Entity::Attach(EntityComponent* component)
        {
            auto& type = component->GetType();

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

        EntityComponent* Entity::Detach(EntityComponent* component)
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

        EntityComponent* Entity::Get(const type_info& type)
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

        EntityComponent* Entity::_get_BeginComponent() const
        {
            auto begin = this->components->next;
            return begin;
        }

        EntityComponent* Entity::_get_EndComponent() const
        {
            auto end = this->components;
            return end;
        }

        vector<EntityComponent*> Entity::_get_Components() const
        {
            vector<EntityComponent*> dest;

            if (this->component_count > 0)
            {
                dest.reserve(this->component_count);

                auto begin = this->components->next;
                auto end = this->components;
                auto it = begin;
                while (it != end)
                {
                    auto next = it->next;
                    dest.push_back(it);
                    it = next;
                }
            }

            return dest;
        }

        void Entity::ReceiveMessage(const string& message, void* params[])
        {
            vector<EntityComponent*> _components = this->Components;
            for (auto component : _components)
            {
                if (component->owner == this)
                    component->ReceiveMessage(message, params);
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
