#include "stream.h"

namespace zephyr
{
    void read(istream& stream, void* data, size_t size)
    {
        stream.read((char*)data, size);
    }

    void write(ostream& stream, const void* data, size_t size)
    {
        stream.write((const char*)data, size);
    }

    template <>
    void write(ostream& stream, const char* const& data)
    {
        write(stream, data, sizeof(char) * strlen(data));
    }

    template <>
    void write(ostream& stream, const string& data)
    {
        write(stream, data.data(), sizeof(char) * data.length());
    }

    template <>
    void write(ostream& stream, const char& data)
    {
        stream << data;
    }
}
