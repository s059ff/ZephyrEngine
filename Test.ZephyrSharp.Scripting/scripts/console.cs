#include "common.csh"

void println(string text, params object[] args)
{
    Console.WriteLine(text, args);
}

void println(object o)
{
    Console.WriteLine(o);
}
