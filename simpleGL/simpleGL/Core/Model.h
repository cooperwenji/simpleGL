#pragma once
#ifndef  MODEL_H
#define MODEL_H
#include "../Dependencies/assimpd/assimp/Importer.hpp"
#include"../Dependencies/assimpd/assimp/scene.h"
#include "../Dependencies/assimpd/assimp/postprocess.h"
#include "../Dependencies/soil/SOIL.h"
#include"../Dependencies\stb\stb_image.h"

#include"Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model
{
public:
	//模型数据
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;
	bool gammaCorrection;

	Model(string const & path, bool gamma = false);
	void Draw(Shader shader);
private:
	

	//私有成员函数
	void loadModel(string const& path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
#endif  //! MODEL_H
