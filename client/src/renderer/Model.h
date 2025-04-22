#pragma once

#include "glm/glm.hpp"
#include "vulkan/vulkan.h"

#include <vector>
#include <iostream>

namespace TT {
    struct Buffer {
        VkBuffer Handle = nullptr;
        VkDeviceMemory Memory = nullptr;
        VkDeviceSize Size = 0;
        VkBufferUsageFlagBits Usage = VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;
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

    class Model {

    public:
        Model();
        Model(VkDevice &device, VkPhysicalDevice physicalDevice, const std::string& path);
        Model(VkDevice &device, VkPhysicalDevice physicalDevice, std::vector<Vertex> vertices, std::vector<uint32_t> indices);
        ~Model();

        void CreateBuffers(VkDevice &device, VkPhysicalDevice physicalDevice);
        void Destroy();

        const Buffer& GetVertexBuffer() const { return m_VertexBuffer; }
        const Buffer& GetIndexBuffer() const { return m_IndexBuffer; }
        uint32_t GetIndexCount() const { return m_IndexCount; }
    private:
        void CopyDataToGPU(VkDevice &device);
        void CreateOrResizeBuffer(VkDevice &device, VkPhysicalDevice physicalDevice, Buffer& buffer, uint64_t newSize);

        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;

        Buffer m_VertexBuffer;
        Buffer m_IndexBuffer;
        uint32_t m_IndexCount;
    };

    bool LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t& indexCount);
}