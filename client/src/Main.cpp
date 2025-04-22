#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>

#include "renderer/Renderer.h"
#include "renderer/Model.h"
#include "input/Input.h"
#include "glm/glm.hpp"

void update() {

    if (TT::Input::isKeyDown(GLFW_KEY_W)) {
        TT::Renderer::m_CameraPosition.z -= 0.1f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_S)) {
        TT::Renderer::m_CameraPosition.z += 0.1f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_A)) {
        TT::Renderer::m_CameraPosition.x -= 0.1f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_D)) {
        TT::Renderer::m_CameraPosition.x += 0.1f;
    }

    if (TT::Input::isKeyDown(GLFW_KEY_LEFT)) {
        TT::Renderer::m_CameraRotation.y += 2.0f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_RIGHT)) {
        TT::Renderer::m_CameraRotation.y -= 2.0f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_UP)) {
        TT::Renderer::m_CameraRotation.x -= 2.0f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_DOWN)) {
        TT::Renderer::m_CameraRotation.x += 2.0f;
    }
}

int main() {

    try {
        TT::Renderer::init();

        const std::vector<TT::Renderer::Vertex> vertices = {
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

        TT::Renderer::Model m = *new TT::Renderer::Model(vertices, indices);
        TT::Renderer::Model m2 = *new TT::Renderer::Model("assets/models/static/untitled.ply");

        while (!glfwWindowShouldClose(TT::Renderer::window)) {
            glfwPollEvents();

            update();

            TT::Renderer::start();
            TT::Renderer::renderModel(m.vertexBuffer, m.indexBuffer, m.indexBufferSize, glm::vec3{ 0.0f}, glm::vec3{0.0f});
            TT::Renderer::renderModel(m2.vertexBuffer, m2.indexBuffer, m2.indexBufferSize, glm::vec3{ 2.0f}, glm::vec3{0.0f});
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