#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

const char* vertexShaderSource{ R"(
#version 330 core
layout (location = 0) in vec3 aPos;
uniform vec2 offset;

void main()
{
    gl_Position = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z, 1.0);
}
)" };

const char* fragmentShaderSource{ R"(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);
} 
)" };

int main() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[]{
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    GLFWwindow* window{ glfwCreateWindow(800, 600, "Moving Triangle", NULL, NULL) };
    if (window == NULL) {
        std::cout << "Failed to create GLFW window!\n";

        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, 800, 600);

    GLuint vertexShader{ glCreateShader(GL_VERTEX_SHADER) };
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader{ glCreateShader(GL_FRAGMENT_SHADER) };
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram{ glCreateProgram() };
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Store the data.

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // In case VBO and VAO are changed.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.3f, 0.3f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    });

    float xOffset{ 0.0f };
    float yOffset{ 0.0f };
    float speed{ 0.01f };

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_W)) yOffset += speed;
        if (glfwGetKey(window, GLFW_KEY_S)) yOffset -= speed;
        if (glfwGetKey(window, GLFW_KEY_A)) xOffset -= speed;
        if (glfwGetKey(window, GLFW_KEY_D)) xOffset += speed;

        glClearColor(0.3f, 0.3f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        int offsetLocation{ glGetUniformLocation(shaderProgram, "offset") };
        glUniform2f(offsetLocation, xOffset, yOffset);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
