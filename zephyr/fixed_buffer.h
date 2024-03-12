#pragma once

#include "assert.h"
#include "property.h"
#include "uncopyable.h"
#include "type.h"

namespace zephyr
{
    template <size_t Bytes>
    class fixed_buffer : uncopyable
    {
    public:

        fixed_buffer() : m_size(Bytes)
        {
            this->reset();
        }

        fixed_buffer(size_t bytes) : buffer() { this->resize(bytes); }

        ~fixed_buffer() { this->reset(); }

        void clear()
        {
            memset(m_data, 0, m_capacity);
        }

        void resize(size_t bytes)
        {
            assert(m_capacity >= bytes);

            m_size = bytes;
        }

        void reset()
        {
            this->clear();
            m_size = 0;
        }

        void* data() { return m_data; }

        const void* data() const { return m_data; }

        void* data(size_t offset)
        {
            assert(offset < m_size);
            return (byte*)m_data + offset;
        }

        const void* data(size_t offset) const
        {
            assert(offset < m_size);
            return (byte*)m_data + offset;
        }

        size_t size() const { return m_size; }

        size_t capacity() const { return m_capacity; }

        template <typename T>
        T& access(size_t offset) { return *reinterpret_cast<T*>(data(offset)); }

        template <typename T>
        const T& access(size_t offset) const { return *reinterpret_cast<const T*>(data(offset)); }

        void copy_from(const void* src, size_t bytes)
        {
            resize(bytes);

            memcpy(m_data, src, bytes);
        }

        template <size_t _Size>
        void copy_from(const fixed_buffer<_Size>& src, size_t bytes)
        {
            assert(bytes <= src.size());

            resize(bytes);
            copy_from(src.data(), bytes);
        }

        void copy_to(void* dest, size_t bytes) const
        {
            memcpy(dest, m_data, bytes);
        }

        template <size_t _Size>
        void copy_to(fixed_buffer<_Size>& dest, size_t bytes) const
        {
            assert(bytes <= size());

            dest.resize(bytes);
            copy_to(dest.data(), bytes);
        }

    private:

        static void memset(void* dest, int value, size_t bytes)
        {
#ifdef _WIN64
            using unit = int64_t;
            //size_t count = bytes / sizeof(unit);
            size_t count = bytes >> 3;
            //size_t remain = bytes % sizeof(unit);
            size_t remain = bytes& 0b111;
#else
            using unit = int32_t;
            //size_t count = bytes / sizeof(unit);
            size_t count = bytes >> 2;
            //size_t remain = bytes % sizeof(unit);
            size_t remain = bytes& 0b11;
#endif
            for (size_t i = 0; i < count; i++)
            {
                reinterpret_cast<unit*>(dest)[i] = (unit)value;
            }
            auto ptr = reinterpret_cast<unit*>(dest) + count;
            for (size_t i = 0; i < remain; i++)
            {
                reinterpret_cast<byte*>(ptr)[i] = (byte)value;
            }
        }

        static void memcpy(void* dest, const void* src, size_t bytes)
        {
#ifdef _WIN64
            using unit = int64_t;
            //size_t count = bytes / sizeof(unit);
            size_t count = bytes >> 3;
            //size_t remain = bytes % sizeof(unit);
            size_t remain = bytes& 0b111;
#else
            using unit = int32_t;
            //size_t count = bytes / sizeof(unit);
            size_t count = bytes >> 2;
            //size_t remain = bytes % sizeof(unit);
            size_t remain = bytes& 0b11;
#endif
            for (size_t i = 0; i < count; i++)
            {
                reinterpret_cast<unit*>(dest)[i] = reinterpret_cast<const unit*>(src)[i];
            }
            auto ptr_dest = reinterpret_cast<unit*>(dest) + count;
            auto ptr_src = reinterpret_cast<const unit*>(src) + count;
            for (size_t i = 0; i < remain; i++)
            {
                reinterpret_cast<byte*>(ptr_dest)[i] = reinterpret_cast<const byte*>(ptr_src)[i];
            }
        }

    private:

        byte m_data[Bytes];

        size_t m_size;

        static constexpr size_t m_capacity = Bytes;
    };
}
