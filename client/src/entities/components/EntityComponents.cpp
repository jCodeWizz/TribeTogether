#include "../Component.h"
#include "glm/glm.hpp"

namespace TT {

    class Transform : public Component {
    public:
        glm::vec3 position;
        glm::vec3 rotation;
        float scale;

        Transform() {
            this->position = glm::vec3(0, 0, 0);
            this->rotation = glm::vec3(0, 0, 0);
            this->scale = 1;
        }

        Transform(glm::vec3 position) {
            this->position = position;
            this->rotation = glm::vec3(0, 0, 0);
            this->scale = 1;
        }

        Transform(glm::vec3 position, glm::vec3 rotation, float scale) {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }

        void init() override {

        }

        void update(float dt) {

        }
    };
}