#include "common.csh"

partial void update()
{
    _keyboard.Update();
    _mouse.Update();

    mouseX = _mouse.X;
    mouseY = _mouse.Y;
}

int getkey(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code);
}

bool nowpressed(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) == 1;
}

bool pressed(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) > 0;
}

bool released(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) <= 0;
}

bool nowreleased(Keyboard.KeyCode code)
{
    return _keyboard.GetKeyState(code) == -1;
}

bool click()
{
    return _mouse.Left > 0;
}

bool clickL()
{
    return _mouse.Left > 0;
}

bool clickR()
{
    return _mouse.Right > 0;
}

int mouseX, mouseY;

Keyboard _keyboard = new Keyboard();

Mouse _mouse = new Mouse();
