#include <vulkan/vulkan.h>
#include <iostream>

int main() {
    uint32_t version;
    vkEnumerateInstanceVersion(&version);
    std::cout << "Vulkan Version: " << VK_VERSION_MAJOR(version) << "."
              << VK_VERSION_MINOR(version) << "."
              << VK_VERSION_PATCH(version) << std::endl;
    return 0;
}