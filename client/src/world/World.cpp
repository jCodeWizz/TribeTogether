#include "World.h"

namespace TT {
    void World::init() {
        auto entity = Entity();
        entity.addComponent<Transform>(glm::vec3(2, 2, -2), glm::vec3(0, 45, 0), 1.0f);
        entity.addComponent<ModelComponent>("assets/models/static/untitled.ply");
        m_Entities.push_back(entity);

        auto camera = Entity();
        camera.addComponent<CameraController>();
        m_Entities.push_back(camera);
    }

    void World::create() {
    }

    void World::open() {
    }

    void World::update(const float dt) {
        for (Entity& entity : m_Entities) {
            entity.update(dt);
        }
    }

    void World::render() {
        for (Entity& entity : m_Entities) {
            if (entity.hasComponent<ModelComponent>()) {
                Renderer::renderModel(
                    entity.getComponent<ModelComponent>()->model->vertexBuffer,
                    entity.getComponent<ModelComponent>()->model->indexBuffer,
                    entity.getComponent<ModelComponent>()->model->indexBufferSize,
                    entity.getComponent<Transform>()->position,
                    entity.getComponent<Transform>()->rotation,
                    entity.getComponent<Transform>()->scale
                );
            }
        }
    }

    void World::close() {
    }
}
