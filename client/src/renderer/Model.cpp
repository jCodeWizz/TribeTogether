#include "Model.h"
#include "utils/happly.h"

namespace TT::Renderer {

    Model::Model() {

    }

    Model::Model(const std::string& path) {
        if (!LoadModel(path, m_Vertices, m_Indices, indexBufferSize)) {
            std::cerr << "Failed to load model: " << path << "\n";
            return;
        }

        createBuffers();
    }

    Model::Model(std::vector<Vertex> vertices, std::vector<uint32_t> indices) {
        m_Vertices = vertices;
        m_Indices = indices;
        indexBufferSize = indices.size();


        createBuffers();
    }


    Model::~Model() {
    }

    void Model::createBuffers() {
        vertexBuffer = createVertexBuffer(m_Vertices);
        indexBuffer = createIndexBuffer(m_Indices);
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