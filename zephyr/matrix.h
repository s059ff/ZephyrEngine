#pragma once

#include <memory>

namespace zephyr
{
    template <typename _T>
    class matrix
    {
    public:

        matrix() : m_data(nullptr), m_rows(0), m_cols(0) {}

        matrix(size_t rows, size_t cols) : m_data(new _T[rows * cols]()), m_rows(rows), m_cols(cols) {}
        
        void resize(size_t rows, size_t cols)
        {
            m_data.reset(new _T[rows * cols]());
            m_rows = rows;
            m_cols = cols;
        }

        void reset(size_t rows, size_t cols)
        {
            m_data.reset(new _T[rows * cols]());
            m_rows = rows;
            m_cols = cols;
        }

        void copy_from(const _T* data)
        {
            memcpy(m_data.get(), data, sizeof(_T) * m_rows * m_cols);
        }

        const _T* operator[] (size_t i) const { return &m_data[i * m_cols]; }

        _T* operator[] (size_t i) { return &m_data[i * m_cols]; }

        const _T& operator() (size_t i, size_t j) const { return m_data[i * m_cols + j]; }

        _T& operator() (size_t i, size_t j) { return m_data[i * m_cols + j]; }

        _T* data() { return m_data.get(); }

        const _T* data() const { return m_data.get(); }

        const size_t& rows = m_rows;

        const size_t& cols = m_cols;

    private:

        std::unique_ptr<_T[]> m_data;

        size_t m_rows;

        size_t m_cols;
    };
}
