#include "ThirdPersonCamera.h"

ThirdPersonCamera::ThirdPersonCamera(GameObject* player):Camera(glm::vec3(0.0f, 0.0f, 0.0f))
{
	this->player = player;
}

void ThirdPersonCamera::updateCamera()
{
	this->pitch = (*player).getPitch();
	this->yaw = (*player).getYaw();
	updateCameraVectors();
}
