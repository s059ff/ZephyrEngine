#include "common.csh"

partial void update()
{
    _keyboard.Update();
    _mouse.Update();

    mouseX = _mouse.X;
    mouseY = _mouse.Y;
}

ButtonState getkey(KeyCode code)
{
    return _keyboard.GetKeyState(code);
}

bool nowpressed(KeyCode code)
{
    return _keyboard.GetKeyState(code) == NOWPRESSED;
}

bool pressed(KeyCode code)
{
    return _keyboard.GetKeyState(code) == PRESSED;
}

bool released(KeyCode code)
{
    return _keyboard.GetKeyState(code) == RELEASED;
}

bool nowreleased(KeyCode code)
{
    return _keyboard.GetKeyState(code) == NOWRELEASED;
}

bool click()
{
    return _mouse.Left == ButtonState.Pressed;
}

bool clickL()
{
    return _mouse.Left == ButtonState.Pressed;
}

bool clickR()
{
    return _mouse.Right == ButtonState.Pressed;
}

int mouseX, mouseY;

Keyboard _keyboard = new Keyboard();

Mouse _mouse = new Mouse();
