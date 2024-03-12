#include <algorithm>
#include <filesystem>

#include "zephyr\assert.h"
#include "Path.h"

using namespace std;
using namespace std::experimental::filesystem;

namespace zephyr
{
    namespace filesystem
    {
        string Path::GetExtension(const string& filepath)
        {
            auto idx = filepath.find_last_of('.');
            assert(idx != string::npos);
            string ext = filepath.substr(idx);
            transform(ext.cbegin(), ext.cend(), ext.begin(), tolower);
            return ext;
        }

        string Path::GetDirectoryName(const string& _filepath)
        {
            string filepath = _filepath;
            replace(filepath.begin(), filepath.end(), '/', '\\');
            auto idx = filepath.find_last_of('\\');
            if (idx != string::npos)
            {
                return GetFullPath(filepath.substr(0, idx));
            }
            else
            {
                return GetFullPath(".\\");
            }
        }

        string Path::GetFileName(const string& filepath)
        {
            return path(filepath).filename().string();
        }

        string Path::GetFileNameWithoutExtension(const string& filepath)
        {
            string filename = path(filepath).filename().string();
            size_t position = filename.find(".");
            return (string::npos == position) ? filename : filename.substr(0, position);
        }

        string Path::GetFullPath(const string& filepath)
        {
            return canonical(filepath).string();
        }
    }
}
