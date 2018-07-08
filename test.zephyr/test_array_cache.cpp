#include "zephyr\array_cache.h"

#include "test.h"

using namespace zephyr;

void test_array_cache()
{
    array_cache<int> ary(10, 4);

    ary[1];
    ary[5];
    ary[1];
    ary[2];
    ary[2];
    ary[2];
    ary[1];
    ary[6];
    ary[2];

    printf("o—Í‚ª %s ‚É‚È‚Á‚Ä‚¢‚é‚©Šm”F‚µ‚Ä‚­‚¾‚³‚¢...\n", "2 -> 6 -> 1 -> 5");
    ary.debug();
}
