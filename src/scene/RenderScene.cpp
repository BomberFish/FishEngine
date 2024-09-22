#include "RenderScene.hpp"
#include <cstdio>

RenderScene::RenderScene() {
    printf("RenderScene created\n");
}

RenderScene::~RenderScene() {
    printf("RenderScene %s destroyed\n", name.c_str());
}

void RenderScene::render() {
    printf("[Warn] RenderScene::render() not implemented\n");
}