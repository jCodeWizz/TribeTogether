#pragma once

#include "Component.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace TT {

    static long entityIdCounter = 0;

    class Entity {
    public:
        Entity();
        void init();
        void update(float dt);

        template <typename T, typename... Args>
        void addComponent(Args&&... args) {
            m_Components[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
            m_Components[typeid(T)]->entity = this;
            m_Components[typeid(T)]->init();
        }

        template <typename T>
        T* getComponent() {
            auto it = m_Components.find(typeid(T));
            return it != m_Components.end() ? dynamic_cast<T*>(it->second.get()) : nullptr;
        }

        template <typename T>
        bool hasComponent() {
            return m_Components.find(typeid(T)) != m_Components.end();
        }

        long getId() const { return m_Id; }

    private:
        std::unordered_map<std::type_index, std::shared_ptr<Component>> m_Components;

        long m_Id = 0;
    };
}