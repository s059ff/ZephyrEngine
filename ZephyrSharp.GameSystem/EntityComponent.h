#pragma once

using namespace System::Collections::Generic;

namespace ZephyrSharp
{
    namespace GameSystem
    {
        ref class Entity;
        ref class EntityComponent;

        /// <summary>
        /// �Q�[�� �G���e�B�e�B�̍\���v�f�ł���G���e�B�e�B �R���|�[�l���g��\���܂��B
        /// </summary>
        public ref class EntityComponent
        {
        public:

            /// <summary>
            /// �R���|�[�l���g���G���e�B�e�B�Ɏ��t�����Ă��邩���ׂ܂��B
            /// </summary>
            property bool HasOwner { bool get() { return owner != nullptr; } }

            /// <summary>
            /// �R���|�[�l���g���������Ă���G���e�B�e�B�B
            /// </summary>
            property Entity^ Owner
            {
                Entity^ get() { return owner; }

                void set(Entity^ value);
            }

            /// <summary>
            /// �O���R���|�[�l���g�Ƀ��b�Z�[�W�𑗐M���܂��B
            /// </summary>
            /// <param name="message">���b�Z�[�W�f�[�^�B</param> 
            void SendMessage(EntityComponent^ one, System::Object^ message, System::Object^ argument)
            {
                one->ReceiveMessage(message, argument);
            }
            
        protected public:

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
            virtual void ReceiveMessage(System::Object^ message, System::Object^ argument) {}

        internal:

            EntityComponent^ back = this;

            EntityComponent^ next = this;

            Entity^ owner = nullptr;
        };
    }
}
