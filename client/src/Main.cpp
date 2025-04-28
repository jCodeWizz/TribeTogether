#include <chrono>
#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>
#include <thread>

#include "renderer/Renderer.h"
#include "input/Input.h"
#include "glm/glm.hpp"
#include "network/Network.h"
#include "world/World.h"
#include "Protocol.h"

void update(float dt) {

    if (TT::Input::isKeyPressed(GLFW_KEY_F11)) {
        TT::Renderer::toggleFullscreen();
    }

    if (TT::Input::isKeyPressed(GLFW_KEY_F12)) {
        std::string s = "testing server?";
        TT::Network::send(NW_INIT, std::vector<uint8_t>(s.begin(), s.end()), "127.0.0.1", 9696);
    }
}

int main() {
    auto lastFrame = std::chrono::high_resolution_clock::now();

    try {
        TT::Renderer::init();
        TT::Network::init();

        auto world = TT::World();
        world.init();

        while (!glfwWindowShouldClose(TT::Renderer::window)) {
            glfwPollEvents();

            auto now = std::chrono::high_resolution_clock::now();
            float dt = std::chrono::duration<float>(now - lastFrame).count();
            lastFrame = now;

            update(dt);
            world.update(dt);

            if (TT::Renderer::start()) {
                world.render();
                TT::Renderer::flush();
            }

            TT::Input::update(dt);
        }

        vkDeviceWaitIdle(TT::Renderer::device);
        TT::Renderer::cleanup();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
