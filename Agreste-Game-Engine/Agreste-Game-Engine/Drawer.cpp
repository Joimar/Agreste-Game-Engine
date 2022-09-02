#include "Drawer.h"
Drawer* Drawer:: drawer_ = NULL;

Drawer::Drawer()
{
	stencilShader_ = new Shader("stencil.vs", "stencil.fs");
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
	
		/*if (board.gameObjects.empty() == false) {

			for (size_t i = 0; i < board.gameObjects.size(); i++) {
				if (board.gameObjects[i]->isStencilMode() == false) {
					draw(*board.gameObjects[i], board);
				}
				//else lidar com os casos stencilmode
				else {
					drawStencil(board, *board.gameObjects[i]);
				}
			}
		}*/

	

		for (auto *obj : board.gameObjects) {
			obj->isStencilMode() ? drawStencil(board, *obj) : draw(*obj, board);
			/*if (obj->isStencilMode()) {
				
				drawStencil(board, *obj);
			}
			//else lidar com os casos stencilmode
			else {
				draw(*obj, board);
			}*/
		}
	
	
}

void Drawer::drawSkybox(GameBoard & board, Cubemap & skybox)
{
	//desenha skybox
	
	glm::mat4 view = glm::mat4(glm::mat3((*board.getCamera()).GetViewMatrix()));
	glm::mat4 projection = *board.getProjection();

	glDepthFunc(GL_LEQUAL);
	shader_ = skybox.getShader();

	shader_->Use();
	shader_->setMat4("view", view);
	shader_->setMat4("projection", projection);

	skybox.getShader()->Use();
	skybox.getShader()->setMat4("view", view);
	skybox.getShader()->setMat4("projection", projection);
	//skybox.draw(glm::mat4(glm::mat3((*this->getCamera()).GetViewMatrix())), this->projection);

	// skybox cube
	glBindVertexArray(skybox.getSkyboxVAO());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.getTextureID());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

void Drawer::drawStencil(GameBoard & board, GameObject & object) 
{
	
	glm::mat4 model = glm::translate(board.getModel(), object.getPosition());
	glm::mat4 view = board.getView();
	model = glm::translate(model, object.getPosition());
	glm::mat4 *projection = board.getProjection();
	stencilShader_->Use();
	stencilShader_->setMat4("projection", *projection);
	stencilShader_->setMat4("view", view);
	stencilShader_->setMat4("model", model);
	stencilShader_->setVec4("stencil", object.getRawColor());
	object.getModel().Draw(*object.getShader());
	
}

void Drawer::drawScene(GameBoard & board, Cubemap & skybox)
{
	glClearColor(0.0, 0.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glStencilFunc(GL_ALWAYS, 1, 0xFF);
	glStencilMask(0xFF);

	board.setProjection(glm::perspective(board.getCamera()->GetZoom(), board.getScreenWidth() / board.getScreenHeight(), 0.1f, 100.0f));
	board.setView(board.getCamera()->GetViewMatrix());
	//desenhar skybox primeiro
	this->drawSkybox(board, skybox);
	//Desenhar todos os objects
	this->drawAllObjects(board);


}
