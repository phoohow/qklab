#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>

std::string load_file(const std::string &path)
{
    std::string content;
    FILE *file = fopen(path.c_str(), "rb");
    assert(file);

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, 0, SEEK_SET);
    content.resize(size);
    fread(&content[0], 1, size, file);
    fclose(file);

    return content;
}

void save_file(const std::string &path, const std::string &content)
{
    FILE *file = fopen(path.c_str(), "wb");
    assert(file);

    fwrite(content.c_str(), 1, content.size(), file);
    fclose(file);
}
