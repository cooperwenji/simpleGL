#pragma once
#ifndef MESH_H
#define MESH_H

// std. Includes
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<vector>
using namespace std;
// GL Includes
#include"../Dependencies/glew/glew.h"
#include"../Dependencies/glm/glm.hpp"
#include"../Dependencies/glm/gtc/matrix_transform.hpp"
#include "../Dependencies/assimpd/assimp/Importer.hpp"
#include"../Dependencies/assimpd/assimp/scene.h"
#include "../Dependencies/assimpd/assimp/postprocess.h"
#include"Shader.h"

struct Vertex
{
	glm::vec3 Position;    //位置
	glm::vec3 Normal;      //法线
	glm::vec2 TexCoords;   //纹理坐标
	glm::vec3 Tangent;     //切线
	glm::vec3 Bitangent;   //双切线
};
 
struct Texture
{
	unsigned int id;
	string type;
	aiString path;
};

class Mesh
{
public:
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	unsigned int VAO;

	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	void Draw(Shader shader);
private:
	unsigned int VBO, EBO;
	void setupMesh();
};

#endif // !MESH_H