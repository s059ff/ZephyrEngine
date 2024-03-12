#include <cstdint>

#include "assert.h"
#include "memory.h"

namespace zephyr
{
    void memset(void* dest, int _value, size_t bytes)
    {
#ifdef _WIN64
        int64_t value = _value;
        value &= 0b11111111;

        int64_t data = 0;
        data |= value;
        data |= value << 8;
        data |= value << 16;
        data |= value << 24;
        data |= value << 32;
        data |= value << 40;
        data |= value << 48;
        data |= value << 56;

        size_t count = bytes >> 3;
        {
            int64_t* ptr = (int64_t*)dest;
            for (size_t i = 0; i < count; i++)
            {
                *ptr++ = data;
            }
        }
        {
            int64_t* ptr = (int64_t*)((unsigned char*)dest + bytes) - 1;
            *ptr = data;
        }
#else
        int32_t value = _value;
        value &= 0b11111111;

        int32_t data = 0;
        data |= value;
        data |= value << 8;
        data |= value << 16;
        data |= value << 24;

        size_t count = bytes >> 2;
        {
            int32_t* ptr = (int32_t*)dest;
            for (size_t i = 0; i < count; i++)
            {
                *ptr++ = data;
            }
        }
        {
            int32_t* ptr = (int32_t*)((unsigned char*)dest + bytes) - 1;
            *ptr = data;
        }
#endif
    }

    void memcpy(void* dest, const void* src, size_t bytes)
    {
#ifdef _WIN64
        size_t count = bytes >> 3;
        {
            int64_t* dest_ptr = (int64_t*)dest;
            int64_t* src_ptr = (int64_t*)src;
            for (size_t i = 0; i < count; i++)
            {
                *dest_ptr++ = *src_ptr++;
            }
        }
        {
            int64_t* dest_ptr = (int64_t*)((unsigned char*)dest + bytes) - 1;
            int64_t* src_ptr = (int64_t*)((unsigned char*)src + bytes) - 1;
            *dest_ptr = *src_ptr;
        }
#else
        size_t count = bytes >> 2;
        {
            int32_t* dest_ptr = (int32_t*)dest;
            int32_t* src_ptr = (int32_t*)src;
            for (size_t i = 0; i < count; i++)
            {
                *dest_ptr++ = *src_ptr++;
            }
        }
        {
            int32_t* dest_ptr = (int32_t*)((unsigned char*)dest + bytes) - 1;
            int32_t* src_ptr = (int32_t*)((unsigned char*)src + bytes) - 1;
            *dest_ptr = *src_ptr;
        }
#endif
    }
}
