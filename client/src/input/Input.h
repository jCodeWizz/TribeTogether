#pragma once

#include <array>
#include "GLFW/glfw3.h"

namespace TT::Input {

    inline std::array<bool, 326> keys;
    inline std::array<bool, 326> keysPressed;

    void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
    bool isKeyDown(const int &key);
    bool isKeyPressed(const int &key);
    void update(float dt);
}
