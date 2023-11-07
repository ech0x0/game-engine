#include "window.hpp"

#include <stdexcept>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

graphics::Window::Window(const int width, const int height, const char* name, vec4<float> backgroundColor) {
    m_bgColor = backgroundColor;

    // Set windows hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GL_TRUE);

    // Create window
    m_window = glfwCreateWindow(width, height, name, nullptr, nullptr);

    // Check for errors
    if (m_window == nullptr) {
        destroyGl();
        throw std::runtime_error("Failed to initialize GLFW window");
    }

    // Make window context the current one
    glfwMakeContextCurrent(m_window);

    // Set resize callback to our function
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    // Make sure vsync is disabled because we will be limiting fps ourselves
    glfwSwapInterval(0);

    // Get window size
    int screenWidth, screenHeight;
    glfwGetFramebufferSize(m_window, &screenWidth, &screenHeight);

    // Set viewport to the window size
    glViewport(0, 0, screenWidth, screenHeight);

    // Set background colour
    glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffer to the coloured one
    glfwSwapBuffers(m_window);

    // Initalize glew
    // glewExperimental needs to be true
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        destroyGl();
        throw std::runtime_error("Failed to initialize GLEW");
    }
}

graphics::Window::~Window() {
    if (m_window) glfwDestroyWindow(m_window);
}

void graphics::Window::render() {
    // Poll window events, keyboard and mouse inputs
    glfwPollEvents();

    glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, m_bgColor.w);
    glClear(GL_COLOR_BUFFER_BIT);

    while (!drawables.empty()) {
        drawables.front()->draw();
        drawables.pop_front();
    }

    // Swap buffers
    glfwSwapBuffers(m_window);
}

bool graphics::Window::shouldClose() {
    return glfwWindowShouldClose(m_window);
}

void graphics::Window::draw(Drawable* drawable) {
    drawables.push_back(drawable);
}
