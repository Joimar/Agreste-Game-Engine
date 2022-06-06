#pragma once
#include<glm/glm.hpp>
#include<vector>
#include"GameObject.h"
#include"Camera.h"
#include"Cubemap.h"

class GameObject;
using namespace std;

class GameBoard
{
private:
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;
	Camera * camera;
	Cubemap skyCube;
	float ScreenWidth, ScreenHeight;
	
public:
	float distance_from_camera_to_player;
	void thirdPersonCamera(GameObject obj, float distance);
	vector<GameObject*> gameObjects;
	GameBoard(float ScreenWidth, float ScreenHeight);
	~GameBoard();
	void drawGameObjects();
	glm::mat4 getModel();
	void setModel(glm::mat4 model);
	glm::mat4 getView();
	void setView(glm::mat4 view);
	glm::mat4 *getProjection();
	void setProjection(glm::mat4 projection);
	Camera * getCamera();
	void setCamera(Camera * cam);
	Cubemap getSkyCube();
	void setSkyCube(string path);
	float getScreenWidth();
	float getScreenHeight();
	void addGameObject(string const & objPath, const GLchar *vertexShaderPath = "model_loading.vs", const GLchar *fragmentShaderPath = "model_loading.fs");
	
};

