#include "../Component.h"
#include "glm/glm.hpp"
#include "../../renderer/Renderer.h"

namespace TT {
    class CameraController : public Component {
    public:
        void init() override {
        }

        void update(float dt) {
            glm::mat4 cameraTransform = glm::translate(glm::mat4(1.0f), Renderer::cameraPosition)
                * glm::eulerAngleXYZ(glm::radians(Renderer::cameraRotation.x), glm::radians(Renderer::cameraRotation.y),
                                     glm::radians(Renderer::cameraRotation.z));

            glm::vec3 forward = -cameraTransform[2];
            glm::vec3 side = cameraTransform[0];

            if (Input::isKeyDown(GLFW_KEY_W)) {
                Renderer::cameraPosition += forward * dt * 10.0f;
            }
            if (Input::isKeyDown(GLFW_KEY_S)) {
                Renderer::cameraPosition += -forward * dt * 10.0f;
            }
            if (Input::isKeyDown(GLFW_KEY_A)) {
                Renderer::cameraPosition += -side * dt * 10.0f;
            }
            if (Input::isKeyDown(GLFW_KEY_D)) {
                Renderer::cameraPosition += side * dt * 10.0f;
            }

            if (Input::isKeyDown(GLFW_KEY_LEFT)) {
                Renderer::cameraRotation.y += 100.0f * dt;
            }
            if (Input::isKeyDown(GLFW_KEY_RIGHT)) {
                Renderer::cameraRotation.y -= 100.0f * dt;
            }
            if (Input::isKeyDown(GLFW_KEY_UP)) {
                Renderer::cameraRotation.x -= 100.0f * dt;
            }
            if (Input::isKeyDown(GLFW_KEY_DOWN)) {
                Renderer::cameraRotation.x += 100.0f * dt;
            }
        }
    };
}
