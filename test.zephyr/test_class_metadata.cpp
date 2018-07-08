#include <bitset>

#include "zephyr\print.h"
#include "zephyr\test.h"

#include "zephyr\property.h"
#include "zephyr\dynamic.h"

#include "test.h"

using namespace zephyr;

struct Vector
{
    int x, y, z;

    READWRITE_PROPERTY(int, X, { return x; }, { x = value; });
    READWRITE_PROPERTY(int, Y, { return y; }, { y = value; });
    READWRITE_PROPERTY(int, Z, { return z; }, { z = value; });

    READONLY_PROPERTY(int, XYZ, { return x + y + z; });

    int sum()
    {
        return x + y + z;
    }

    void mul(int k)
    {
        x *= k;
        y *= k;
        z *= k;
    }
};

void test_class_metadata()
{
    println("<Class Metadata Test>");

    ClassMetadata metadata(typeid(Vector), "c", 0, sizeof(Vector));
    metadata.def_field("x", &Vector::x);
    metadata.def_field("y", &Vector::y);
    metadata.def_field("z", &Vector::z);
    metadata.def_property("X", &Vector::_get_X, &Vector::_set_X);
    metadata.def_property("Y", &Vector::_get_Y, &Vector::_set_Y);
    metadata.def_property("Z", &Vector::_get_Z, &Vector::_set_Z);
    metadata.def_property("XYZ", &Vector::_get_XYZ, nullptr);
    metadata.def_method("sum", &Vector::sum);
    metadata.def_method("mul", &Vector::mul);

    {
        Vector c;
        c.x = 11;
        c.y = 22;
        c.z = 33;
        metadata.set<int>(&c, "x", 64);
        test("Read/Write Field", metadata.get<int>(&c, "x"), 64);

        metadata.set<int>(&c, "X", 128);
        test("Read/Write Property", metadata.get<int>(&c, "X"), 128);
    }

    {
        Vector c;
        c.x = 11;
        c.y = 22;
        c.z = 33;
        test("Read Property", metadata.get<int>(&c, "XYZ"), 11 + 22 + 33);

        bool exception_throwed = false;
        try
        {
            metadata.set<int>(&c, "XYZ", -11 - 22 - 33);
        }
        catch (std::runtime_error)
        {
            exception_throwed = true;
        }
        test("Write Undefined Property", exception_throwed);

        test("Readable Property", metadata.properties[3].getter.executable() == true);
        test("Writable Property", metadata.properties[3].setter.executable() == false);
    }

    {
        Vector c;
        c.x = 1;
        c.y = 2;
        c.z = 3;
        test("Invoke Method", metadata.invoke<int>(&c, "sum"), 6);

        metadata.invoke(&c, "mul", 2);
        test("Invoke Method", c.x == 2 && c.y == 4 && c.z == 6);
    }

    println();
}
