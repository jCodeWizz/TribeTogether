#pragma once

#include "../Component.h"
#include <string>
#include "../../Renderer/Model.h"

namespace TT {

    class ModelComponent : public Component {
    public:
        Renderer::Model* model;

        ModelComponent(const std::string& path) {
            model = new Renderer::Model(path);
        }

        void init() override {

        }

        void update(float dt) override {

        }
    };
}