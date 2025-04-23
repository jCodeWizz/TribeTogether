#include "Entity.h"

namespace TT {

    Entity::Entity() {
        m_Id = entityIdCounter++;
    }

    void Entity::init() {
        for (const auto& pair : m_Components) {
            pair.second->init();
        }
    }

    void Entity::update(const float dt) {
        for (const auto& pair : m_Components) {
            pair.second->update(dt);
        }
    }
}
