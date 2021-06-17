#pragma once
#include "Camera.h"
#include "GameObject.h"
class ThirdPersonCamera :
	public Camera
{
private: 
	GameObject* player;
public:
	ThirdPersonCamera(GameObject* player);
	 void updateCamera();
};

