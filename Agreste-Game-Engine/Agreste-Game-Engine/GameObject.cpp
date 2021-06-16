#include "GameObject.h"



GameObject::GameObject(string const & objPath, const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath):
	shader(vertexShaderPath, fragmentShaderPath), 
	model(objPath)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->fixed = true;
	this->tangible = false;
	this->stencilMode = false;
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->right = glm::vec3(1.0f, 0.0f, 0.0f);
	this->moveSpeed = 3.0;
	this->rawColor = glm::vec4(0.0f, 0.0f, 0.0f,1.0f);
	
}

void GameObject::draw(GameBoard & board)
{
	glm::mat4 model = glm::translate(board.getModel(), position);
	glm::mat4 view = board.getCamera().GetViewMatrix();
	model = glm::translate(model, this->position);
	glm::mat4 projection = glm::perspective(glm::radians(board.getCamera().GetZoom()), (float)board.getScreenWidth() / (float)board.getScreenHeight(), 0.1f, 100.0f);
	this->shader.Use();
	this->shader.setMat4("projection", projection);
	this->shader.setMat4("view", view);
	this->shader.setMat4("model", model);
	this->model.Draw(this->shader);
}


glm::vec3 GameObject::getPosition()
{
	return this->position;
}

void GameObject::setPosition(glm::vec3 position)
{
	this->position = position;
}

glm::vec3 GameObject::getFront()
{
	return this->front;
}

void GameObject::setFront(glm::vec3 front)
{
	this->front = front;
}

glm::vec3 GameObject::getWorldUp()
{
	return this->worldUp;
}

void GameObject::setWorldUp(glm::vec3 worldUp)
{
	this->worldUp = worldUp;
}

glm::vec3 GameObject::getUp()
{
	return this->up;
}

void GameObject::setUp(glm::vec3 up)
{
	this->up = up;
}

glm::vec3 GameObject::getRight()
{
	return this->right;
}

void GameObject::setRight(glm::vec3 right)
{
	this->right = right;
}

GLfloat GameObject::getMoveSpeed()
{
	return this->moveSpeed;
}

void GameObject::setMoveSpeed(GLfloat moveSpeed)
{
	this->moveSpeed = moveSpeed;
}



Shader GameObject::getShader()
{
	return this->shader;
}

bool GameObject::isFixed()
{
	return this->fixed;
}

void GameObject::fix()
{
	this->fixed = true;
}

void GameObject::unfix()
{
	this->fixed = false;
}

bool GameObject::isTangible()
{
	return this->tangible;
}

void GameObject::setTangibility(bool value)
{
	this->tangible = value;
}

bool GameObject::isStencilMode()
{
	return stencilMode;
}

void GameObject::setStencilMode(bool mode)
{
	this->stencilMode = mode;
}

glm::vec4 GameObject::getRawColor()
{
	return this->rawColor;
}

void GameObject::setRawColor(glm::vec4 color)
{
	this->rawColor = color;
}

 void GameObject::processGamePadAxisMovement(Camera_Movement direction, float axisValue, float deltaTime)
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

Model GameObject::getModel()
{
	return this->model;
}

void GameObject::Move(glm::vec3 direction, float deltaTime)
{
	this->position += direction * moveSpeed*deltaTime;
}


void GameObject::drawStencil( GameBoard & board)
{
	Shader stencilShader("stencil.vs", "stencil.fs");
	glm::mat4 model = glm::translate(board.getModel(), position);
	glm::mat4 view = board.getView();
	model = glm::translate(model, this->position);
	glm::mat4 projection = board.getProjection();
	stencilShader.Use();
	stencilShader.setMat4("projection", projection);
	stencilShader.setMat4("view", view);
	stencilShader.setMat4("model", model);
	stencilShader.setVec4("stencil", rawColor);
	this->model.Draw(this->shader);
}
