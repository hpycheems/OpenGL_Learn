/*
#include "stb_image.h"
#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>


//callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
*/

/*
*  �����Ʒ�ʽ ʹ��glTexParamiter����������
*  GL_REPEAT			�ظ�����ͼ��
*  GL_MIRRORED_REPEAT   ÿ���ظ�ͼƬ�Ǿ�����õġ�
*  GL_CLAMP_EDGE		��������ᱻԼ����0��1֮�䣬�����Ĳ��ֻ��ظ���������ı�Ե������һ�ֱ�Ե�������Ч����
*  GL_CLAMP_BORDER		����������Ϊ�û�ָ���ı�Ե��ɫ��
*  glTexParameteri
*  glTexParameterfv ���������������ָ��GL_CLAMP_BORDER�ı�Ե��ɫGL_TEXTURE_BORDERCOLOR
*
*  �������
*  GL_NEAREST    �ڽ����� OpenGL��ѡ�����ĵ���ӽ�����������Ǹ����ء�
*  GL_LIEAR    ���Թ��� ��������������긽�����������أ������һ����ֵ�����Ƴ���Щ��������֮�����ɫ��
*				 һ���������ص����ľ�����������Խ������ô����������ص���ɫ�����յ�������ɫ�Ĺ���Խ��
*
*  ���зŴ����С����ʱ����������˵�ѡ��
*  ��Ҫʹ��glTexParameter����Ϊ�Ŵ����Сָ�����˷�ʽ��
*  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEARST);
*  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_FILTER, GL_LINEAR)
*
*  �༶��Զ����һϵ�е�����ͼ�񣬺�һ������ͼ����ǰһ���Ķ���֮һ��
*  �༶��Զ�����������ܼ򵥣�	��۲��ߵľ��볬��һ������ֵ��OpenGL��ʹ�ò�ͬ�Ķ༶��Զ���������ʺ�����ľ�����Ǹ���
*							    ���ھ���Զ�������Ȳ���Ҳ���ᱻ�û�ע�⵽��ͬʱ���༶��Զ������һ�ӷ�֮�����������ܷǳ��á�
*  glGenerateMipmap�������ڴ�����һ������������OpenGL�ͻ�е������������й����ˡ�
*
*  Ϊ��ָ����ͬ�༶��Զ������֮��Ĺ��˷�ʽ�������ʹ�������ĸ�ѡ���е�һ������ԭ�еĹ��˷�ʽ��
*  GL_NEARST_MIPMAP_NEARST ʹ�����ڽ��Ķ༶��Զ������ƥ�����ش�С����ʹ���ڽ���ֵ�����������
*  GL_LINEAR_MIPMAP_NEARST ʹ�����ڽ��Ķ༶��Զ�����𣬲�ʹ�����Բ�ֵ���в���
*  GL_NEARST_MIPMAP_LINEAR ��������ƥ�����ش�С�Ķ༶��Զ����֮��������Բ�ֵ��ʹ���ڽ���ֵ���в���
*  GL_LINEAR_MIPMAP_LINEAR �������ڽ��Ķ༶��Զ����֮��ʹ�����Բ�ֵ����ʹ�����Բ�ֵ���в���
*  ���ã�	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
*			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LEANR);
*
*  һ�������Ĵ����ǣ����Ŵ���˵�ѡ������Ϊ�༶��Զ�������ѡ��֮һ������û���κ�Ч������Ϊ�༶��Զ������Ҫ��ʹ����������С������µģ�
*  ����Ŵ󲻻�ʹ�ö༶��Զ����Ϊ�Ŵ�������ö༶��Զ�����ѡ������һ��GL_INVALID_ENUM������롣
*
*  ����Ԫ
*  ����Ԫ����ҪĿ��������������ɫ���п���ʹ�ö���һ��������
*  ͨ��������Ԫ��ֵ�������������ǿ���һ�ΰ󶨶������ֻҪ�������ȼ����Ӧ������Ԫ��
*  ����ʹ��glActiveTexture��������Ԫ������������Ҫʹ�õ�����Ԫ
*  glActiveTexture(GL_TEXTURE0)
*  glBindTexture(GL_TEXTURE_2D, texture);
*  ��������Ԫ֮�󣬽�������glBindTexture�������û�����������ǰ���������Ԫ������ԪGL_TEXTURE0Ĭ�����Ǳ�����
*/

/*
int main() {
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//glfw windows
	GLFWwindow* window = glfwCreateWindow(800, 600, "MyWindow", NULL, NULL);
	if (window == NULL) {
		std::cout << "failed create GLFW window \n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//Init GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to Init GLAD\n";
		return -1;
	}

	//viewport
	glViewport(0, 0, 800, 600);

	//frameCallback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//=========================================================================================================================================

	//load Texture
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);


	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture \n";
	}
	stbi_image_free(data);//�ͷ��ڴ�

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data1 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data1) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data1);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture \n";
	}
	stbi_image_free(data1);//�ͷ��ڴ�

	//init VAO VBO
	float vertices[] = {
		//     ---- λ�� ----       ---- ��ɫ ----     - �������� -
			 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // ����
			 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // ����
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // ����
	};
	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	unsigned int VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);



	Shader s("texture_v.glsl", "texture_f.glsl");
	s.use();
	s.setInt("texture1", 0);
	s.setInt("texture2", 1);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		//��Ⱦ
		glClearColor(0.2f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		s.use();
		float time = glfwGetTime();
		float offset = (sin(time) / 2.0f) + 0.5f;
		s.setFloat("offset", offset);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}
*/