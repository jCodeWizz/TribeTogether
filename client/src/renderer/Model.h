#pragma once

#include "Renderer.h"
#include "glm/glm.hpp"
#include "vulkan/vulkan.h"

#include <vector>
#include <iostream>

namespace TT::Renderer {
    struct Buffer {
        VkBuffer Handle = nullptr;
        VkDeviceMemory Memory = nullptr;
        VkDeviceSize Size = 0;
        VkBufferUsageFlagBits Usage = VK_BUFFER_USAGE_FLAG_BITS_MAX_ENUM;
    };

    class Model {

    public:
        Model();
        Model(const std::string& path);
        Model(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
        ~Model();

        void createBuffers();

        VkBuffer vertexBuffer;
        VkBuffer indexBuffer;
        uint32_t indexBufferSize;
    private:
        std::vector<Vertex> m_Vertices;
        std::vector<uint32_t> m_Indices;
    };

    bool LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t& indexCount);
}