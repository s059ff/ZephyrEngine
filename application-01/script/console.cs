#include "common.csh"

void print(string text, params object[] args)
{
    Console.Write(text, args);
}

void println(string text, params object[] args)
{
    Console.WriteLine(text, args);
}

void print(object o)
{
    Console.Write(o);
}

void println(object o)
{
    Console.WriteLine(o);
}
