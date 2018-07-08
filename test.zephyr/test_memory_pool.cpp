#include "zephyr\print.h"
#include "zephyr\test.h"

#include "zephyr\pool.h"

#include "test.h"

using namespace zephyr;

struct T
{
    int x;
    float y;
    double z;
    char c;
};

void test_memory_pool()
{
    println("<MemoryPool Test>");

    pool pool(sizeof(T), 8);

    auto e1 = pool.alloc<T>();
    auto e2 = pool.alloc<T>();
    e2->x = 137;
    pool.free<T>(e2);

    auto e3 = pool.alloc<T>();
    e3->x = 499;

    test("Alloc/Free", e2, e3);

    pool.show_status();

    println();
}
