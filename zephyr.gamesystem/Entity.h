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
        /// �Q�[�� �G���e�B�e�B��\���܂��B
        /// </summary>
        class Entity
        {
        public:

            /// <summary>
            /// �V�K�ɃG���e�B�e�B���쐬���܂��B
            /// </summary>
            static Entity* Instantiate();

            /// <summary>
            /// �w��̃G���e�B�e�B���폜���܂��B�G���e�B�e�B����������R���|�[�l���g���ꊇ���č폜����܂��B
            /// </summary>
            /// <param name="entity">�폜����G���e�B�e�B�B</param>
            static void Kill(Entity* entity);

            /// <summary>
            /// �i���� kill ��ԂɂȂ��Ă���G���e�B�e�B�����S�ɍ폜���܂��B���̃��\�b�h�̓t���[�����ɌĂяo���K�v������܂��B�j
            /// </summary>
            static void Update();

            /// <summary>
            /// ���ׂẴG���e�B�e�B���폜���܂��B
            /// </summary>
            static void Clear();

            /// <summary>
            /// �G���e�B�e�B�ɖ��O�����܂��B
            /// </summary>
            /// <param name="entity">�����Ώۂ̃G���e�B�e�B�B</param>
            /// <param name="name">�G���e�B�e�B�̖��O�B</param>
            static void Rename(Entity* entity, const string& name);

            /// <summary>
            /// �w��̖��O�����G���e�B�e�B���������܂��B
            /// </summary>
            /// <param name="name">�G���e�B�e�B�̖��O�B</param>
            static Entity* Find(const string& name);

            /// <summary>
            /// �����Ɉ�v����ŏ��̃G���e�B�e�B���擾���܂��B
            /// </summary>
            /// <param name="pred">���������B</param>
            static Entity* Find(function<bool(Entity*)> pred);

            /// <summary>
            /// �w��̃��b�Z�[�W���w��̃G���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="one">�G���e�B�e�B�B</param> 
            /// <param name="message">���b�Z�[�W�B</param> 
            /// <param name="argument">���b�Z�[�W�����B</param> 
            static void SendMessage(Entity* one, const string& message, void* params[]);

            /// <summary>
            /// �w��̃��b�Z�[�W���w��̃G���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="one">�G���e�B�e�B�B</param> 
            /// <param name="message">���b�Z�[�W�B</param> 
            static void SendMessage(Entity* one, const string& message)
            {
                SendMessage(one, message, nullptr);
            }

            /// <summary>
            /// �w��̃��b�Z�[�W�����ׂẴG���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�B</param> 
            /// <param name="argument">���b�Z�[�W�����B</param> 
            static void BroadcastMessage(const string& message, void* params[]);

            /// <summary>
            /// �w��̃��b�Z�[�W�����ׂẴG���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�B</param> 
            static void BroadcastMessage(const string& message)
            {
                BroadcastMessage(message, nullptr);
            }

            /// <summary>
            /// �S�ẴG���e�B�e�B�ɑ΂��ď������s���܂��B
            /// </summary>
            /// <param name="callback">�R�[���o�b�N�֐��B</param> 
            static void ForEach(function<void(Entity*)> callback);

            /// <summary>
            /// �Q�[���V�X�e�����V���A���f�[�^�ɕϊ����܂��B
            /// </summary>
            /// <param name="stream">�V���A���f�[�^���������ރX�g���[���B</param> 
            static void Serialize(ostream& stream);

            /// <summary>
            /// �V���A���f�[�^���Q�[���V�X�e���ɕϊ����܂��B
            /// </summary>
            /// <param name="stream">�V���A���f�[�^��ǂݍ��ރX�g���[���B</param> 
            static void Deserialize(istream& stream);

            /// <summary>
            /// �������g�p�󋵂�\�����܂��B
            /// </summary>
            static void ShowMemoryStatus();

            /// <summary>
            /// �G���e�B�e�B�̑������擾���܂��B
            /// </summary>
            static const int& EntityCount;

        private:

            static void Delete(Entity* entity);

        public:

            /// <summary>
            /// �G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
            /// </summary>
            /// <param name="component">�R���|�[�l���g�B</param> 
            EntityComponent* Attach(EntityComponent* component);

            /// <summary>
            /// �G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            //EntityComponent* Attach(System::Type* type)
            //{
            //    EntityComponent* component = dynamic_cast<EntityComponent*>(System::Activator::CreateInstance(type));
            //    return this->Attach(component);
            //}

            /// <summary>
            /// �G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
            /// </summary>
            /// <param name="component">�R���|�[�l���g�B</param> 
            EntityComponent* Detach(EntityComponent* component);

            /// <summary>
            /// �G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            EntityComponent* Detach(const type_info& type)
            {
                return this->Detach(this->Get(type));
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���������Ă��邩���ׂ܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            bool Has(const type_info& type)
            {
                return Get(type) != nullptr;
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���擾���܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            EntityComponent* Get(const type_info& type);

            /// <summary>
            /// �w��̃��b�Z�[�W�����̃G���e�B�e�B�������ׂẴR���|�[�l���g�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�B</param> 
            /// <param name="argument">���b�Z�[�W�����B</param> 
            void ReceiveMessage(const string& message, void* params[]);

            /// <summary>
            /// �G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
            /// </summary>
            template <typename ComponentType> ComponentType* Attach()
            {
                return (ComponentType*)(this->Attach(new ComponentType()));
            }

            /// <summary>
            /// �G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
            /// </summary>
            template <typename ComponentType> ComponentType* Detach()
            {
                return (ComponentType*)(this->Detach(typeid(ComponentType)));
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���������Ă��邩���ׂ܂��B
            /// </summary>
            template <typename ComponentType> bool Has()
            {
                return this->Has(typeid(ComponentType));
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���擾���܂��B
            /// </summary>
            template <typename ComponentType> ComponentType* Get()
            {
                return (ComponentType*)(this->Get(typeid(ComponentType)));
            }

            /// <summary>
            /// �w��̃R���|�[�l���g�����łɎ��t�����Ă��Ȃ��ꍇ�A�G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
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
            /// �w��̃R���|�[�l���g�����łɎ��t�����Ă���ꍇ�A�G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
            /// </summary>
            template <typename ComponentType> void TryDetach()
            {
                auto component = this->Get<ComponentType>();
                if (component != nullptr)
                    this->Detach<ComponentType>();
            }

            /// <summary>
            /// �R���|�[�l���g�̈ꗗ���擾���܂��B
            /// </summary>
            READONLY_PROPERTY(EntityComponent*, BeginComponent, const;);

            /// <summary>
            /// �R���|�[�l���g�̈ꗗ���擾���܂��B
            /// </summary>
            READONLY_PROPERTY(EntityComponent*, EndComponent, const;);

            /// <summary>
            /// �R���|�[�l���g�̈ꗗ���擾���܂��B
            /// </summary>
            READONLY_PROPERTY(vector<EntityComponent*>, Components, const;);

        public:

            /// <summary>
            /// �G���e�B�e�B�̖��O�B�����̏ꍇ�́Anull�B
            /// </summary>
            READWRITE_PROPERTY(string, Name, const{ return name; }, { Rename(this, value); });

            /// <summary>
            /// ���̃G���e�B�e�B�̎��ʔԍ����擾���܂��B
            /// </summary>
            READONLY_PROPERTY(unsigned long long, ID, const{ return id; });

            /// <summary>
            /// �G���e�B�e�B�� Kill ����Ă��Ȃ����擾���܂��B
            /// </summary>
            READONLY_PROPERTY(bool, IsAlive, const{ return !killed; });

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
