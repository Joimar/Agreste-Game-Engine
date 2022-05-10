#pragma once
#include<glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include "GameBoard.h"
#include "CameraMovement.h"

constexpr auto threshold = 0.5;

using namespace std;

class GameBoard;

class GameObject
{
protected:
	Shader shader;
	Model model;
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 worldUp;
	glm::vec3 right;
	glm::vec3 edges[2];
	GLfloat moveSpeed;
	bool fixed;
	bool tangible;
	bool stencilMode;
	glm::vec4 rawColor;
	GLfloat yaw,pitch;
	//glm::vec3 max, min;// máximo e mínimo estao na classe mesh
	//glm::vec3 arestaList[2]; // redundante

public:
	GameObject(string const & objPath, const GLchar *vertexShaderPath = "model_loading.vs", const GLchar *fragmentShaderPath = "model_loading.fs");

	void draw( GameBoard & board);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 position);
	glm::vec3 getFront();
	void setFront(glm::vec3 front);
	glm::vec3 getWorldUp();
	void setWorldUp(glm::vec3 worldUp);
	glm::vec3 getUp();
	void setUp(glm::vec3 up);
	glm::vec3 getRight();
	void setRight(glm::vec3 right);
	GLfloat getMoveSpeed();
	void setMoveSpeed(GLfloat moveSpeed);
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
	virtual void processGamePadAxisMovement(Camera_Movement direction ,float axisValue, float deltaTime);
	virtual void processGamePadAxisRotation(GLfloat xOffset, GLfloat yOffset, GLboolean constrainPitch = true);
	Model getModel();
	GLfloat getYaw();
	void setYaw(GLfloat yaw);
	GLfloat getPitch();
	void setPitch(GLfloat pitch);
	void Move(glm::vec3 direction, float deltaTime);
	void updateVectors();
	
};

