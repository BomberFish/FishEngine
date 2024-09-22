#pragma once 
#include "../common.hpp"

class RenderScene {
public:
	std::string name;
	RenderScene();
	virtual ~RenderScene();
	virtual void render();
};