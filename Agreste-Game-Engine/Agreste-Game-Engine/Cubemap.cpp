#include "Cubemap.h"

Cubemap::Cubemap(std::string path):
	textureID(0),
	shader("skybox.vs", "skybox.fs")
{
	std::vector<std::string> faces = getFacePaths(path);
	loadCubeMap(faces);
	// skybox VAO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->skyBoxVertices), &skyBoxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
}


void Cubemap::draw(glm::mat4 View, glm::mat4 Projection)
{
	// draw skybox as last
	glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
	this->shader.Use();
	shader.setMat4("view", View);
	shader.setMat4("projection", Projection);
	// skybox cube
	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS); // set depth function back to default
}

std::vector<std::string> Cubemap::getFacePaths(std::string path)
{
	std::vector<std::string> aux;
	for (const auto & entry : fs::directory_iterator(path))
	{
		aux.push_back(entry.path().string());
	}
	return aux;
}

unsigned int Cubemap::getTextureID()
{
	return textureID;
}

unsigned int Cubemap::getSkyboxVAO()
{
	return skyboxVAO;
}

unsigned int Cubemap::getSkyboxVBO()
{
	return skyboxVBO;
}

void Cubemap::setTextureID(unsigned int texId)
{
	textureID = texId;
}

void Cubemap::setSkyboxVAO(unsigned int vaoId)
{
	skyboxVAO = vaoId;
}

void Cubemap::setSkyboxVBO(unsigned int vboId)
{
	skyboxVBO = vboId;
}

void Cubemap::loadCubeMap(std::vector<std::string> faces)
{
	
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrComponents;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char *data = SOIL_load_image(faces[i].c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			SOIL_free_image_data(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SOIL_free_image_data(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

}
