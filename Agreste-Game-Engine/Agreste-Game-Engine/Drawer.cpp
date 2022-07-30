#include "Drawer.h"
Drawer* Drawer:: drawer_ = NULL;

Drawer::Drawer()
{
}

Drawer * Drawer::GetInstance()
{
	if (drawer_ == nullptr) {
		drawer_ = new Drawer();
	}
	return drawer_;
}

void Drawer::draw(GameObject & object, GameBoard & board)
{
	glm::mat4 model = glm::translate(board.getModel(), object.getPosition());
	glm::mat4 view = (*board.getCamera()).GetViewMatrix();
	model = glm::translate(model, object.getPosition());
	GLfloat Yaw = glm::radians(object.getYaw());
	model = glm::rotate(model, Yaw, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians((*board.getCamera()).GetZoom()), (float)board.getScreenWidth() / (float)board.getScreenHeight(), 0.1f, 100.0f);
	
	shader_ = object.getShader();
	shader_->Use();
	
	shader_->setMat4("projection", projection);
	shader_->setMat4("view", view);
	shader_->setMat4("model", model);
	object.getModel().Draw(*shader_);
	
}

void Drawer::drawAllObjects(GameBoard & board)
{
	//desenhar todos os objetos
	//desenhar o skybox
	//
	glClearColor(0.0, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	board.setProjection(glm::perspective(board.getCamera()->GetZoom(), board.getScreenWidth()/board.getScreenHeight(), 0.1f, 100.0f));
	board.setView(board.getCamera()->GetViewMatrix());
	
		if (board.gameObjects.empty() == false) {

			for (size_t i = 0; i < board.gameObjects.size(); i++) {
				if (board.gameObjects[i]->isStencilMode() == false) {
					draw(*board.gameObjects[i], board);
				}
				//else lidar com os casos stencilmode
				else {}
			}
		}
	board.drawGameObjects();

}

void Drawer::drawSkybox(GameBoard & board, Cubemap & skybox)
{
	//desenha skybox

	//skybox.draw(glm::mat4(glm::mat3((*this->getCamera()).GetViewMatrix())), this->projection);
}

void Drawer::drawStancil(GameBoard & board, GameObject & object) 
{
	Shader stencilShader("stencil.vs", "stencil.fs");
	glm::mat4 model = glm::translate(board.getModel(), object.getPosition());
	glm::mat4 view = board.getView();
	model = glm::translate(model, object.getPosition());
	glm::mat4 *projection = board.getProjection();
	stencilShader.Use();
	stencilShader.setMat4("projection", *projection);
	stencilShader.setMat4("view", view);
	stencilShader.setMat4("model", model);
	stencilShader.setVec4("stencil", object.getRawColor());
	object.getModel().Draw(*object.getShader());
	
}

void Drawer::drawScene(GameBoard & board, Cubemap & skybox)
{
	//desenhar skybox primeiro
	//Desenhar todos os objects

}
