#pragma once
#include "GameObject.h"

class Player :public GameObject
{
public:
	
	Player(string const & objPath, const GLchar *vertexShaderPath = "model_loading.vs", const GLchar *fragmentShaderPath = "model_loading.fs");
	void processGamePadAxisMovement(Camera_Movement direction, float axisValue, float deltaTime);
};

