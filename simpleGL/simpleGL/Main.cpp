#include"Core\Shader.h"
#include"Dependencies\glfw\GLFW\glfw3.h"
#include"Dependencies\soil\SOIL.h"
#include"Dependencies\glm\glm.hpp"
#include"Dependencies\glm\gtc\matrix_transform.hpp"
#include"Dependencies\glm\gtc\type_ptr.hpp"
#include<iostream>
#include<string>
#include<map>
#include"Core\Camera.h"
#include"Core\Model.h"
#include"Dependencies\assimpd\assimp\vector3.h"
#include"./Dependencies\stb\stb_image.h"

#include"Core\PointLight.h"
#include"Core\DirLight.h"
#include"Core\SpotLight.h"

GLfloat vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
GLuint indices[] = {
	0,1,3,
	1,2,3
};
GLfloat texCoords[] = {
	0.0f, 0.0f,   //左下角
	1.0f, 0.0f,   //右下角
	0.5f, 1.0f    //上中
};
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};

//framebuffer ---second render vertices
GLfloat quadVertices[] = {
   //--coordinate------texCoords---
	-1.0f, -1.0f,     0.0f, 0.0f,
	 1.0f, -1.0f,     1.0f, 0.0f,
	 1.0f,  1.0f,     1.0f, 1.0f,

	-1.0f, -1.0f,     0.0f, 0.0f,
     1.0f,  1.0f,     1.0f, 1.0f,
	-1.0f,  1.0f,     0.0f, 1.0f
};

//草的顶点数据
GLfloat grassVertices[] = {
	0.0f, 0.5f, 0.0f,   0.0f, 0.0f,
	0.0f,-0.5f, 0.0f,   0.0f, 1.0f,
	1.0f,-0.5f, 0.0f,   1.0f, 1.0f,

	0.0f, 0.5f, 0.0f,   0.0f, 0.0f,
	1.0f,-0.5f, 0.0f,   1.0f, 1.0f,
	1.0f, 0.5f, 0.0f,   1.0f, 0.0f
};

//sky box vertices data
float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

GLuint VBO;
GLuint VAO;
GLuint EBO;

GLuint grassVBO;
GLuint grassVAO;

GLuint screenVAO;
GLuint screenVBO;

GLuint skyboxVAO;
GLuint skyboxVBO;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//设置
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//摄像机变量
Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));
GLfloat lastX = SCR_WIDTH / 2.0f;
GLfloat lastY = SCR_HEIGHT / 2.0f;

bool keys[1024];
bool firstMouse = true;

//光源参数
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

//-----------------交互函数----------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();
   
//半透明草  函数
unsigned int SetGrassData(GLuint& VAO, GLuint& VBO, GLfloat vertice[], int verticeLength, const string& filename);
void DrawGrass(Shader& shader, const GLuint& VAO, unsigned int textureId, const std::vector<glm::vec3>& vegetation);

//defalut framebuffer function
void SetQuadData(GLuint& VAO, GLuint& VBO, GLfloat vertice[], int verticeLength);
void DrawQuad(Shader& shader,  GLuint textureColorbuffer);

//load cube map
GLuint loadCubemap(vector<const GLchar*> faces);
void SetCubemapData(GLuint& VAO, GLuint& VBO, GLfloat vertice[], int verticeLength);

int main(int argc, char **argv) 
{
	glfwInit(); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	//设置按键事件
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	int windowWidth, windowHeight;
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	//设置和编译着色器
	Shader shader("./Shaders/Vertex_Shader.glsl", "./Shaders/Fragment_Shader.glsl");
	Shader lightingshader("./Shaders/lamp_verShader.glsl", "./Shaders/lamp_fragShader.glsl");
	Shader screenShader("./Shaders/5.1.framebuffers_screen_vs.glsl", "./Shaders/5.1.framebuffers_screen_fs.glsl");
	Shader skyBoxShader("./Shaders/5.2.cubemap_vs.glsl", "./Shaders/5.2.cubemap_fs.glsl");
	//加载模型
	Model ourModel("../Model_Lib/nanosuit/nanosuit.obj");

	//Sky box
	std::vector<const GLchar*> skyBoxTextrueFile;
	skyBoxTextrueFile.push_back("../skybox/right.jpg");
	skyBoxTextrueFile.push_back("../skybox/left.jpg");
	skyBoxTextrueFile.push_back("../skybox/top.jpg");
	skyBoxTextrueFile.push_back("../skybox/bottom.jpg");
	skyBoxTextrueFile.push_back("../skybox/back.jpg");
	skyBoxTextrueFile.push_back("../skybox/front.jpg");
	GLuint cubemapTexture = loadCubemap(skyBoxTextrueFile);

//灯源对象
	//1.点光源对象
	PointLight pointlight_one(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f,0.09f, 0.032f));
	PointLight pointlight_two(glm::vec3(2.3f, -3.3f, -4.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	PointLight pointlight_three(glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	PointLight pointlight_four(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	//2.平行光对象
	DirLight dirLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.050f, 0.050f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
	//3.聚光灯对象
	SpotLight spotLight(camera.Position- glm::vec3(0.0f,0.0f,18.0f), camera.Front, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)),glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
	
	//半透明窗户 数据设置
//	glEnable(GL_BLEND);   //融合；
	glEnable(GL_CULL_FACE);  //面剔除；
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//cube map setting
	SetCubemapData(skyboxVAO, skyboxVBO, skyboxVertices, sizeof(skyboxVertices) / sizeof(GLfloat));

	//grass data setting
	unsigned int grassTextureId = SetGrassData(grassVAO, grassVBO, grassVertices, sizeof(grassVertices) / sizeof(GLfloat), "./blending_transparent_window.png");
	std::vector<glm::vec3> vegetation;
	vegetation.push_back(glm::vec3(-1.5f, 0.0f, -0.48f));
	vegetation.push_back(glm::vec3(1.5f, 0.0f, 0.51f));
	vegetation.push_back(glm::vec3(0.0f, 0.0f, 0.7f));
	vegetation.push_back(glm::vec3(-0.3f, 0.0f, -2.3f));
	vegetation.push_back(glm::vec3(0.5f, 0.0f, -0.6f));

	//screen data setting
	SetQuadData(screenVAO, screenVBO, quadVertices, sizeof(quadVertices) / sizeof(GLfloat));

	//lighting setting
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  // 只需要绑定VBO不用再次设置VBO的数据，因为容器(物体)的VBO数据中已经包含了正确的立方体顶点数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 设置灯立方体的顶点属性指针(仅设置灯的顶点数据)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//帧缓存对象
	GLuint framebuffer;
	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	//纹理附件
	GLuint texColorBuffer;
	glGenTextures(1, &texColorBuffer);
	glBindTexture(GL_TEXTURE_2D, texColorBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//-----将纹理附件attach 到帧缓存对象中
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
	//渲染缓冲对象  render buffer object
	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//-----将渲染缓冲对象附加到帧缓存中
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
	//检查帧缓冲是否准备好
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	while (!glfwWindowShouldClose(window)) {
		//检查事件;
		glfwPollEvents();
		do_movement();

		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//渲染指令;
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);


		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 trans = projection * view;

		shader.Use();
		//传送矩阵
		shader.setMat4("transform", trans);
		shader.setMat4("model", model);
		shader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

		shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader.setFloat("material.shininess", 32.0f);

		//点光源数据传送
		pointlight_one.TransData(shader, 0);
		pointlight_two.TransData(shader, 1);
		pointlight_three.TransData(shader, 2);
		pointlight_four.TransData(shader, 3);

		//平行光数据传送
		dirLight.TransData(shader);

		//聚光灯数据传送
		spotLight.TransData(shader);
		
		ourModel.Draw(shader);

		//传送草的相关矩阵
		DrawGrass(shader, grassVAO, grassTextureId, vegetation);

		//灯光物体着色器
		lightingshader.Use();
		
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightingshader.setMat4("model", model);
		lightingshader.setMat4("transform", trans);
		   
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//cube map drawing
		glDepthFunc(GL_LEQUAL);
		skyBoxShader.Use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));

		skyBoxShader.setMat4("projection", projection);
		skyBoxShader.setMat4("view", view);

		glBindVertexArray(skyboxVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);


		//defalut framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		screenShader.Use();
		DrawQuad(screenVAO, texColorBuffer);

		//交换缓冲;
		glfwSwapBuffers(window);   
	}

	//glDeleteVertexArrays(1, &VAO);
	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024) 
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

}

void do_movement()
{
	//摄像机控制
	if (keys[GLFW_KEY_W])
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (GLfloat)xpos;
		lastY = (GLfloat)ypos;
		firstMouse = false;
	}

	GLfloat xoffset = (GLfloat)(xpos - lastX);
	GLfloat yoffset = (GLfloat)(lastY - ypos);
	
	lastX = (GLfloat)xpos;
	lastY = (GLfloat)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((GLfloat)yoffset);
}

unsigned int SetGrassData(GLuint& VAO, GLuint& VBO, GLfloat vertice[], int verticeLength, const string&  filename)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*verticeLength, vertice, GL_STATIC_DRAW);

	//设置顶点坐标指针
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	//设置顶点的纹理坐标
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (image)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		//Assign texture to ID
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		//参数设置
		//设置纹理wrap参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		//设置纹理过滤参数
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(image);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(image);
	}
	return textureID;
}

void DrawGrass(Shader& shader, const GLuint& VAO, unsigned int textureId ,const std::vector<glm::vec3>& vegetation)
{
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(shader.Program, "material.texture_diffuse1"), 0);
	glBindTexture(GL_TEXTURE_2D, textureId);

	std::map<float, glm::vec3> sorted;
	for (unsigned int i = 0; i < vegetation.size(); i++)
	{
		float distance = glm::length(camera.Position - vegetation[i]);
		sorted[distance] = vegetation[i];
	}

	glBindVertexArray(VAO);
	glm::mat4 model;

	for (std::map<float, glm::vec3>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
	{
		model = glm::mat4();
		model = glm::translate(model, it->second);
		shader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glBindVertexArray(0);
}

void SetQuadData(GLuint& VAO, GLuint& VBO, GLfloat vertice[], int verticeLength)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verticeLength, vertice, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void DrawQuad(const GLuint& VAO,  GLuint textureColorbuffer)
{
	glBindVertexArray(VAO);
	glDisable(GL_DEPTH_TEST);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

GLuint loadCubemap(vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height, nrComponent;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (int i = 0; i < faces.size(); i++)
	{
		image = stbi_load(faces[i], &width, &height, &nrComponent, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
			GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

void SetCubemapData(GLuint& VAO, GLuint& VBO, GLfloat vertice[], int verticeLength)
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)* verticeLength, vertice, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
}

