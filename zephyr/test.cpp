#include <Windows.h>

#include "test.h"

namespace zephyr
{
    enum Color
    {
        Black = 0,
        Blue = 1,
        Green = 2,
        Cyan = 3,
        Red = 4,
        Magenta = 5,
        Brown = 6,
        LightGray = 7,
        DarkGray = 8,
        LightBlue = 9,
        LightGreen = 10,
        LightCyan = 11,
        LightRed = 12,
        LightMagenta = 13,
        Yellow = 14,
        White = 15
    };

    void test(const char* name, bool succeeded)
    {
        printf("%-32s", name);
        auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
        print("[");
        SetConsoleTextAttribute(handle, succeeded ? Color::Green : Color::Red);
        print(std::cout, succeeded ? "OK" : "FAILED");
        SetConsoleTextAttribute(handle, Color::LightGray);
        println("]");
    }
}
