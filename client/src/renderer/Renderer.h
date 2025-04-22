#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>
#include <optional>
#include <cstdint>
#include "../input/Input.h"
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
#include <iostream>
#include <limits>

namespace TT::Renderer {
    inline struct PushConstants {
        glm::mat4 ViewProjection;
        glm::mat4 Transform;
    } m_PushConstants;

    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    struct Vertex {
        glm::vec3 position;
        glm::vec3 colour;
        glm::vec3 normal;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription{};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }

        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, position);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, colour);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, normal);

            return attributeDescriptions;
        }
    };

    inline glm::vec3 m_CameraPosition{0, 0, 2};
    inline glm::vec3 m_CameraRotation{0, 0, 0};

    inline const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    inline constexpr int MAX_FRAMES_IN_FLIGHT = 2;
    inline constexpr uint32_t WIDTH = 1280;
    inline constexpr uint32_t HEIGHT = 720;

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    void init();
    void start();
    void renderModel(VkBuffer vertexBuffer, VkBuffer indexBuffer, uint32_t indexBufferSize, glm::vec3 position, glm::vec3 rotation);
    void flush();
    void cleanup();

    /////////////////////////////
    ///
    /// Vulkan / Rendering variables
    ///
    /////////////////////////////

    inline bool frameBufferResized = false;

    inline GLFWwindow* window;
    inline VkInstance instance;
    inline VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    inline VkDevice device;
    inline VkQueue graphicsQueue;
    inline VkSurfaceKHR surface;
    inline VkQueue presentQueue;
    inline VkSwapchainKHR swapChain;
    inline std::vector<VkImage> swapChainImages;
    inline VkFormat swapChainImageFormat;
    inline VkExtent2D swapChainExtent;
    inline std::vector<VkImageView> swapChainImageViews;
    inline VkRenderPass renderPass;
    inline VkPipelineLayout pipelineLayout;
    inline VkPipeline graphicsPipeline;
    inline std::vector<VkFramebuffer> swapChainFrameBuffers;
    inline VkCommandPool commandPool;
    inline std::vector<VkCommandBuffer> commandBuffers;
    inline std::vector<VkSemaphore> imageAvailableSemaphores;
    inline std::vector<VkSemaphore> renderFinishedSemaphores;
    inline std::vector<VkFence> inFlightFences;
    inline uint32_t currentFrame = 0;
    inline uint32_t imageIndex;
    inline VkImage depthImage;
    inline VkDeviceMemory depthImageMemory;
    inline VkImageView depthImageView;

    void initWindow();
    void initVulkan();
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
    VkBuffer createVertexBuffer(std::vector<Vertex> vertices);
    VkBuffer createIndexBuffer(std::vector<uint32_t> indices);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties,
                      VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createDepthResources();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling,
                                 VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage,
                     VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    VkCommandBuffer beginSingleTimeCommands();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
}
