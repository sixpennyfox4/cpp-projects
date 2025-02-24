#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

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
	GLFWwindow* window{ glfwCreateWindow(800, 800, "Simple Window", NULL, NULL) };
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

	// Set window viewport
	glViewport(0, 0, 800, 800);
	// Set callback when window is resized
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Render loop
	while (!glfwWindowShouldClose(window)) {
		// Process the input
		processInput(window);

		// Make the color buffer color to this
		glClearColor(0.3f, 0.2f, 0.1f, 1.0f);
		// Clear the color buffer so it can start empty next loop
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the buffers
		glfwSwapBuffers(window);
		// Handle events
		glfwPollEvents();
	}
	
	// Terminate glfw library
	glfwTerminate();
	return 0;
}
