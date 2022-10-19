#include "GameBoard.h"

void GameBoard::thirdPersonCamera(GameObject obj, float distance)
{
	// Set camera behind object
	this->camera->setPosition(obj.getPosition() + glm::vec3(0, 3, 10));
	
	// Get vector from camera to object and make camera point to that vector
	// This is similar to camera.lookAt(obj)
	auto forward = obj.getPosition() - camera->GetPosition();
	this->camera->setFront(forward);
}


GameBoard::GameBoard(float ScreenWidth, float ScreenHeight) :
	skyCube("../Agreste-Game-Engine/skybox")
{
	this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
	this->ScreenWidth = ScreenWidth;
	this->ScreenHeight = ScreenHeight;
	this->setModel(glm::mat4(1));
	this->setModel(glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f)));	// it's a bit too big for our scene, so scale it down
	this->setProjection(glm::perspective((*camera).GetZoom(), (GLfloat)ScreenWidth / (GLfloat)ScreenHeight, 0.1f, 100.0f));
	this->setView((*camera).GetViewMatrix());
	this->distance_from_camera_to_player = 4;
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

GameBoard::~GameBoard()
{
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

glm::mat4 * GameBoard::getProjection()
{
	return &projection;
}

//glm::mat4 GameBoard::getProjection()
//{
//	return this-> projection;
//}

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




