#include "zephyr\print.h"
#include "zephyr\string.h"

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

        system("cls");

        println(std::cout, "To end this test, please push 'Q'.");
        for (int i = 0; i < 18; i++)
        {
            auto name = std::to_string(i);
            auto state = joystick.GetButtonState((JoyStick::ButtonCode)i);

            println(std::cout, "{0} = {1}", name, state);
        }

        println(std::cout, "POV Left  = {0}", joystick.GetHatSwitchState(JoyStick::HatSwitchCode::Left));
        println(std::cout, "POV Right = {0}", joystick.GetHatSwitchState(JoyStick::HatSwitchCode::Right));
        println(std::cout, "POV Up    = {0}", joystick.GetHatSwitchState(JoyStick::HatSwitchCode::Up));
        println(std::cout, "POV Down  = {0}", joystick.GetHatSwitchState(JoyStick::HatSwitchCode::Down));

        println(std::cout, "Axis1-X = {0}", joystick.Axis1X);
        println(std::cout, "Axis1-Y = {0}", joystick.Axis1Y);
        println(std::cout, "Axis2-X = {0}", joystick.Axis2X);
        println(std::cout, "Axis2-Y = {0}", joystick.Axis2Y);

        Sleep(1000);
    }
}
