#include "zephyr\print.h"
#include "zephyr\string.h"

#include "zephyr.input\Keyboard.h"

using namespace zephyr;
using namespace zephyr::input;

void test_keyboard()
{
    std::pair<string, Keyboard::KeyCode> keyCodes[] = {
        {"A", Keyboard::KeyCode::A},
        {"B", Keyboard::KeyCode::B},
        {"C", Keyboard::KeyCode::C},
        {"D", Keyboard::KeyCode::D},
        {"E", Keyboard::KeyCode::E},
        {"F", Keyboard::KeyCode::F},
        {"G", Keyboard::KeyCode::G},
        {"H", Keyboard::KeyCode::H},
        {"I", Keyboard::KeyCode::I},
        {"J", Keyboard::KeyCode::J},
        {"K", Keyboard::KeyCode::K},
        {"L", Keyboard::KeyCode::L},
        {"M", Keyboard::KeyCode::M},
        {"N", Keyboard::KeyCode::N},
        {"O", Keyboard::KeyCode::O},
        {"P", Keyboard::KeyCode::P},
        {"Q", Keyboard::KeyCode::Q},
        {"R", Keyboard::KeyCode::R},
        {"S", Keyboard::KeyCode::S},
        {"T", Keyboard::KeyCode::T},
        {"U", Keyboard::KeyCode::U},
        {"V", Keyboard::KeyCode::V},
        {"W", Keyboard::KeyCode::W},
        {"X", Keyboard::KeyCode::X},
        {"Y", Keyboard::KeyCode::Y},
        {"Z", Keyboard::KeyCode::Z},
        {"F1", Keyboard::KeyCode::F1},
        {"F2", Keyboard::KeyCode::F2},
        {"F3", Keyboard::KeyCode::F3},
        {"F4", Keyboard::KeyCode::F4},
        {"F5", Keyboard::KeyCode::F5},
        {"F6", Keyboard::KeyCode::F6},
        {"F7", Keyboard::KeyCode::F7},
        {"F8", Keyboard::KeyCode::F8},
        {"F9", Keyboard::KeyCode::F9},
        {"Left", Keyboard::KeyCode::Left},
        {"Right", Keyboard::KeyCode::Right},
        {"Up", Keyboard::KeyCode::Up},
        {"Down", Keyboard::KeyCode::Down},
        {"Escape", Keyboard::KeyCode::Escape},
        {"Tab", Keyboard::KeyCode::Tab},
        {"LeftShift", Keyboard::KeyCode::LeftShift},
        {"RightShift", Keyboard::KeyCode::RightShift},
        {"LeftCtrl", Keyboard::KeyCode::LeftCtrl},
        {"RightCtrl", Keyboard::KeyCode::RightCtrl},
        {"LeftAlt", Keyboard::KeyCode::LeftAlt},
        {"RightAlt", Keyboard::KeyCode::RightAlt},
        {"Space", Keyboard::KeyCode::Space},
        {"Enter", Keyboard::KeyCode::Enter},
        {"BackSpace", Keyboard::KeyCode::BackSpace},
    };

    Keyboard keyboard;
    keyboard.Update();
    while (0 <= GetKeyState('Q'))
    {
        keyboard.Update();

        system("cls");

        println(std::cout, "To end this test, please push 'Q'.");
        for (auto keyCode : keyCodes)
        {
            auto name = keyCode.first;
            auto state = keyboard.GetKeyState(keyCode.second);
            println(std::cout, "{0} = {1}", name, state);
        }

        Sleep(1000);
    }
}
