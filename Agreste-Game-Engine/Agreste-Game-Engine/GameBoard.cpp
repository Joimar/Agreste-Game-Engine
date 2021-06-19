#include "GameBoard.h"

void GameBoard::thirdPersonCamera(GameObject obj)
{
	(*this->camera).setYaw(obj.getYaw());
	(*this->camera).setPitch(obj.getPitch());
	(*this->camera).updateThirdPersonVectors();
}


GameBoard::GameBoard(float ScreenWidth, float ScreenHeight) :
	skyCube("../Agreste-Game-Engine/skybox")
{
	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;
	this->setModel(glm::mat4(1));
	this->setProjection(glm::perspective((*camera).GetZoom(), (GLfloat)ScreenWidth / (GLfloat)ScreenHeight, 0.1f, 100.0f));
	this->setView((*camera).GetViewMatrix());
	// OpenGL options
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void GameBoard::drawGameObjects()
{
	glClearColor(0.0, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	this->setProjection(glm::perspective((*camera).GetZoom(), (GLfloat)ScreenWidth / (GLfloat)ScreenHeight, 0.1f, 100.0f));
	this->setView((*camera).GetViewMatrix());
	this->setModel (glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)));	// it's a bit too big for our scene, so scale it down
	if (!this->gameObjects.empty())
	{
		for (size_t i = 0; i < this->gameObjects.size(); i++)
		{
			if (!(*this->gameObjects[i]).isStencilMode()) 
			{
				(*this->gameObjects[i]).draw(*this);
			}
			else 
			{
				(*this->gameObjects[i]).drawStencil(*this);
			}
			
		}
	}
	this->skyCube.draw(glm::mat4(glm::mat3((*this->getCamera()).GetViewMatrix())), this->getProjection());
}

glm::mat4 GameBoard::getModel()
{
	return this->model;
}

void GameBoard::setModel(glm::mat4 model)
{
	this->model = model;
}

glm::mat4 GameBoard::getView()
{
	return this->view;
}

void GameBoard::setView(glm::mat4 view)
{
	this->view = view;
}

glm::mat4 GameBoard::getProjection()
{
	return this->projection;
}

void GameBoard::setProjection(glm::mat4 projection)
{
	this->projection = projection;
}

Camera* GameBoard::getCamera()
{
	return this->camera;
}

void GameBoard::setCamera(Camera *cam)
{
	this->camera = cam;
}

Cubemap GameBoard::getSkyCube()
{
	return this->skyCube;
}

void GameBoard::setSkyCube(string path)
{
	Cubemap newCube(path);
	this->skyCube = newCube;
}

float GameBoard::getScreenWidth()
{
	return this->ScreenWidth;
}

float GameBoard::getScreenHeight()
{
	return this->ScreenHeight;
}

void GameBoard::addGameObject(string const & objPath, const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath)
{
	GameObject *aux = new GameObject(objPath, vertexShaderPath, fragmentShaderPath);
	gameObjects.push_back(aux);
}




