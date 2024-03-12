#pragma once
#pragma once

#include "zephyr\runtime_assert.h"
#include "zephyr\property.h"

namespace zephyr
{
    class pool
    {
        class block
        {
            block* next;

            friend class pool;
        };

    public:

        pool(size_t objectSize, size_t blockCount);

        ~pool();

        void* alloc();

        void free(void* data);

        template <typename _T, typename... _Args>
        _T* alloc(const _Args&... args)
        {
            runtime_assert(m_objectSize <= sizeof(_T), "Type T is oversized.");
            return new(alloc()) _T(args...);
        }

        template <typename _T>
        void free(_T* data)
        {
            data->~_T();
            free((void*)data);
        }

        void show_status();

    public:

        READONLY_PROPERTY(bool, available, const{ return m_pPool != nullptr; });

        READONLY_PROPERTY(size_t, object_max_size, const{ return m_objectSize; });

        READONLY_PROPERTY(size_t, block_count, const{ return m_blockCount; });

        READONLY_PROPERTY(size_t, heap_size, const{ return m_heapSize; });

    private:

        void* m_pPool;

        block* m_next_alloc_block;

        size_t m_objectSize;

        size_t m_heapSize;

        size_t m_blockCount;
    };
}
