#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>

#include "renderer/Renderer.h"
#include "renderer/Model.h"
#include "glm/glm.hpp"

int main() {

    try {
        TT::Renderer::init();

        TT::Model m = *new TT::Model(TT::Renderer::device, TT::Renderer::physicalDevice, "assets/models/static/untitled.ply");

        while (!glfwWindowShouldClose(TT::Renderer::window)) {
            glfwPollEvents();
            //update();
            //render();

            TT::Renderer::start();
            TT::Renderer::renderModel(m, glm::vec3{ 0.0f}, glm::vec3{0.0f});
            TT::Renderer::flush();
        }

        vkDeviceWaitIdle(TT::Renderer::device);
        TT::Renderer::cleanup();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}