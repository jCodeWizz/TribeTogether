#include <chrono>
#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>
#include <thread>

#include "renderer/Renderer.h"
#include "input/Input.h"
#include "glm/glm.hpp"
#include "world/World.h"

void update(float dt) {

    if (TT::Input::isKeyDown(GLFW_KEY_F11)) {
        TT::Renderer::toggleFullscreen();
    }
}

int main() {
    auto lastFrame = std::chrono::high_resolution_clock::now();

    try {
        TT::Renderer::init();

        auto world = TT::World();
        world.init();

        while (!glfwWindowShouldClose(TT::Renderer::window)) {
            glfwPollEvents();

            auto now = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float>(now - lastFrame).count();
            lastFrame = now;

            update(dt);
            world.update(dt);

            bool c = TT::Renderer::start();
            if (c) {
                world.render();
                TT::Renderer::flush();
            }
        }

        vkDeviceWaitIdle(TT::Renderer::device);
        TT::Renderer::cleanup();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
