#include "common.csh"

int frame;

float fps;

partial void initialize()
{
    _timer.Interval = 1000;
    _timer.AutoReset = true;
    _timer.Elapsed += (o, e) => { fps = _count; _count = 0; };
    _timer.Start();
}

partial void update()
{
    frame++;
    _count++;
}

Timer _timer = new Timer();
int _count;
