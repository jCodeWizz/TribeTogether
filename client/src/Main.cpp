#include <vulkan/vulkan.h>
#include <iostream>
#include <cstdlib>

#include "VulkanApp.h"

int main() {
    TT::VulkanApp app{};

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}