#pragma once

#include "assert.h"
#include "functional.h"
#include "list.h"
#include "smart_ptr.h"
#include "vector.h"

namespace zephyr
{
    template <typename T>
    class array_cache
    {
    public:

        array_cache(size_t length, size_t capacity)
            : m_capacity(capacity)
        {
            m_data_array.resize(length);
        }

        T& get(int index)
        {
            assert(index < m_data_array.size());

            auto& data_entry = m_data_array[index];

            if (data_entry.ptr == nullptr)
            {
                // If capacity is over, remove old data.
                if (m_accesstime_list.size() == m_capacity)
                {
                    // Remove from array.
                    int data_array_index = m_accesstime_list.back();
                    auto& data_entry = m_data_array[data_array_index];
                    data_entry.ptr.reset();
                    data_entry.listitr = std::list<int>::iterator();

                    // Remove from list.
                    m_accesstime_list.erase(--m_accesstime_list.end());
                }

                // Create a new instancce.
                data_entry.ptr.reset(new T());
                m_accesstime_list.push_front(index);
                data_entry.listitr = m_accesstime_list.begin();
            }
            else
            {
                // Move acess time list entry to front.
                assert(*data_entry.listitr == index);
                m_accesstime_list.erase(data_entry.listitr);
                m_accesstime_list.push_front(index);

                // Update data entry.
                data_entry.listitr = m_accesstime_list.begin();
            }

            return *data_entry.ptr;
        }

        T& operator[] (int index)
        {
            return get(index);
        }

        size_t capacity()
        {
            return m_capacity;
        }

        size_t size()
        {
            return m_accesstime_list.size();
        }

        void debug()
        {
            printf("size: %zd\n", size());
            printf("access list: ");
            for (auto& index : m_accesstime_list)
            {
                printf("%d -> ", index);
            }
            printf("[end]\n");
        }

    private:

        struct data_entry
        {
            std::unique_ptr<T> ptr;
            std::list<int>::iterator listitr;
        };

        std::vector<data_entry> m_data_array;

        std::list<int> m_accesstime_list;

        const size_t m_capacity;
    };
}
