#pragma once
#include <iostream>
#include "GameObject.h"
#include "Array.h"
#include <algorithm>
#include <tuple>
using namespace std;
class World
{
private:
	Array<GameObject> entities;
	Array<GameObject> entitiesToRemove;

public:
	//virtual void onMakeEntity(EntityHandle handle);
	//virtual void onRemoveEntity(EntityHandle handle);
	//virtual void onAddComponent(EntityHandle handle, uint32 id);
	//virtual void onRemoveComponent(EntityHandle handle, uint32 id);
};

