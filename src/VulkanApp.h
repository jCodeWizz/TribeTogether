#pragma once
#define GGLFW_INCLUDE_VULKAN

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <optional>
#include <cstdint>

namespace TT {

    const int MAX_FRAMES_IN_FLIGHT = 2;
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class VulkanApp {
    public:
        void run();

        bool frameBufferResized = false;
    private:
        const std::vector<const char*> deviceExtensions = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        GLFWwindow* window;

        VkInstance instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkSurfaceKHR surface;
        VkQueue presentQueue;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkRenderPass renderPass;
        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        std::vector<VkFramebuffer> swapChainFrameBuffers;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        std::vector<VkSemaphore> imageAvailableSemaphores;
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        uint32_t currentFrame = 0;
        uint32_t imageIndex;
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();

        void createInstance();
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        void createLogicalDevice();
        void createSurface();
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        void createSwapChain();
        void createImageViews();
        void createRenderPass();
        void createGraphicsPipeline();
        VkShaderModule createShaderModule(const std::vector<char>& code);
        void createFrameBuffers();
        void createCommandPool();
        void createCommandBuffers();
        void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
        void drawFrame();
        void createSyncObjects();
        void recreateSwapChain();
        void cleanupSwapChain();
    };
}