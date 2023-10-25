#pragma once
#ifndef GRAPHICS_BASE_HPP
#define GRAPHICS_BASE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "debugbreak.h"

void glClearErrors();
bool glGetLatestErrors(const char* function, const char* file, const int line);

#define ASSERT(x) if (!(x)) debug_break;
#define glCall(x) glClearErrors();x;ASSERT(glGetLatestErrors(#x, __FILE__, __LINE__));

namespace graphics {
    void initGl();
    void destroyGl();
}

#endif