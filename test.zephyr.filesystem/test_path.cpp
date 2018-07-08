#include "zephyr\print.h"
#include "zephyr\test.h"

#include "zephyr.filesystem\Path.h"

#include "test.h"

using namespace zephyr;
using namespace zephyr::filesystem;

void test_path()
{
    test("GetDirectoryName", Path::GetDirectoryName("res/a.txt"), "D:\\Documents\\Visual Studio 2017\\Projects\\ZephyrEngine\\test.zephyr.filesystem\\res");
    test("GetExtension", Path::GetExtension("res/a.txt"), ".txt");
    test("GetFileName", Path::GetFileName("res/a.txt"), "a.txt");
    test("GetFileNameWithoutExtension", Path::GetFileNameWithoutExtension("res/a.txt"), "a");
    test("GetFullPath", Path::GetFullPath("res/a.txt"), "D:\\Documents\\Visual Studio 2017\\Projects\\ZephyrEngine\\test.zephyr.filesystem\\res\\a.txt");
}
