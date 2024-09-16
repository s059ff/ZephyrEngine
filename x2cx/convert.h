#pragma once

#include <string>

enum TemplateShape
{
    Box,
    Cylinder,
    Torus,
    Sphere,
    Teapot
};

void create_d3d9_device();

void convert(std::string src_path, std::string dest_path);

void convert(TemplateShape shape, std::string dest_path);
