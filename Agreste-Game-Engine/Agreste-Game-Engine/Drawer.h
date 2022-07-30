#pragma once
#include "GameObject.h"
#include "GameBoard.h"
#include <vector>
#include <glm/glm.hpp>
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
		void drawAllObjects(GameBoard & board);
		void drawSkybox(GameBoard & board, Cubemap & skybox);
		void drawStancil(GameBoard & board, GameObject & object);
		void drawSkybox(Cubemap & skybox);
		void drawScene(GameBoard & board, Cubemap & skybox);
	
};

