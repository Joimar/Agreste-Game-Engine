#pragma once
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

#include"Mesh.h"
#include"Shader.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>	
#include<map>
#include<vector>

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model
{
	public:
		vector<Texture> textures_loaded;
		vector<Mesh> meshes;
		string directory;
		bool gammaCorrection;

		//constructor expects a filepath to a 3d model
		Model(string const &path, bool gamma = false);

		// draws the model, and thus all its meshes
		void Draw(Shader &shader);

	private:
		// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
		void loadModel(string const &path);
		void processNode(aiNode *node, const aiScene *scene);
		Mesh processMesh(aiMesh *mesh, const aiScene *scene);
		vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
		unsigned int TextureFromFile(const char *path, const string &directory);

};

