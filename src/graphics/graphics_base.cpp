#include "graphics_base.hpp"

#include <stdexcept>

void graphics::initGl() {
    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

void graphics::destroyGl() {
    glfwTerminate();
}