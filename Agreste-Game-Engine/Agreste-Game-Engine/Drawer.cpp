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
