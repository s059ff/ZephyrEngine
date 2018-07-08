#include "zephyr\print.h"
#include "zephyr\test.h"

#include "zephyr.filesystem\File.h"

#include "test.h"

using namespace zephyr;
using namespace zephyr::filesystem;

void test_file()
{
    test("Exists", File::Exists("res/a.txt"), true);
    test("Exists", File::Exists("res/c.txt"), false);
    test("ReadAllTexts", File::ReadAllTexts("res/a.txt"), "Hello, world!!!");
    test("ReadAllTexts", File::ReadAllTexts("res/b.txt"), "Kitty on you lap.");
}
