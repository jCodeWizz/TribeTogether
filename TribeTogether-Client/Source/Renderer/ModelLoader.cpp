#include "ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "utils/tiny_obj_loader.h"

bool LoadModel(const std::string& path, std::vector<TT::Vertex>& vertices, std::vector<uint32_t>& indices) {

    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warn, err;

    if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
        std::cerr << "Failed to load OBJ file: " << err << std::endl;
        return false;
    }

    std::cout << "Loading model" << "\n";

    for (const auto& shape : shapes) {
        size_t index_offset = 0;

        for (const auto& face : shape.mesh.num_face_vertices) {
            for (size_t v = 0; v < 3; v++) { // Assuming only triangles
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                glm::vec3 position = {
                    attrib.vertices[3 * idx.vertex_index + 0],
                    attrib.vertices[3 * idx.vertex_index + 1],
                    attrib.vertices[3 * idx.vertex_index + 2]
                };

                glm::vec3 normal = (idx.normal_index >= 0) ? glm::vec3{
                    attrib.normals[3 * idx.normal_index + 0],
                    attrib.normals[3 * idx.normal_index + 1],
                    attrib.normals[3 * idx.normal_index + 2]
                } : glm::vec3(0.0f, 0.0f, 1.0f);

                vertices.push_back({ position, normal });
                indices.push_back(indices.size());
            }
            index_offset += face;
        }
    }

    return true;
}
