#include"Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) 
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->setupMesh();
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//1. 绑定VAO
	glBindVertexArray(this->VAO);
	//2.把顶点数组复制到缓冲中供opengl使用
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	//设置顶点坐标指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//设置法线指针
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
	glEnableVertexAttribArray(1);

	//设置顶点的纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(2);

	//设置顶点的切线
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Tangent));
	glEnableVertexAttribArray(3);
	
	//设置顶点的双切线
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Bitangent));
	glEnableVertexAttribArray(4);

	//4.解绑VAO
	glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) 
{
	//理解：纹理对象包含纹理贴图数据，一个纹理单元可以同时绑定多个纹理对象，glActiveTexture激活纹理单元，将带有纹理数据
	//      的纹理对象绑定到纹理单元，然后glUniform1i中使着色器中的纹理采样器绑定到纹理单元0，这样纹理采样器就能
	//      够从当前纹理单元中的纹理对象获取纹理数据（纹素）。
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;

	for (unsigned int i = 0; i < textures.size(); i++) 
	{
		//1.激活纹理单元   2.绑定纹理对象  3.设置纹理取样器位置
		glActiveTexture(GL_TEXTURE0 + i); // 在绑定纹理前需要激活适当的纹理单元  
		// 检索纹理序列号 (N in diffuse_textureN)
		stringstream ss;
		string number;
		string name = textures[i].type;
		if (name == "texture_diffuse")
			ss << diffuseNr++;
		else if (name == "texture_specular")
			ss << specularNr++;
		else if (name == "texture_normal")
			ss << normalNr++;
		else if (name == "texture_height")
			ss << heightNr++;
		number = ss.str();

		glUniform1i(glGetUniformLocation(shader.Program, ("material." + name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	glActiveTexture(GL_TEXTURE0);
	//绘制Mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}