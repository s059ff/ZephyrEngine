#include <Windows.h>

#include "zephyr.graphics/Window.h"
#include "zephyr.sound/SoundBuffer.h"
#include "zephyr.sound/SoundDevice.h"
#include "zephyr.sound/StreamingSoundBuffer.h"

using namespace zephyr;
using namespace zephyr::graphics;
using namespace zephyr::sound;

void test_sound()
{
    Window window;
    window.Create(800, 600);

    SoundDevice device;
    device.Create(window.handle);

    SoundBuffer sound1;
    sound1.Create(device, "./explosion1.wav");

    SoundBuffer sound2;
    sound2.Create(device, sound1);

    SoundBuffer sound3;
    sound3.Create(device, "./explosion2.wav");

    sound1.Play();
    Sleep(200);
    sound2.Play();
    Sleep(200);
    sound3.Play();

    window.Start();
}
