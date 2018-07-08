#include "zephyr\print.h"
#include "zephyr\string.h"

#include "zephyr.input\ButtonState.h"
#include "zephyr.input\Mouse.h"

using namespace zephyr;
using namespace zephyr::input;

void test_mouse()
{
    Mouse mouse;
    mouse.Update();

    while (true)
    {
        mouse.Update();

        auto to_string = [](ButtonState state) {
            switch (state)
            {
            case ButtonState::Released:
                return "Released";
            case ButtonState::Pressed:
                return "Pressed";
            case ButtonState::NowReleased:
                return "NowReleased";
            case ButtonState::NowPressed:
                return "NowPressed";
            default:
                return "?";
            }
        };

        system("cls");

        println(std::cout, "Left = {0}", to_string(mouse.Left));
        println(std::cout, "Center = {0}", to_string(mouse.Center));
        println(std::cout, "Right = {0}", to_string(mouse.Right));
        println(std::cout, "X = {0}", mouse.X);
        println(std::cout, "Y = {0}", mouse.Y);
        println(std::cout, "Movement-X = {0}", mouse.MovementX);
        println(std::cout, "Movement-Y = {0}", mouse.MovementY);
        println(std::cout, "Movement-Z = {0}", mouse.MovementZ);

        Sleep(1000);
    }
}
