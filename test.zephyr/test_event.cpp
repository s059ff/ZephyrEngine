#include <iostream>

#include "zephyr\event.h"

#include "test.h"

using std::cout;
using std::endl;
using zephyr::event;

void test_event()
{
    event<int, double> e;
    e += [](int a, double b) { cout << a << b << endl; };
    e(1, 2.43);

    event<> e2;
    e2 += []() {cout << "Hello, world!!!" << endl; };
    e2();
}
