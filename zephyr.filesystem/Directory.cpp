#include <direct.h>

#include <filesystem>
#include <regex>

#include "zephyr\runtime_assert.h"
#include "Directory.h"

#define this (*this)

using namespace std;
using namespace std::experimental::filesystem;

namespace zephyr
{
    namespace filesystem
    {
        string Directory::GetCurrentDirectory()
        {
            char currentPath[FILENAME_MAX] = {};
            _getcwd(currentPath, (int)sizeof(currentPath));
            return string(currentPath);
        }

        void Directory::SetCurrentDirectory(const string& dir)
        {
            _chdir(dir.c_str());
        }

        void Directory::EnumerateFiles(
            const string& dir,
            const function<void(const string&)>& callback)
        {
            for_each(directory_iterator(path(dir)), directory_iterator(),
                [&](const path& p)
            {
                if (is_regular_file(p))
                {
                    callback(p.filename().string());
                }
            });
        }

        void Directory::EnumerateFiles(
            const string& dir,
            const string& pattern,
            const function<void(const string&)>& callback)
        {
            regex regex(pattern);
            EnumerateFiles(dir, [&](const string& path)
            {
                if (regex_match(path, regex))
                {
                    callback(path);
                }
            });
        }

        void Directory::EnumerateDirectories(
            const string& dir,
            const function<void(const string&)>& callback)
        {
            for_each(directory_iterator(path(dir)), directory_iterator(),
                [&](const path& p)
            {
                if (!is_regular_file(p))
                {
                    callback(p.filename().string());
                }
            });
        }

        void Directory::EnumerateDirectories(
            const string& dir,
            const string& pattern,
            const function<void(const string&)>& callback)
        {
            regex regex(pattern);
            EnumerateDirectories(dir, [&](const string& path)
            {
                if (regex_match(path, regex))
                {
                    callback(path);
                }
            });
        }
    }
}
