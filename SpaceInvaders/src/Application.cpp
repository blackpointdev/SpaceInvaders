#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// My modules
#include "Shader.h"


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		std::cout << "Changed PolygonMode to GL_LINE\n";
	}

	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		std::cout << "Changed PolygonMode to GL_FILL\n";
	}
}

// Window resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Changed window size to: " << width << "x" << height << std::endl;
	glViewport(0, 0, width, height);
}


// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	// ---------------------------------- SHADER COMPILATION ----------------------------------

	// Load shader source
	Shader shader("res/shaders/Basic.shader");
	shader.Compile();

	// ---------------------------------- DATA FOR DRAWING ----------------------------------


	//float vertices[] = {
	//-0.05f, -0.8f, 1.0f, 0.0f, 0.0f,   // top right
	// 0.05f, -0.8f, 0.0f, 1.0f, 0.0f,  // bottom right
	//-0.05f, -0.9f, 0.0f, 0.0f, 1.0f,  // bottom left
	// 0.05f, -0.9f,  0.0f, 0.0f, 0.0f // top left 
	//};

	float vertices[] = {
	-0.05f, -0.8f,
	 0.05f, -0.8f,
	-0.05f, -0.9f,
	 0.05f, -0.9f
	};

	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		2, 3, 1    // second triangle
	};

	unsigned int VertexBufferObject, VertexArrayObejct, ElementBufferObject;

	// Generating vertex array and buffer
	glGenVertexArrays(1, &VertexArrayObejct);
	glGenBuffers(1, &VertexBufferObject);
	glGenBuffers(1, &ElementBufferObject);

	// Binding vertex array and buffer
	glBindVertexArray(VertexArrayObejct);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferObject);


	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(float), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), NULL);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
	//glEnableVertexAttribArray(1);

	// Unbinding
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		// render
		glClearColor(0.227f, 0.274f, 0.349f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();

		// Change color over time
		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;

		shader.SetUniformF("inColor", 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(VertexArrayObejct);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}