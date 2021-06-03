#include "GameObject.h"



GameObject::GameObject(string const & objPath, const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath):
	shader(vertexShaderPath, fragmentShaderPath), 
	model(objPath)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->fixed = true;
	this->tangible = false;
	this->stencilMode = false;
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

glm::vec3 GameObject::getVelocity()
{
	return this->velocity;
}

void GameObject::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
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
