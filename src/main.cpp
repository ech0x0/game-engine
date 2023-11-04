#include "graphics/window.hpp"
#include "game_engine/timer.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    graphics::initGl();

    graphics::Window window(800, 600, "Title", { 0.1f, 0.1f, 0.1f, 1.f });

    {
        Timer timer;

        vec2<float> vertices[] = {
            { -960.f, -540.f },
            { 960.f, -540.f },
            { 0.0f, 540.f }
        };
        unsigned int indices[] = {
            0, 1, 2
        };

        graphics::BufferLayout bufferLayout;
        bufferLayout.attributes.push_back(graphics::VertexAttribute(2, GL_FLOAT, GL_FALSE, 0));
        bufferLayout.stride = sizeof(vec2<float>);

        graphics::Drawable dr("basic", (void*)vertices, 3 * sizeof(vec2<float>), indices, 3, GL_STATIC_DRAW, bufferLayout);
        while (!window.shouldClose()) {
            window.draw(&dr);
            window.render();
            auto timeElapsed = timer.tick(60);
        }
    }

    graphics::destroyGl();
    return 0;
}
