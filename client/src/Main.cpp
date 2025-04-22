#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>

#include "renderer/Renderer.h"
#include "renderer/Model.h"
#include "glm/glm.hpp"

int main() {

    try {
        TT::Renderer::init();

        const std::vector<TT::Vertex> vertices = {
            // Front face (red)
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}},

            // Back face (green)
            {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}},

            // Left face (blue)
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}},

            // Right face (yellow)
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}},

            // Top face (cyan)
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},
            {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},
            {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}},

            // Bottom face (magenta)
            {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},
            {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},
            {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}},
        };

        const std::vector<uint32_t> indices = {
            // Front face
            0, 1, 2, 2, 3, 0,

            // Back face
            4, 5, 6, 6, 7, 4,

            // Left face
            8, 9, 10, 10, 11, 8,

            // Right face
            12, 13, 14, 14, 15, 12,

            // Top face
            16, 17, 18, 18, 19, 16,

            // Bottom face
            20, 21, 22, 22, 23, 20
        };

        TT::Model m = *new TT::Model(TT::Renderer::device, TT::Renderer::physicalDevice, vertices, indices);

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