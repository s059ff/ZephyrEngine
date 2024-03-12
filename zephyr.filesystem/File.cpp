#include <fstream>
#include <filesystem>
#include <sys/stat.h>

#include "zephyr\buffer.h"
#include "zephyr\runtime_assert.h"

#include "File.h"

using namespace std;
using namespace std::experimental::filesystem;

namespace zephyr
{
    namespace filesystem
    {
        bool File::Exists(const string& path)
        {
            struct stat st;
            return stat(path.c_str(), &st) == 0;
        }

        string File::ReadAllTexts(const string& path)
        {
            return string((istreambuf_iterator<char>(ifstream(path))), istreambuf_iterator<char>());
        }

        buffer File::ReadAllBytes(const string& path)
        {
            buffer dest;

            ifstream ifs(path, ios::binary);
            runtime_assert(ifs.good());

            ifs.seekg(0, ios::end);

            dest.resize(ifs.tellg());

            ifs.clear();
            ifs.seekg(0, ios::beg);

            ifs.read((char*)dest.data(), dest.size());

            return dest;
        }

        void File::WriteAllBytes(const string& path, const buffer& src)
        {
            ofstream ofs(path, ios::binary);
            runtime_assert(ofs.good());
            ofs.write((const char*)src.data(), src.size());
        }

        void File::WriteAllTexts(const string& path, const string& src)
        {
            ofstream ofs(path);
            runtime_assert(ofs.good());
            ofs.write((const char*)src.c_str(), src.size());
        }

        void File::Copy(const string& filepath1, const string& filepath2)
        {
            copy_file(filepath1, filepath2);
        }
    }
}
