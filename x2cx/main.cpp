#include <iostream>
#include <map>
#include <string>

#include <zephyr/print.h>
#include <zephyr/runtime_assert.h>

#include "convert.h"

using zephyr::println;
using zephyr::runtime_assert;

void main(int argc, const char* argv[])
{
    std::string argv1 = (1 < argc) ? argv[1] : "";
    std::string argv2 = (2 < argc) ? argv[2] : "";

    create_d3d9_device();

    std::map<std::string, TemplateShape> template_shapes = {
        {"box", TemplateShape::Box},
        {"cylinder", TemplateShape::Cylinder},
        {"torus", TemplateShape::Torus},
        {"sphere", TemplateShape::Sphere},
        {"teapot", TemplateShape::Teapot},
    };

    if (template_shapes.find(argv1) != template_shapes.end())
    {
        convert(template_shapes[argv1], argv2);
    }
    else
    {
        println(std::cout, "{0} -> {1}", argv1, argv2);
        convert(argv1, argv2);
    }
}
