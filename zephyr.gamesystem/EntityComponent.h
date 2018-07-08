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
        /// �Q�[�� �G���e�B�e�B�̍\���v�f�ł���G���e�B�e�B �R���|�[�l���g��\���܂��B
        /// </summary>
        class EntityComponent
        {
        public:

            /// <summary>
            /// �R���|�[�l���g���G���e�B�e�B�Ɏ��t�����Ă��邩���ׂ܂��B
            /// </summary>
            READONLY_PROPERTY(bool, HasOwner, const{ return owner != nullptr; });

            /// <summary>
            /// �R���|�[�l���g���������Ă���G���e�B�e�B�B
            /// </summary>
            READWRITE_PROPERTY(Entity*, Owner, const{ return owner; }, ;);

            /// <summary>
            /// �O���R���|�[�l���g�Ƀ��b�Z�[�W�𑗐M���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�f�[�^�B</param> 
            void SendMessage(EntityComponent* one, const string& message, void* params[])
            {
                one->ReceiveMessage(message, params);
            }

            /// <summary>
            /// ���̃C���X�^���X��type_info��Ԃ��܂��B
            /// </summary>
            const type_info& GetType() const 
            {
                return typeid(*this);
            }

        public:

            /// <summary>
            /// �R���|�[�l���g���G���e�B�e�B�ɃA�^�b�`���ꂽ�Ƃ��ɌĂяo����܂��B
            /// </summary>
            virtual void OnAttach() {}

            /// <summary>
            /// �R���|�[�l���g���G���e�B�e�B����f�^�b�`���ꂽ�Ƃ��ɌĂяo����܂��B
            /// </summary>
            virtual void OnDetach() {}

            /// <summary>
            /// ���̃R���|�[�l���g���������Ă���G���e�B�e�B���j�������Ƃ��ɌĂяo����܂��B���\�[�X�̉���������s���܂��B���̃��\�b�h���Őe�G���e�B�e�B�ɃA�N�Z�X���邱�Ƃ͂ł��܂���B
            /// </summary>
            virtual void OnDestroy() {}

            /// <summary>
            /// �O���R���|�[�l���g����̃��b�Z�[�W����M���ď������s���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�f�[�^�B</param> 
            virtual void ReceiveMessage(const string& message, void* params[]) {}

        private:

            friend class Entity;

            EntityComponent* back = this;

            EntityComponent* next = this;

            Entity* owner = nullptr;
        };
    }
}
