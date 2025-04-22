#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>

#include "renderer/Renderer.h"
#include "renderer/Model.h"
#include "input/Input.h"
#include "glm/glm.hpp"
#include "entities/Entity.h"
#include "entities/components/EntityComponents.cpp"
#include "entities/components/RenderingComponents.cpp"

void update() {

    if (TT::Input::isKeyDown(GLFW_KEY_W)) {
        TT::Renderer::m_CameraPosition.z -= 0.01f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_S)) {
        TT::Renderer::m_CameraPosition.z += 0.01f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_A)) {
        TT::Renderer::m_CameraPosition.x -= 0.01f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_D)) {
        TT::Renderer::m_CameraPosition.x += 0.01f;
    }

    if (TT::Input::isKeyDown(GLFW_KEY_LEFT)) {
        TT::Renderer::m_CameraRotation.y += 0.1f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_RIGHT)) {
        TT::Renderer::m_CameraRotation.y -= 0.1f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_UP)) {
        TT::Renderer::m_CameraRotation.x -= 0.1f;
    }
    if (TT::Input::isKeyDown(GLFW_KEY_DOWN)) {
        TT::Renderer::m_CameraRotation.x += 0.1f;
    }
}

int main() {

    try {
        TT::Renderer::init();

        TT::Entity entity = TT::Entity();
        entity.addComponent<TT::Transform>(glm::vec3(2, 2, -2), glm::vec3(0, 45, 0), 1.0f);
        entity.addComponent<TT::ModelComponent>("assets/models/static/untitled.ply");

        while (!glfwWindowShouldClose(TT::Renderer::window)) {
            glfwPollEvents();

            update();

            TT::Renderer::start();
            TT::Renderer::renderModel(entity.getComponent<TT::ModelComponent>()->model->vertexBuffer, entity.getComponent<TT::ModelComponent>()->model->indexBuffer, entity.getComponent<TT::ModelComponent>()->model->indexBufferSize, entity.getComponent<TT::Transform>()->position, entity.getComponent<TT::Transform>()->rotation);
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