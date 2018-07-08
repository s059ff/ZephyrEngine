#include "zephyr\composit.h"
#include "zephyr\test.h"

#include "test.h"

using zephyr::composit;
using zephyr::test;

void test_composit()
{
    composit<int, float, double> a;
    a.type<int>::value = 1;
    a.type<float>::value = 2;
    a.type<double>::value = 3;
    test("Access composit", a.type<int>::value, 1);
    test("Access composit", a.type<float>::value, 2.0f);
    test("Access composit", a.type<double>::value, 3.0);
}
