#pragma once

#include "zephyr\string.h"

namespace zephyr
{
    class buffer;

    namespace filesystem
    {
        class File
        {
        public:

            File() = delete;

            static bool Exists(const string& path);

            static buffer ReadAllBytes(const string& path);

            static string ReadAllTexts(const string& path);

            static void WriteAllBytes(const string& path, const buffer& src);

            static void WriteAllTexts(const string& path, const string& src);

            static void Copy(const string& filepath1, const string& filepath2);
        };
    }
}
