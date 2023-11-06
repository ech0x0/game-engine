#pragma once
#ifndef GRAPHICS_BASE_HPP
#define GRAPHICS_BASE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GAME_VERSION 1

void glClearErrors();
bool glGetLatestErrors(const char* function, const char* file, const int line);

void printErrorFn(const char* error, const char* file, const int line);

#define printError(x) printErrorFn(x, __FILE__, __LINE__)

#define glCall(x) \
    x;            \
    glGetLatestErrors(#x, __FILE__, __LINE__);

namespace graphics {
    void initGl();
    void destroyGl();
} // namespace graphics

#endif