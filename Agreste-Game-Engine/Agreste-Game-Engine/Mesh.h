#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include <string>
#include <vector>

using namespace std;

struct Vertex 
{
//position
	glm::vec3 Position;
//normal
	glm::vec3 Normal;
//TexCoords
	glm::vec2 TexCoords;
//Tangent
	glm::vec3 Tangent;
//Bitangent
	glm::vec3 Bitangent;
};

struct Texture 
{
	unsigned int id;
	string type;
	string path;
};

class Mesh
{
public:
	// mesh Data
	vector<Vertex>       vertices;
	vector<unsigned int> indices;
	vector<Texture>      textures;
	unsigned int VAO;
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader &shader);
private:
	// render data 
	unsigned int VBO, EBO;

	// initializes all the buffer objects/arrays
	void setupMesh();
};

