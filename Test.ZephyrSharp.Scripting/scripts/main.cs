#include "common.csh"

partial void update()
{
    println("process1");
}

partial void update()
{
    println("process2");
}

const string AppVersion = "0.1.2";

void main(string[] args)
{
    println(ADD(1, 2));     // 3
    println(ADD(JPN, JPN)); // japanjapan

    update();               // process1
                            // process2

    println(__LINE__);      // 23

    println(AppVersion);    // 0.1.2
}
