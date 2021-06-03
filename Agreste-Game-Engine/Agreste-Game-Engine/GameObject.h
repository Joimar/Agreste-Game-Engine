#pragma once
#include<glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include "GameBoard.h"

using namespace std;

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
	bool stencilMode;
	glm::vec4 rawColor;

public:
	GameObject(string const & objPath, const GLchar *vertexShaderPath = "model_loading.vs", const GLchar *fragmentShaderPath = "model_loading.fs");
	void draw( GameBoard & board);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getVelocity();
	void setVelocity(glm::vec3 velocity);
	Shader getShader();
	bool isFixed();
	void fix();
	void unfix();
	bool isTangible();
	void setTangibility(bool value);
	bool isStencilMode();
	void setStencilMode(bool mode);
	glm::vec4 getRawColor();
	void setRawColor(glm::vec4 color);
	void drawStencil( GameBoard & board);
};
