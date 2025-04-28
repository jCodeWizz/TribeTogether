#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "../entities/Entity.h"
#include "../entities/components/EntityComponents.h"
#include "../entities/components/RenderingComponents.h"
#include "../entities/components/ControlComponents.h"
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
