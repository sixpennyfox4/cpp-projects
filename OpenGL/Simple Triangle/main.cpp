#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

const int windowWidth{ 800 };
const int windowHeight{ 600 };

const char* vertexShaderSource{ R"(#version 330 core
layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
})" };

const char* fragmentShaderSource{ R"(#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
})" };

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	// Init GLFW
	glfwInit();

	// V3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window object
	GLFWwindow* window{ glfwCreateWindow(windowWidth, windowHeight, "Simple Triangle", NULL, NULL) };
	if (window == NULL) {
		std::cout << "Failed to create GLDW window!";

		glfwTerminate();
		return -1;
	}
	// Set the current context
	glfwMakeContextCurrent(window);

	// Load the addresses of function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to init GLAD!";

		return -1;
	}

	// Triangle vertices
	float vertices[]{
		-0.5f, -0.5f, 0.0f, // Left
		0.5f, -0.5f, 0.0f, // Right
		0.0f, 0.5f, 0.0f  // Bottom
	};

	unsigned int shaderProgram;
	unsigned int vertexShader, fragmentShader;
	unsigned int VBO, VAO;
	// Generate and bind vertex buffer object. (VBO)
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Generate and bind vertex array object. (VAO)
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Create and compile vertex shader.
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// Create and compile fragment shader.
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Link the shaders into a program.
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Delete the shaders.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Set window viewport
	glViewport(0, 0, windowWidth, windowHeight);
	// Set callback when window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Process the input
		processInput(window);

		// Make the color buffer color to this
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		// Clear the color buffer so it can start empty next loop
		glClear(GL_COLOR_BUFFER_BIT);

		// Use the program and draw the triangle
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap the buffers
		glfwSwapBuffers(window);
		// Handle events
		glfwPollEvents();
	}

	// Terminate glfw library
	glfwTerminate();
	return 0;
}
