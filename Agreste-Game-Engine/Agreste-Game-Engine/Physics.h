#pragma once
#include<glm/glm.hpp>
#include<vector>
#include"GameObject.h"


class Physics
{
private:
	glm::vec3 gravity;
	
public:
	glm::vec3 normalResponse;
	Physics();
	//returns true if the object 1 is coliding with object 2, obj1 is the referential
	bool detectCollision(GameObject obj1, GameObject obj2);
	void gravityForce(vector<GameObject*> GameObjects, float deltaTime);
	
};

