#include "common.csh"

void chdir(string dir)
{
    Directory.SetCurrentDirectory(dir);
}

void mkdir(string dir)
{
    Directory.CreateDirectory(dir);
}
