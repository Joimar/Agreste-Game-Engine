#include "GameObject.h"



GameObject::GameObject(string const & objPath, const GLchar *vertexShaderPath, const GLchar *fragmentShaderPath):
	shader(vertexShaderPath, fragmentShaderPath), 
	model(objPath)
{
	this->position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->fixed = true;
	this->tangible = false;
}

void GameObject::draw(GameBoard & board)
{
	glm::mat4 model = glm::translate(board.getModel(), position);
	glm::mat4 view = board.getView();
	model = glm::translate(model, this->position);
	glm::mat4 projection = board.getProjection();
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
