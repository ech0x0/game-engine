#include "graphics_base.hpp"

#include <stdexcept>
#include <cstdio>

void glClearErrors() {
    while (glGetError() != GL_NO_ERROR)
        ;
}

bool glGetLatestErrors(const char* function, const char* file, const int line) {
    bool ret = true;

    GLenum err = glGetError();
    while (err != GL_NO_ERROR) {
        const char* errStr;
        switch (err) {
        case GL_INVALID_ENUM:
            errStr = "Invalid enum";
            break;
        case GL_INVALID_VALUE:
            errStr = "Invalid value";
            break;
        case GL_INVALID_OPERATION:
            errStr = "Invalid operation";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errStr = "Invalid framebuffer operation";
            break;
        case GL_OUT_OF_MEMORY:
            errStr = "Out of memory";
            break;
        case GL_STACK_UNDERFLOW:
            errStr = "Stack underflow";
            break;
        case GL_STACK_OVERFLOW:
            errStr = "Stack overflow";
            break;
        default:
            errStr = "Unknown error code";
            break;
        }
        fprintf(stderr, "OpenGL error %d: %s caused by %s in %s at line %d\n", err, errStr, function, file, line);
        err = glGetError();

        ret = false;
    }
    return ret;
}

void printErrorFn(const char* error, const char* file, const int line) {
    fprintf(stderr, "Runtime error: %s caused by line %d in file %s\n", error, line, file);
}

void graphics::initGl() {
    // Initialize GLFW
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}

void graphics::destroyGl() {
    glfwTerminate();
}
