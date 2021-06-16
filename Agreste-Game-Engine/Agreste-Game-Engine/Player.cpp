#include "Player.h"

Player::Player(string const & objPath, const GLchar *vertexShaderPath , const GLchar *fragmentShaderPath):
	GameObject( objPath, vertexShaderPath,  fragmentShaderPath)
{



}

void Player::processGamePadAxisMovement(Camera_Movement direction, float axisValue, float deltaTime)
{
	float sign;
	if (axisValue > 0)
		sign = -1.0f;
	else
		sign = 1.0f;

	if (direction == FORWARD)
	{
		this->position += front * sign * moveSpeed * deltaTime;

	}
	if (direction == RIGHT)
	{
		this->position -= right * sign * moveSpeed * deltaTime;
	}
}
