#pragma once

#include "zephyr\string.h"
#include "zephyr\functional.h"

#undef GetCurrentDirectory
#undef SetCurrentDirectory

namespace zephyr
{
    namespace filesystem
    {
        class Directory
        {
        public:

            Directory() = delete;

            static string GetCurrentDirectory();

            static void SetCurrentDirectory(const string& dir);

            static void EnumerateFiles(
                const string& dir,
                const function<void(const string&)>& callback);

            static void EnumerateFiles(
                const string& dir,
                const string& pattern,
                const function<void(const string&)>& callback);

            static void EnumerateDirectories(
                const string& dir,
                const function<void(const string&)>& callback);

            static void EnumerateDirectories(
                const string& dir,
                const string& pattern,
                const function<void(const string&)>& callback);
        };
    }
}
