#include "Model.h"
#include "utils/happly.h"

namespace TT {

    Model::Model() {

    }

    Model::Model(VkDevice &device, uint32_t memType, const std::string& path) {
        if (!LoadModel(path, m_Vertices, m_Indices, m_IndexCount)) {
            std::cerr << "Failed to load model: " << path << "\n";
            return;
        }

        CreateBuffers(device, memType);
    }

    Model::~Model() {
        Destroy();
    }

    void Model::Destroy() {

    }

    void Model::CreateBuffers(VkDevice &device, uint32_t memType) {
        m_VertexBuffer.Usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        CreateOrResizeBuffer(device, memType, m_VertexBuffer, sizeof(Vertex) * m_Vertices.size());

        m_IndexBuffer.Usage = VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        CreateOrResizeBuffer(device, memType, m_IndexBuffer, sizeof(uint32_t) * m_Indices.size());


        CopyDataToGPU(device);
    }

    void Model::CreateOrResizeBuffer(VkDevice &device, uint32_t memType, Buffer& buffer, uint64_t newSize) {
        if (buffer.Handle != VK_NULL_HANDLE)
            vkDestroyBuffer(device, buffer.Handle, nullptr);
        if (buffer.Handle != VK_NULL_HANDLE)
            vkFreeMemory(device, buffer.Memory, nullptr);

        VkBufferCreateInfo bufferCI = { VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO };
        bufferCI.size = newSize;
        bufferCI.usage = buffer.Usage;
        bufferCI.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        if(!vkCreateBuffer(device, &bufferCI, nullptr, &buffer.Handle)) {
            std::cerr << "Error Model 1" << "\n";
        }

        VkMemoryRequirements req;
        vkGetBufferMemoryRequirements(device, buffer.Handle, &req);
        // bd->BufferMemoryAlignment = (bd->BufferMemoryAlignment > req.alignment) ? bd->BufferMemoryAlignment : req.alignment;
        VkMemoryAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = req.size;
        //alloc_info.memoryTypeIndex = ImGui_ImplVulkan_MemoryType(VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, req.memoryTypeBits);
        // FUNCTION TO CALL TODO: alloc_info.memoryTypeIndex = findMemoryType(req.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
        alloc_info.memoryTypeIndex = memType;
        if(!vkAllocateMemory(device, &alloc_info, nullptr, &buffer.Memory)) {
            std::cerr << "Error Model 2" << "\n";
        }

        if(vkBindBufferMemory(device, buffer.Handle, buffer.Memory, 0)) {
            std::cerr << "Error Model 3" << "\n";
        }

        buffer.Size = req.size;
    }

    void Model::CopyDataToGPU(VkDevice &device) {
        void* vbMemory;
        vkMapMemory(device, m_VertexBuffer.Memory, 0, sizeof(Vertex) * m_Vertices.size(), 0, &vbMemory);
        memcpy(vbMemory, m_Vertices.data(), sizeof(Vertex) * m_Vertices.size());
        vkUnmapMemory(device, m_VertexBuffer.Memory);

        void* ibMemory;
        vkMapMemory(device, m_IndexBuffer.Memory, 0, sizeof(uint32_t) * m_Indices.size(), 0, &ibMemory);
        memcpy(ibMemory, m_Indices.data(), sizeof(uint32_t) * m_Indices.size());
        vkUnmapMemory(device, m_IndexBuffer.Memory);
    }

    bool LoadModel(const std::string& path, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t& indexCount) {
        happly::PLYData plyIn(path, false);

        std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
        std::vector<std::array<double, 3>> vNor = plyIn.getVertexNormals();
        std::vector<std::array<unsigned char, 4>> vCol = plyIn.getVertexColors();
        std::vector<std::vector<size_t>> fInd = plyIn.getFaceIndices<size_t>();

        for (int i = 0; i < vPos.size(); i++) {
            glm::vec3 pos = { vPos[i][0], vPos[i][1], vPos[i][2]};
            glm::vec3 col = { vCol[i][0] / 255.0f, vCol[i][1] / 255.0f, vCol[i][2] / 255.0f };

            glm::vec3 nor = { vNor[i][0], vNor[i][1], vNor[i][2]};
            vertices.push_back({ pos, col, nor});
        }

        for (int i = 0; i < fInd.size(); i++) {
            for (int j = 0; j < fInd[i].size(); j++) {
                size_t index = fInd[i][j];
                indices.push_back(index);
            }
        }

        indexCount = indices.size();
        return true;
    }
}