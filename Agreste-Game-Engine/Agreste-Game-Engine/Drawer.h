#pragma once
#include "GameObject.h"
#include "GameBoard.h"
#include<glm/glm.hpp>
class Drawer
{
protected:
	Drawer();
	

	static Drawer* drawer_;
	 Shader* shader_;
	
	public:
		Drawer(Drawer &other) = delete;
		void operator=(const Drawer &) = delete;

		static Drawer *GetInstance();
		void draw(GameObject & object, GameBoard & board);
	
};

