#include"Core\Shader.h"
#include"Dependencies\glfw\GLFW\glfw3.h"
#include"Dependencies\soil\SOIL.h"
#include"Dependencies\glm\glm.hpp"
#include"Dependencies\glm\gtc\matrix_transform.hpp"
#include"Dependencies\glm\gtc\type_ptr.hpp"
#include<iostream>
#include<string>
#include"Core\Camera.h"
#include"Core\Model.h"
#include"Dependencies\assimpd\assimp\vector3.h"

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
	0.0f, 0.0f,   //���½�
	1.0f, 0.0f,   //���½�
	0.5f, 1.0f    //����
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

GLuint VBO;
GLuint VAO;
GLuint EBO;

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//����
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//���������
Camera camera(glm::vec3(0.0f, 0.0f, 20.0f));
GLfloat lastX = SCR_WIDTH / 2.0f;
GLfloat lastY = SCR_HEIGHT / 2.0f;

bool keys[1024];
bool firstMouse = true;

//��Դ����
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();

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

	//���ð����¼�
	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);

	int windowWidth, windowHeight;
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);

	//���úͱ�����ɫ��
	Shader shader("./Shaders/Vertex_Shader.glsl", "./Shaders/Fragment_Shader.glsl");
	Shader lightingshader("./Shaders/lamp_verShader.glsl", "./Shaders/lamp_fragShader.glsl");

	//����ģ��
	Model ourModel("../Model_Lib/nanosuit/nanosuit.obj");

//��Դ����
	//1.���Դ����
	PointLight pointlight_one(glm::vec3(0.7f, 0.2f, 2.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f,0.09f, 0.032f));
	PointLight pointlight_two(glm::vec3(2.3f, -3.3f, -4.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	PointLight pointlight_three(glm::vec3(-4.0f, 2.0f, -12.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	PointLight pointlight_four(glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 0.09f, 0.032f));
	//2.ƽ�й����
	DirLight dirLight(glm::vec3(-0.2f, -1.0f, -0.3f), glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.4f, 0.4f, 0.4f), glm::vec3(0.5f, 0.5f, 0.5f));
	//3.�۹�ƶ���
	SpotLight spotLight(camera.Position- glm::vec3(0.0f,0.0f,18.0f), camera.Front, glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(17.5f)),glm::vec3(0.05f, 0.05f, 0.05f), glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(1.0f, 1.0f, 1.0f));
	
	//�ƹ�����
	GLuint lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);  // ֻ��Ҫ��VBO�����ٴ�����VBO�����ݣ���Ϊ����(����)��VBO�������Ѿ���������ȷ�������嶥������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// ���õ�������Ķ�������ָ��(�����õƵĶ�������)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);

	//����任
	
	while (!glfwWindowShouldClose(window)) {
		//����¼�;
		glfwPollEvents();
		do_movement();

		GLfloat currentFrame = (GLfloat)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//��Ⱦָ��;
		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		shader.Use();  

		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 trans = projection * view;

		//���;���
		shader.setMat4("transform", trans);
		shader.setMat4("model", model);
		shader.setVec3("viewPos", camera.Position.x, camera.Position.y, camera.Position.z);

		shader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
		shader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
		shader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		shader.setFloat("material.shininess", 32.0f);

		//���Դ���ݴ���
		pointlight_one.TransData(shader, 0);
		pointlight_two.TransData(shader, 1);
		pointlight_three.TransData(shader, 2);
		pointlight_four.TransData(shader, 3);

		//ƽ�й����ݴ���
		dirLight.TransData(shader);

		//�۹�����ݴ���
		spotLight.TransData(shader);
		
		ourModel.Draw(shader);

		//�ƹ�������ɫ��
		lightingshader.Use();
		
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightingshader.setMat4("model", model);
		lightingshader.setMat4("transform", trans);
		   
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//��������;
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
	//���������
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
