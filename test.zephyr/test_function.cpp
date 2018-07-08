#include <iostream>

#include "zephyr\function.h"

#include "test.h"

using std::cout;
using std::endl;

using namespace zephyr;

class C
{
public:

    int add(int x, int y)
    {
        return x + y + z;
    }

    int z;
};

int add(int x, int y)
{
    return x + y;
}

void test_function()
{
    function<int(int, int)> a;
    C c;
    c.z = -1;
    a = &C::add;
    a.instance(&c);
    test("Instance method", a(1, 2), 2);

    int z = -1;
    {
        a = [&](int x, int y)
        {
            return x + y + z;
        };
    }
    test("Lambda", a(1, 2), 2);

    a = add;
    test("Function", a(1, 2), 3);
}
