#include <string>

#include "Buffer.h"

namespace zephyr
{
    buffer::buffer()
    {
        m_capacity = 0;
        m_data = nullptr;
        m_size = 0;
    }

    buffer::buffer(const buffer& src) : buffer()
    {
        copy_from(src, src.size());
    }

    buffer::buffer(buffer&& rsrc)
    {
        m_data = rsrc.m_data;
        m_capacity = rsrc.m_capacity;
        m_size = rsrc.m_size;

        rsrc.m_capacity = 0;
        rsrc.m_data = nullptr;
        rsrc.m_size = 0;
    }

    void buffer::operator= (const buffer& src)
    {
        copy_from(src, src.size());
    }

    void buffer::operator= (buffer&& rsrc)
    {
        m_data = rsrc.m_data;
        m_capacity = rsrc.m_capacity;
        m_size = rsrc.m_size;

        rsrc.m_capacity = 0;
        rsrc.m_data = nullptr;
        rsrc.m_size = 0;
    }

    void buffer::resize(size_t bytes)
    {
        if (m_capacity < bytes)
        {
            this->reset();

            m_capacity = bytes;
            m_size = bytes;
            m_data = malloc(m_capacity);
        }
        else
        {
            m_size = bytes;

            memset(m_data, 0, m_capacity);
        }
    }

    void buffer::reserve(size_t bytes)
    {
        if (m_capacity < bytes)
        {
            this->reset();

            m_capacity = bytes;
            m_data = malloc(m_capacity);
        }
    }

    void buffer::reset()
    {
        m_capacity = 0;
        if (m_data != nullptr)
        {
            ::free(m_data);
            m_data = nullptr;
        }
        m_size = 0;
    }

    void buffer::copy_from(const void* src, size_t bytes)
    {
        resize(bytes);

        memcpy(m_data, src, bytes);
    }

    void buffer::copy_from(const buffer& src, size_t bytes)
    {
        assert(bytes <= src.size());

        resize(bytes);
        copy_from(src.data(), bytes);
    }

    void buffer::copy_to(void* dest, size_t bytes) const
    {
        memcpy(dest, m_data, bytes);
    }

    void buffer::copy_to(buffer& dest, size_t bytes) const
    {
        assert(bytes <= size());

        dest.resize(bytes);
        copy_to(dest.data(), bytes);
    }
}
