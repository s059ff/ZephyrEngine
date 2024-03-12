#pragma once

#include "zephyr\string.h"

namespace zephyr
{
    namespace filesystem
    {
        class Path
        {
        public:

            static string GetExtension(const string& filepath);

            static string GetDirectoryName(const string& filepath);

            static string GetFileName(const string& filepath);

            static string GetFileNameWithoutExtension(const string& filepath);

            static string GetFullPath(const string& filepath);
        };
    }
}
