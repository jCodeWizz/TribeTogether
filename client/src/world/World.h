#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "../entities/Entity.h"
#include "../entities/components/EntityComponents.cpp"
#include "../entities/components/RenderingComponents.cpp"
#include "../entities/components/ControlComponents.cpp"
#include "../renderer/Renderer.h"

namespace TT {
    class World {
    public:
        void init();
        void create();
        void open();
        void close();

        void update(float dt);
        void render();

    private:
        std::vector<Entity> m_Entities;
    };
}
