#pragma once

#include <stdexcept>
#include <string>
#include <sstream>

#include "assert.h"
#include "runtime_assert.h"

namespace zephyr
{
    using std::string;
    using std::stringstream;
    using std::wstring;
    using std::wstringstream;
}

namespace zephyr
{
    template <typename char_type, size_t>
    class basic_static_string;

    template <typename char_type, size_t L>
    class basic_static_string
    {
    private:

        using standard_string = std::string;

        using size_type = size_t;

    public:

        static constexpr size_type npos = (size_type)-1;

    public:

        basic_static_string() = default;

        basic_static_string(const char_type* src) { operator= (src); }

        basic_static_string(const standard_string& src) { operator= (src); }

        template <size_type _L>
        basic_static_string(const basic_static_string<char_type, _L>& src) { operator= (src); }

        basic_static_string& operator = (const char_type* src)
        {
            m_length = 0;
            append(src);

            return *this;
        }

        template <size_type _L>
        basic_static_string& operator = (const basic_static_string<char_type, _L>& src)
        {
            static_assert(capacity() >= src.capacity(), "Capacity is low.");

            auto src_ptr = src.c_str();
            auto dest_ptr = m_data;

            while (*dest_ptr++ = *src_ptr++) {}

            m_length = src.length();

            return *this;
        }

        basic_static_string& operator = (const standard_string& src)
        {
            runtime_assert(capacity() >= src.length());

            auto src_ptr = src.c_str();
            auto dest_ptr = m_data;

            while (*dest_ptr++ = *src_ptr++) {}

            m_length = src.length();

            return *this;
        }

        const char_type operator [] (int index) const
        {
            assert(index < m_length);

            return m_data[index];
        }

        char_type& operator [] (int index)
        {
            assert(index < m_length);

            return m_data[index];
        }

        void append(char_type c)
        {
            size_type len = 1;
            runtime_assert(length() + 1 <= L);

            auto it = end();
            *it = c;
            *(it + 1) = '\0';
            ++m_length;
        }

        void append(const char_type* src)
        {
            size_type len = strlen(src);
            runtime_assert(length() + len <= L);

            auto src_ptr = src;
            auto dest_ptr = end();

            while (*dest_ptr++ = *src_ptr++) {}
            m_length += len;
        }

        template <typename String>
        void append(const String& src)
        {
            size_type len = src.length();
            runtime_assert(length() + len <= L);

            auto src_ptr = src.c_str();
            auto dest_ptr = end();

            while (*dest_ptr++ = *src_ptr++) {}
            m_length += len;
        }

        const char_type at(size_type index) const
        {
            return operator [](index);
        }

        char_type& at(size_type index)
        {
            return operator [](index);
        }

        const char_type* begin() const
        {
            return m_data;
        }

        char_type* begin()
        {
            return m_data;
        }

        const char_type* c_str() const
        {
            return m_data;
        }

        int compare(const basic_static_string& s) const
        {
            return strcmp(c_str(), s.c_str());
        }

        const char_type* data() const
        {
            return c_str();
        }

        bool empty() const
        {
            return length() == 0;
        }

        const char_type* end() const
        {
            return m_data + m_length;
        }

        char_type* end()
        {
            return m_data + m_length;
        }

        size_type find(char_type c, size_type pos = 0)
        {
            for (auto it = begin() + pos; it < end(); it++)
            {
                if (*it == c)
                {
                    return distance(begin(), it);
                }
            }
            return npos;
        }

        size_type find(const char_type* s, size_type pos = 0)
        {
            auto it = strstr(begin() + pos, s);
            return it != nullptr ? distance(begin(), it) : npos;
        }

        template <typename String>
        size_type find(const String& s, size_type pos = 0)
        {
            return find(s.c_str(), pos);
        }

        size_type length() const
        {
            return m_length;
        }

        size_type size() const
        {
            return m_length;
        }

        standard_string string() const
        {
            return standard_string(m_data);
        }

        void clear()
        {
            this->m_length = 0;
            this->m_data[0] = '\0';
        }

        template <size_type _L = L>
        basic_static_string<char_type, _L> substr(size_type pos) const
        {
            return basic_static_string<char_type, _L>(begin() + pos);
        }

        template <size_type _L = L>
        basic_static_string<char_type, _L> substr(size_type pos, size_type len) const
        {
            static_assert(capacity() <= basic_static_string<char_type, _L>::capacity(), "Capacity is low.");

            if (len == string::npos)
            {
                return substr<_L>(pos);
            }
            else
            {
                basic_static_string<char_type, _L> dest;

                auto* src_ptr = m_data + pos;
                auto* dest_ptr = dest.m_data;
                auto count = (size_type)0;

                while ((*dest_ptr++ = *src_ptr++)&& ++count <= len) {}
                dest.m_data[len] = '\0';
                dest.m_length = len;

                return dest;
            }
        }

    public:

        static constexpr size_type capacity()
        {
            return L;
        }

        template <typename Stream>
        friend Stream& operator << (Stream& stream, const basic_static_string& s)
        {
            return stream << s.c_str();
        }

    private:

        template <typename char_type, size_type>
        friend class basic_static_string;

        char_type m_data[L + 1] = { (char_type)0 };

        size_type m_length = 0;
    };

    template <typename char_type, size_t L1, size_t L2>
    bool operator == (const basic_static_string<char_type, L1>& a, const basic_static_string<char_type, L2>& b)
    {
        return (a.length() == b.length()) && (strcmp(a.c_str(), b.c_str()) == 0);
    }
    
    template <typename char_type, size_t L1, size_t L2>
    bool operator != (const basic_static_string<char_type, L1>& a, const basic_static_string<char_type, L2>& b)
    {
        return (a.length() != b.length()) || (strcmp(a.c_str(), b.c_str()) != 0);
    }

    template <size_t L> using static_string = basic_static_string<char, L>;

    template <size_t L> using wstatic_string = basic_static_string<wchar_t, L>;

    template <typename char_type, size_t L>
    bool operator == (const basic_static_string<char_type, L>& a, const char_type* b)
    {
        return (a.length() == strlen(b)) && (strcmp(a.c_str(), b) == 0);
    }

    template <typename char_type, size_t L>
    bool operator == (const char_type* a, const basic_static_string<char_type, L>& b)
    {
        return (b.length() == strlen(a)) && (strcmp(b.c_str(), a) == 0);
    }

    template <size_t L>
    bool operator == (const static_string<L>& a, const string& b)
    {
        return (a.length() == b.length()) && (strcmp(a.c_str(), b.c_str()) == 0);
    }

    template <size_t L>
    bool operator == (const wstatic_string<L>& a, const wstring& b)
    {
        return (a.length() == b.length()) && (strcmp(a.c_str(), b.c_str()) == 0);
    }

    template <size_t L>
    bool operator == (const string& a, const static_string<L>& b)
    {
        return (a.length() == b.length()) && (strcmp(a.c_str(), b.c_str()) == 0);
    }

    template <size_t L>
    bool operator == (const wstring& a, const wstatic_string<L>& b)
    {
        return (a.length() == b.length()) && (strcmp(a.c_str(), b.c_str()) == 0);
    }

    template <typename char_type, size_t L>
    bool operator != (const basic_static_string<char_type, L>& a, const char_type* b)
    {
        return (a.length() != strlen(b)) || (strcmp(a.c_str(), b) != 0);
    }

    template <typename char_type, size_t L>
    bool operator != (const char_type* a, const basic_static_string<char_type, L>& b)
    {
        return (b.length() != strlen(a)) || (strcmp(b.c_str(), a) != 0);
    }

    template <size_t L>
    bool operator != (const static_string<L>& a, const string& b)
    {
        return (a.length() != b.length()) || (strcmp(a.c_str(), b.c_str()) != 0);
    }

    template <size_t L>
    bool operator != (const wstatic_string<L>& a, const wstring& b)
    {
        return (a.length() != b.length()) || (strcmp(a.c_str(), b.c_str()) != 0);
    }

    template <size_t L>
    bool operator != (const string& a, const static_string<L>& b)
    {
        return (a.length() != b.length()) || (strcmp(a.c_str(), b.c_str()) != 0);
    }

    template <size_t L>
    bool operator != (const wstring& a, const wstatic_string<L>& b)
    {
        return (a.length() != b.length()) || (strcmp(a.c_str(), b.c_str()) != 0);
    }

    template <
        typename Arg0 = int,
        typename Arg1 = int,
        typename Arg2 = int,
        typename Arg3 = int,
        typename Arg4 = int,
        typename Arg5 = int,
        typename Arg6 = int,
        typename Arg7 = int>
        string format(
            const char* format,
            const Arg0& arg0 = 0,
            const Arg1& arg1 = 0,
            const Arg2& arg2 = 0,
            const Arg3& arg3 = 0,
            const Arg4& arg4 = 0,
            const Arg5& arg5 = 0,
            const Arg6& arg6 = 0,
            const Arg7& arg7 = 0)
    {
        stringstream ss;

        auto len = strlen(format);
        for (size_t i = 0; i < len; i++)
        {
            if (format[i] == '{'&& isdigit(format[i + 1])&& format[i + 2] == '}')
            {
                int n = format[i + 1] - '0';
                switch (n)
                {
                case 0:
                    ss << arg0;
                    break;
                case 1:
                    ss << arg1;
                    break;
                case 2:
                    ss << arg2;
                    break;
                case 3:
                    ss << arg3;
                    break;
                case 4:
                    ss << arg4;
                    break;
                case 5:
                    ss << arg5;
                    break;
                case 6:
                    ss << arg6;
                    break;
                case 7:
                    ss << arg7;
                    break;
                default:
                    break;
                }
                i += 2;
            }
            else
            {
                ss << format[i];
            }
        }

        return ss.str();
    }

    template <
        typename Arg0 = int,
        typename Arg1 = int,
        typename Arg2 = int,
        typename Arg3 = int,
        typename Arg4 = int,
        typename Arg5 = int,
        typename Arg6 = int,
        typename Arg7 = int>
        wstring format(
            const wchar_t* format,
            const Arg0& arg0 = 0,
            const Arg1& arg1 = 0,
            const Arg2& arg2 = 0,
            const Arg3& arg3 = 0,
            const Arg4& arg4 = 0,
            const Arg5& arg5 = 0,
            const Arg6& arg6 = 0,
            const Arg7& arg7 = 0)
    {
        wstringstream ss;

        auto len = wcslen(format);
        for (size_t i = 0; i < len; i++)
        {
            if (format[i] == '{'&& isdigit(format[i + 1])&& format[i + 2] == '}')
            {
                int n = format[i + 1] - '0';
                switch (n)
                {
                case 0:
                    ss << arg0;
                    break;
                case 1:
                    ss << arg1;
                    break;
                case 2:
                    ss << arg2;
                    break;
                case 3:
                    ss << arg3;
                    break;
                case 4:
                    ss << arg4;
                    break;
                case 5:
                    ss << arg5;
                    break;
                case 6:
                    ss << arg6;
                    break;
                case 7:
                    ss << arg7;
                    break;
                default:
                    break;
                }
                i += 2;
            }
            else
            {
                ss << format[i];
            }
        }

        return ss.str();
    }

    template <typename ...Args>
    string format(
        const string& text,
        const Args& ...arg)
    {
        return format(text.c_str(), arg...);
    }

    template <typename ...Args>
    wstring format(
        const wstring& text,
        const Args& ...arg)
    {
        return format(text.c_str(), arg...);
    }

    template <typename ...Args>
    static_string<1024> cformat(
        const char* format,
        const Args& ...arg)
    {
        char buf[1024];
        sprintf_s(buf, format, arg...);
        return buf;
    }

    template <typename ...Args>
    wstatic_string<1024> cformat(
        const wchar_t* format,
        const Args& ...arg)
    {
        wchar_t buf[1024];
        swprintf_s(buf, format, arg...);
        return buf;
    }

    template <typename ...Args, typename String>
    static_string<1024> cformat(
        const String& format,
        const Args& ...arg)
    {
        return format(format.c_str(), arg...);
    }
}
