#pragma once
#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "graphics_base.hpp"
#include "drawable.hpp"
#include "camera.hpp"

#include "../data_types/vec2.hpp"
#include "../data_types/vec4.hpp"

#include <deque>

namespace graphics {
    class Window {
    private:
        GLFWwindow* m_window;
        vec4<float> m_bgColor;
    public:
        Window(const int width, const int height, const char* name, vec4<float> backgroundColor);
        ~Window();

        void render(Camera* camera);
        bool shouldClose();
    };
} // namespace graphics

#endif