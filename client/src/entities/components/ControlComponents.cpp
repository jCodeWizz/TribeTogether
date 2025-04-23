#include "../Component.h"
#include "glm/glm.hpp"
#include "../../renderer/Renderer.h"

namespace TT {

    class CameraController : public Component {
    public:
        

        void init() override {
        }

        void update(float dt) {
            if (Input::isKeyDown(GLFW_KEY_W)) {
                Renderer::cameraPosition.z -= 10.0f * dt;
            }
            if (Input::isKeyDown(GLFW_KEY_S)) {
                Renderer::cameraPosition.z += 10.0f * dt;
            }
            if (Input::isKeyDown(GLFW_KEY_A)) {
                Renderer::cameraPosition.x -= 10.0f * dt;
            }
            if (Input::isKeyDown(GLFW_KEY_D)) {
                Renderer::cameraPosition.x += 10.0f * dt;
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