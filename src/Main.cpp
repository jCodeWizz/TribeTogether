#include <iostream>

#include "VulkanApp.h"

int main() {
    TT::VulkanApp app{};
    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return -1;
    }
    return 1;
}
