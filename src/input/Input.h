#pragma once

#include <array>
#include <iostream>
#include "GLFW/glfw3.h"

namespace TT::Input {

    inline std::array<bool, 256> keys;

    void onKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
    bool isKeyDown(const int &key);
    bool isKeyPressed(const int &key);
}
