#include "graphics/window.hpp"
#include "game_engine/timer.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    graphics::initGl();

    graphics::Window window(800, 600, "Title", { 0.1f, 0.1f, 0.1f, 1.f });

    Timer timer;
    while (!window.shouldClose()) {
        window.render();
        auto timeElapsed = timer.tick(60);
    }

    graphics::destroyGl();
    return 0;
}
