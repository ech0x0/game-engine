#pragma once
#ifndef GRAPHICS_BASE_HPP
#define GRAPHICS_BASE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace graphics {
    void initGl();
    void destroyGl();
}

#endif