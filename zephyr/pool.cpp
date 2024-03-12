#include <cstdlib>
#include <cstdio>

#include "pool.h"

using namespace std;

namespace zephyr
{
    using byte = char;

    pool::pool(size_t objectSize, size_t blockCount)
    {
        constexpr size_t align_bytes = sizeof(void*);
        size_t blockSize = ((sizeof(block) + objectSize + align_bytes - 1) / align_bytes) * align_bytes;

        m_heapSize = blockSize * blockCount;
        m_pPool = malloc(m_heapSize);
        m_next_alloc_block = (block*)m_pPool;
        m_objectSize = objectSize;
        m_blockCount = blockCount;

        block* block = (pool::block*)(m_pPool);
        for (int i = 0; i < blockCount; i++)
        {
            block->next = (pool::block*)((byte*)m_pPool + blockSize * i);
            block = block->next;
        }
        block->next = nullptr;
    }

    pool::~pool()
    {
        free(m_pPool);

        m_heapSize = 0;
        m_pPool = nullptr;
        m_next_alloc_block = nullptr;
        m_objectSize = 0;
        m_blockCount = 0;
    }

    void* pool::alloc()
    {
        block* block = m_next_alloc_block;

        if (block == nullptr)
        {
            throw runtime_error("Heap area has been exhausted.");
        }

        m_next_alloc_block = m_next_alloc_block->next;
        return (byte*)block + sizeof(block);
    }

    void pool::free(void* data)
    {
        block* block = (pool::block*)((byte*)data - sizeof(block));
        block->next = m_next_alloc_block;
        m_next_alloc_block = block;
    }

    void pool::show_status()
    {
        block* it = m_next_alloc_block;
        size_t free_count = 0;
        for (int i = 1; it != nullptr; i++)
        {
            printf("Free space (%d): %p\n", i, it);
            it = it->next;
            free_count++;
        }
        printf("Usage rate: %zd %%\n", 100 * (m_blockCount - free_count) / m_blockCount);
        printf("Free space rate: %zd %%\n", 100 * free_count / m_blockCount);
        printf("Pool size: %zd bytes\n", m_heapSize);
    }
}
