#pragma once

namespace TT {

    class Entity;

    class Component {
    public:
        virtual ~Component() = default;
        virtual void init() = 0;
        virtual void update(float dt) = 0;

        Entity* entity = nullptr;
    };
}
