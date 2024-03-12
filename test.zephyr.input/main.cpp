#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

#include <Windows.h>

#include "test.h"

void main()
{
    //puts("Test for mouse device, please push Enter to start.");
    //while (0 <= GetKeyState(VK_RETURN))
    //    Sleep(100);
    //test_mouse();
    //puts("Test for keyboard device, please push Enter to start.");
    //while (0 <= GetKeyState(VK_RETURN))
    //    Sleep(100);
    //test_keyboard();
    puts("Test for joystick device, please push Enter to start.");
    while (0 <= GetKeyState(VK_RETURN))
        Sleep(100);
    test_joystick();
}
