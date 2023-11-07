#include "graphics/window.hpp"
#include "game_engine/timer.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    graphics::initGl();

    graphics::Window window(800, 450, "Title", { 0.1f, 0.1f, 0.1f, 1.f });

    {
        Timer timer;

        vec2<float> vertices1[] = {
            { -960 / 2, 540 },
            { 960 / 2, 540 },
            { 960 / 2, -540 },
            { -960 / 2, -540 }
        };
        vec2<float> vertices2[] = {
            { -960 / 2 + 1000, 540 },
            { 960 / 2 + 1000, 540 },
            { 960 / 2 + 1000, -540 },
            { -960 / 2 + 1000, -540 }
        };
        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        graphics::BufferLayout bufferLayout;
        bufferLayout.attributes.push_back(graphics::VertexAttribute(2, GL_FLOAT, GL_FALSE, 0));
        bufferLayout.stride = sizeof(vec2<float>);

        graphics::Drawable dr1("basic", true, (void*)vertices1, 4 * sizeof(vec2<float>), indices, 6, GL_STATIC_DRAW, bufferLayout);
        graphics::Drawable dr2("basic", true, (void*)vertices2, 4 * sizeof(vec2<float>), indices, 6, GL_STATIC_DRAW, bufferLayout);
        dr1.setColor({ 0.f, 0.5f, 0.5f, 1.f });
        dr2.setColor({ 1.f, 1.f, 0.5f, 1.f });
        while (!window.shouldClose()) {
            window.draw(&dr1);
            window.draw(&dr2);
            window.render();
            auto timeElapsed = timer.tick(60);
        }
    }

    graphics::destroyGl();
    return 0;
}
