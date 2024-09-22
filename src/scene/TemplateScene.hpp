#pragma once

#include "../RenderScene.hpp"

class TemplateScene : public RenderScene {
public:
    TemplateScene() {
        name = "template";
    }

    void render() override {
        printf("RenderScene::render() %s\n", name.c_str());
    }
};