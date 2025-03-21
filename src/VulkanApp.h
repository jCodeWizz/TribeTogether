#pragma once
#define GGLFW_INCLUDE_VULKAN

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <fstream>
#include <vector>
#include <string>

namespace TT {
    class VulkanApp {
    public:
        void run();
    private:
        GLFWwindow* window;

        VkInstance instance;

        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();

        void createInstance();
    };
}