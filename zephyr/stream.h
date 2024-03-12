#pragma once

#include <iostream>
#include <sstream>
#include <fstream>

#include "array.h"
#include "string.h"

namespace zephyr
{
    using std::istream;
    using std::ostream;
    using std::fstream;
    using std::ifstream;
    using std::ofstream;
    using std::istringstream;
    using std::ostringstream;
    using std::stringstream;

    using std::wistream;
    using std::wostream;
    using std::wfstream;
    using std::wifstream;
    using std::wofstream;
    using std::wistringstream;
    using std::wostringstream;
    using std::wstringstream;

    void read(istream& stream, void* data, size_t size);

    void write(ostream& stream, const void* data, size_t size);

    template <typename T>
    T read(istream& stream)
    {
        T data;
        stream >> data;
        return data;
    }

    template <typename T>
    void read(istream& stream, T& data)
    {
        stream >> data;
    }

    template <typename T, size_t N>
    array<T, N> read(istream& stream)
    {
        array<T, N> data;
        read(stream, data.data(), sizeof(T) * N);
        return data;
    }

    template <typename T, size_t N>
    void read(istream& stream, array<T, N>& data)
    {
        read(stream, data.data(), sizeof(T) * N);
    }

    template <typename T>
    void write(ostream& stream, const T& data)
    {
        stream << data;
    }

    template <>
    void write(ostream& stream, const char* const& data);

    template <>
    void write(ostream& stream, const string& data);

    template <>
    void write(ostream& stream, const char& data);

    template <typename T, size_t N>
    void write(ostream& stream, const T(&data)[N])
    {
        write(stream, data, sizeof(T) * N);
    }
}
