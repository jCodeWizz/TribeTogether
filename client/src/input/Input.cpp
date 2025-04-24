#include "Input.h"

namespace TT::Input {

    void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
        key -= 32;

        if (action == GLFW_PRESS) {
            if (key > 0 && key < keys.size()) {
                keys[key] = true;
                keysPressed[key] = true;
            }
        } else if (action == GLFW_RELEASE) {
            if (key > 0 && key < keys.size()) {
                keys[key] = false;
            }
        }
    }

    bool isKeyDown(const int &key) {
        int k = key - 32;

        if (k > 0 && k < keys.size()) {
            return keys[k];
        }

        return false;
    }

    bool isKeyPressed(const int &key) {
        int k = key - 32;

        if (k > 0 && k < keysPressed.size()) {
            return keysPressed[k];
        }

        return false;
    }

    void update(float dt) {
        for (int i = 0; i < keysPressed.size(); i++) {
            keysPressed[i] = false;
        }
    }
}