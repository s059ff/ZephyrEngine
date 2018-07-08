#include "zephyr\print.h"
#include "zephyr\string.h"

#include "zephyr.input\ButtonState.h"
#include "zephyr.input\KeyCode.h"
#include "zephyr.input\Keyboard.h"

using namespace zephyr;
using namespace zephyr::input;

void test_keyboard()
{
    std::pair<string, KeyCode> keyCodes[] = {
        {"A", KeyCode::A},
        {"B", KeyCode::B},
        {"C", KeyCode::C},
        {"D", KeyCode::D},
        {"E", KeyCode::E},
        {"F", KeyCode::F},
        {"G", KeyCode::G},
        {"H", KeyCode::H},
        {"I", KeyCode::I},
        {"J", KeyCode::J},
        {"K", KeyCode::K},
        {"L", KeyCode::L},
        {"M", KeyCode::M},
        {"N", KeyCode::N},
        {"O", KeyCode::O},
        {"P", KeyCode::P},
        {"Q", KeyCode::Q},
        {"R", KeyCode::R},
        {"S", KeyCode::S},
        {"T", KeyCode::T},
        {"U", KeyCode::U},
        {"V", KeyCode::V},
        {"W", KeyCode::W},
        {"X", KeyCode::X},
        {"Y", KeyCode::Y},
        {"Z", KeyCode::Z},
        {"F1", KeyCode::F1},
        {"F2", KeyCode::F2},
        {"F3", KeyCode::F3},
        {"F4", KeyCode::F4},
        {"F5", KeyCode::F5},
        {"F6", KeyCode::F6},
        {"F7", KeyCode::F7},
        {"F8", KeyCode::F8},
        {"F9", KeyCode::F9},
        {"Left", KeyCode::Left},
        {"Right", KeyCode::Right},
        {"Up", KeyCode::Up},
        {"Down", KeyCode::Down},
        {"Escape", KeyCode::Escape},
        {"Tab", KeyCode::Tab},
        {"LeftShift", KeyCode::LeftShift},
        {"RightShift", KeyCode::RightShift},
        {"LeftCtrl", KeyCode::LeftCtrl},
        {"RightCtrl", KeyCode::RightCtrl},
        {"LeftAlt", KeyCode::LeftAlt},
        {"RightAlt", KeyCode::RightAlt},
        {"Space", KeyCode::Space},
        {"Enter", KeyCode::Enter},
        {"BackSpace", KeyCode::BackSpace},
    };

    Keyboard keyboard;
    keyboard.Update();
    while (true)
    {
        keyboard.Update();

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

        for (auto keyCode : keyCodes)
        {
            auto name = keyCode.first;
            auto state = keyboard.GetKeyState(keyCode.second);
            println(std::cout, "{0} = {1}", name, to_string(state));
        }

        Sleep(1000);
    }
}
