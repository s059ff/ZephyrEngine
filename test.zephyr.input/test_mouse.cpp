#include "zephyr\print.h"
#include "zephyr\string.h"

#include "zephyr.input\Mouse.h"

using namespace zephyr;
using namespace zephyr::input;

void test_mouse()
{
    Mouse mouse;
    mouse.Update();

    while (0 <= GetKeyState('Q'))
    {
        mouse.Update();

        system("cls");

        println(std::cout, "To end this test, please push 'Q'.");
        println(std::cout, "Left = {0}", mouse.Left);
        println(std::cout, "Center = {0}", mouse.Center);
        println(std::cout, "Right = {0}", mouse.Right);
        println(std::cout, "X = {0}", mouse.X);
        println(std::cout, "Y = {0}", mouse.Y);
        println(std::cout, "Movement-X = {0}", mouse.MovementX);
        println(std::cout, "Movement-Y = {0}", mouse.MovementY);
        println(std::cout, "Movement-Z = {0}", mouse.MovementZ);

        Sleep(1000);
    }
}
