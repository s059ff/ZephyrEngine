#pragma once

#ifdef _DEBUG
#include <cstdio>  
#endif

namespace ZephyrSharp
{
    /// <summary>
    /// �L���b�V���@�\�t���̔z���\���܂��B
    /// </summary>
    generic <typename T> where T : ref class, gcnew() public ref class ArrayCache
    {
        using LinkedList = System::Collections::Generic::LinkedList<int>;
        using LinkedListNode = System::Collections::Generic::LinkedListNode<int>;
        using IDisposable = System::IDisposable;
        using Object = System::Object;

    public:

        /// <summary>
        /// �V�����C���X�^���X���쐬���܂��B
        /// </summary>
        /// <param name="length">�z��̒����B</param> 
        /// <param name="capacity">�ŋߎQ�Ƃ����f�[�^�Ƃ��ĕێ����Ă����f�[�^�̐��B</param> 
        ArrayCache(int length, int capacity)
            : m_capacity(capacity)
        {
            m_data_array = gcnew array<DataEntry>(length);
            m_accesstime_list = gcnew LinkedList();
        }

        ~ArrayCache()
        {
            this->!ArrayCache();
        }

        !ArrayCache()
        {
            for each (auto% entry in m_data_array)
            {
                delete entry.ptr;
                entry.ptr = T();
            }
        }

        /// <summary>
        /// �z��̗v�f���擾���܂��B
        /// </summary>
        /// <param name="index">�v�f�̃C���f�b�N�X�B</param> 
        T Get(int index)
        {
            auto% data_entry = m_data_array[index];

            if (data_entry.ptr == nullptr)
            {
                // If capacity is over, remove old data.
                if (m_accesstime_list->Count == m_capacity)
                {
                    // Remove from array.
                    int data_array_index = m_accesstime_list->Last->Value;
                    auto% data_entry = m_data_array[data_array_index];
                    data_entry.ptr = T();
                    data_entry.listnode = nullptr;

                    // Remove from list.
                    m_accesstime_list->RemoveLast();
                }

                // Create a new instancce.
                data_entry.ptr = gcnew T();
                m_accesstime_list->AddFirst(index);
                data_entry.listnode = m_accesstime_list->First;
            }
            else
            {
                // Move acess time list entry to front.
                m_accesstime_list->Remove(data_entry.listnode);
                m_accesstime_list->AddFirst(index);

                // Update data entry.
                data_entry.listnode = m_accesstime_list->First;
            }

            return data_entry.ptr;
        }

#ifdef _DEBUG
        void Debug()
        {
            printf("size: %d\n", Size);
            printf("access list: ");
            for each (int index in m_accesstime_list)
            {
                printf("%d ->", index);
            }
            printf("[end]");
        }
#endif

        /// <summary>
        /// �z��̗e�ʂ��擾���܂��B
        /// </summary>
        property int Capacity
        {
            int get() { return m_capacity; }
        }

        /// <summary>
        /// �z��̒������擾���܂��B
        /// </summary>
        property int Size
        {
            int get() { return m_accesstime_list->Count; }
        }

        /// <summary>
        /// �z��̗v�f���擾���܂��B
        /// </summary>
        property T default[int]{ T get(int index) { return Get(index); } }

    private:

        value struct DataEntry
        {
            T ptr;
            LinkedListNode^ listnode;
        };

        array<DataEntry>^ m_data_array;

        LinkedList^ m_accesstime_list;

        const int m_capacity;
    };
}
