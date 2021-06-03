#pragma once
#include<glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include "GameBoard.h"
#include "Cubemap.h"

using namespace std;

class Cubemap;
class GameBoard;

class GameObject
{
private:
	Shader shader;
	Model model;
	glm::vec3 position;
	glm::vec3 velocity;
	bool fixed;
	bool tangible;

public:
	GameObject(string const & objPath, const GLchar *vertexShaderPath = "model_loading.vs", const GLchar *fragmentShaderPath = "model_loading.fs");
	void draw( GameBoard & board);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getVelocity();
	void setVelocity(glm::vec3 velocity);
	Shader getShader();
};

