#pragma once

#include "assert.h"
#include "property.h"
#include "uncopyable.h"

namespace zephyr
{
    class buffer
    {
    public:

        buffer();

        buffer(size_t bytes) : buffer() { this->resize(bytes); }

        buffer(const buffer& src);

        buffer(buffer&& rsrc);

        ~buffer() { this->reset(); }

        void operator= (const buffer& src);

        void operator= (buffer&& rsrc);

        void resize(size_t bytes);

        void reserve(size_t bytes);

        void reset();

        void* data() { return m_data; }

        const void* data() const { return m_data; }

        void* data(size_t offset)
        {
            assert(offset < m_size);
            return (unsigned char*)m_data + offset;
        }

        const void* data(size_t offset) const
        {
            assert(offset < m_size);
            return (unsigned char*)m_data + offset;
        }

        size_t size() const { return m_size; }

        size_t capacity() const { return m_capacity; }

        template <typename T>
        T& access(size_t offset) { return *reinterpret_cast<T*>(data(offset)); }

        template <typename T>
        const T& access(size_t offset) const { return *reinterpret_cast<const T*>(data(offset)); }

        void copy_from(const void* src, size_t bytes);
        
        void copy_from(const buffer& src, size_t bytes);

        void copy_to(void* dest, size_t bytes) const;

        void copy_to(buffer& dest, size_t bytes) const;

    private:

        void* m_data;

        size_t m_size;

        size_t m_capacity;
    };
}
