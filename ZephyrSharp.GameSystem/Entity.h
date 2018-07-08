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
        /// �Q�[�� �G���e�B�e�B��\���܂��B
        /// </summary>
        public ref class Entity sealed
        {
        public:

            /// <summary>
            /// �V�K�ɃG���e�B�e�B���쐬���܂��B
            /// </summary>
            static Entity^ Instantiate();

            /// <summary>
            /// �w��̃G���e�B�e�B���폜���܂��B�G���e�B�e�B����������R���|�[�l���g���ꊇ���č폜����܂��B
            /// </summary>
            /// <param name="entity">�폜����G���e�B�e�B�B</param>
            static void Kill(Entity^ entity);

            /// <summary>
            /// �w��̕����̃G���e�B�e�B���폜���܂��B�G���e�B�e�B����������R���|�[�l���g���ꊇ���č폜����܂��B
            /// </summary>
            /// <param name="entities">�폜����G���e�B�e�B�B</param>
            static void KillRange(System::Collections::Generic::IEnumerable<Entity^>^ entities);

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
            static void Rename(Entity^ entity, String^ name);

            /// <summary>
            /// �w��̖��O�����G���e�B�e�B���������܂��B
            /// </summary>
            /// <param name="name">�G���e�B�e�B�̖��O�B</param>
            static Entity^ Find(String^ name);

            /// <summary>
            /// �����Ɉ�v����ŏ��̃G���e�B�e�B���擾���܂��B
            /// </summary>
            /// <param name="pred">���������B</param>
            static Entity^ Find(System::Func<Entity^, bool>^ pred);

            /// <summary>
            /// �w��̃��b�Z�[�W���w��̃G���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="one">�G���e�B�e�B�B</param> 
            /// <param name="message">���b�Z�[�W�B</param> 
            /// <param name="argument">���b�Z�[�W�����B</param> 
            static void SendMessage(Entity^ one, System::Object^ message, System::Object^ argument);

            /// <summary>
            /// �w��̃��b�Z�[�W���w��̃G���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="one">�G���e�B�e�B�B</param> 
            /// <param name="message">���b�Z�[�W�B</param> 
            static void SendMessage(Entity^ one, System::Object^ message)
            {
                SendMessage(one, message, nullptr);
            }

            /// <summary>
            /// �w��̃��b�Z�[�W�����ׂẴG���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�B</param> 
            /// <param name="argument">���b�Z�[�W�����B</param> 
            static void BroadcastMessage(System::Object^ message, System::Object^ argument);

            /// <summary>
            /// �w��̃��b�Z�[�W�����ׂẴG���e�B�e�B�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�B</param> 
            static void BroadcastMessage(System::Object^ message)
            {
                BroadcastMessage(message, nullptr);
            }

            /// <summary>
            /// �S�ẴG���e�B�e�B�ɑ΂��ď������s���܂��B
            /// </summary>
            /// <param name="callback">�R�[���o�b�N�֐��B</param> 
            static void ForEach(System::Action<Entity^>^ callback);

            /// <summary>
            /// �G���e�B�e�B�̑������擾���܂��B
            /// </summary>
            static property int EntityCount
            {
                int get() { return s_entity_count; }
            }

        public:

            /// <summary>
            /// �G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
            /// </summary>
            /// <param name="component">�R���|�[�l���g�B</param> 
            EntityComponent^ Attach(EntityComponent^ component);

            /// <summary>
            /// �G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            EntityComponent^ Attach(System::Type^ type)
            {
                EntityComponent^ component = dynamic_cast<EntityComponent^>(System::Activator::CreateInstance(type));
                return this->Attach(component);
            }

            /// <summary>
            /// �G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
            /// </summary>
            /// <param name="component">�R���|�[�l���g�B</param> 
            EntityComponent^ Detach(EntityComponent^ component);

            /// <summary>
            /// �G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            EntityComponent^ Detach(System::Type^ type)
            {
                return this->Detach(this->Get(type));
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���������Ă��邩���ׂ܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            bool Has(System::Type^ type)
            {
                return Get(type) != nullptr;
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���擾���܂��B
            /// </summary>
            /// <param name="type">�R���|�[�l���g�̃^�C�v�B</param> 
            EntityComponent^ Get(System::Type^ type);

            /// <summary>
            /// �w��̃��b�Z�[�W�����̃G���e�B�e�B�������ׂẴR���|�[�l���g�ɑ΂��Ĕ��s���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�B</param> 
            /// <param name="argument">���b�Z�[�W�����B</param> 
            void ReceiveMessage(System::Object^ message, System::Object^ argument);

            /// <summary>
            /// �G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
            /// </summary>
            generic <typename ComponentType> where ComponentType : gcnew() ComponentType Attach()
            {
                return (ComponentType)(this->Attach((EntityComponent^)gcnew ComponentType()));
            }

            /// <summary>
            /// �G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
            /// </summary>
            generic <typename ComponentType> ComponentType Detach()
            {
                return (ComponentType)(this->Detach(ComponentType::typeid));
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���������Ă��邩���ׂ܂��B
            /// </summary>
            generic <typename ComponentType> bool Has()
            {
                return this->Has(ComponentType::typeid);
            }

            /// <summary>
            /// �w��̃R���|�[�l���g���擾���܂��B
            /// </summary>
            generic <typename ComponentType> ComponentType Get()
            {
                return (ComponentType)(this->Get(ComponentType::typeid));
            }

            ///// <summary>
            ///// �w��̃R���|�[�l���g�����łɎ��t�����Ă��Ȃ��ꍇ�A�G���e�B�e�B�Ɏw��̃R���|�[�l���g�����t���܂��B
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
            ///// �w��̃R���|�[�l���g�����łɎ��t�����Ă���ꍇ�A�G���e�B�e�B����w��̃R���|�[�l���g�����O���܂��B
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
            /// �R���|�[�l���g�̈ꗗ���擾���܂��B
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
            /// �G���e�B�e�B�̖��O�B�����̏ꍇ�́Anull�B
            /// </summary>
            property String^ Name
            {
                String^ get() { return name; }
                void set(String^ name) { Rename(this, name); }
            }

            /// <summary>
            /// ���̃G���e�B�e�B�̎��ʔԍ����擾���܂��B
            /// </summary>
            property unsigned long long ID { unsigned long long get() { return id; } }

            /// <summary>
            /// �G���e�B�e�B�� Kill ����Ă��Ȃ����擾���܂��B
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
