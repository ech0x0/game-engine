#include "window.hpp"

#include <stdexcept>

graphics::Window::Window(const int width, const int height, const char* name, vec4<float> backgroundColor) {
    bgColor = backgroundColor;

    // Set windows hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

    // Create window
    window = glfwCreateWindow(width, height, name, nullptr, nullptr);

    // Check for errors
    if (window == nullptr) {
        destroyGl();
        throw std::runtime_error("Failed to initialize GLFW window");
    }

    GLFWwindow* previousWindow = glfwGetCurrentContext();

    // Make window context the current one
    glfwMakeContextCurrent(window);

    // Make sure vsync is disabled because we will be limiting fps ourselves
    glfwSwapInterval(0);

    // Get window size
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    // Set viewport to the window size
    glViewport(0, 0, screenWidth, screenHeight);

    // Set background colour
    glClearColor(bgColor.x, bgColor.y, bgColor.z, bgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffer to the coloured one
    glfwSwapBuffers(window);

    // Initalize glew
    // glewExperimental needs to be true
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        destroyGl();
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwMakeContextCurrent(previousWindow);
}

graphics::Window::~Window() {
    if (window) glfwDestroyWindow(window);
}

void graphics::Window::render() {
    // Make window context the current one
    GLFWwindow* previousWindow = glfwGetCurrentContext();
    glfwMakeContextCurrent(window);

    // Poll window events, keyboard and mouse inputs
    glfwPollEvents();

    while (!drawables.empty()) {
        drawables.front()->draw();
        drawables.pop_front();
    }


    glClearColor(bgColor.x, bgColor.y, bgColor.z, bgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
    glViewport(0, 0, screenWidth, screenHeight);

    // Swap buffers
    glfwSwapBuffers(window);

    // Change current context back to the window that had it before
    glfwMakeContextCurrent(previousWindow);
}

bool graphics::Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void graphics::Window::draw(Drawable* drawable) {
    drawables.push_back(drawable);
}
