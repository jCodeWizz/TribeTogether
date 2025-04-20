#include "Input.h"

namespace TT::Input {

    void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods) {
        key -= 32;

        if (action == GLFW_PRESS) {
            if (key > 0 && key < keys.size()) {
                keys[key] = true;
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

    /*
     * TODO: needs update loop
     */
    bool isKeyPressed(const int &key) {
        return false;
    }
}