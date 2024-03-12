#include "zephyr\print.h"
#include "zephyr\string.h"

#include "zephyr.input\ButtonCode.h"
#include "zephyr.input\ButtonState.h"
#include "zephyr.input\JoyStick.h"

using namespace zephyr;
using namespace zephyr::input;

void test_joystick()
{
    JoyStick joystick;
    joystick.DeadZone = 0.2f;

    joystick.Update();

    while (0 <= GetKeyState('Q'))
    {
        joystick.Update();

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

        println(std::cout, "To end this test, please push 'Q'.");
        for (int i = 0; i < 18; i++)
        {
            auto name = std::to_string(i);
            auto state = joystick.GetButtonState((ButtonCode)i);
            auto duration = joystick.GetPressTimeLength((ButtonCode)i);

            println(std::cout, "{0} = {1} ({2})", name, to_string(state), duration);
        }
        println(std::cout, "Axis1-X = {0}", joystick.AxisX);
        println(std::cout, "Axis1-Y = {0}", joystick.AxisY);
        println(std::cout, "Axis2-X = {0}", joystick.SubAxisX);
        println(std::cout, "Axis2-Y = {0}", joystick.SubAxisY);
        println(std::cout, "POV-Left = {0} ({1})", to_string(joystick.Left), joystick.LeftPressTimeLength);
        println(std::cout, "POV-Right = {0} ({1})", to_string(joystick.Right), joystick.RightPressTimeLength);
        println(std::cout, "POV-Up = {0} ({1})", to_string(joystick.Up), joystick.UpPressTimeLength);
        println(std::cout, "POV-Down = {0} ({1})", to_string(joystick.Down), joystick.DownPressTimeLength);

        Sleep(1000);
    }
}
