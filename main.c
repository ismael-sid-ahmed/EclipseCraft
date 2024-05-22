#include <stdio.h>

#include "Shaders.h"
#include "Buffers.h"
#include "texture.h"
#include "cglm.h"

#define float WIDTH = 1280;
#define float HEIGHT = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Window Creation
    GLFWwindow* window = glfwCreateWindow(800, 600, "Eclipse Craft", NULL, NULL);

    if (window == NULL)
    {
        printf("Window creation failed");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    unsigned int shaderProgram = shaderProgramCompile();
    VertexAndBufferSetup();
    unsigned int texture = TextureProcess();

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, &texture);

        glUseProgram(shaderProgram);

        //Camera
        mat4 model;
        mat4 proj;
        mat4 view;

        glm_mat4_identity(model);
        glm_mat4_identity(proj);
        glm_mat4_identity(view);

        glm_rotate(model, glm_rad(-55.0f), (vec3){1.0f, 0.0f, 0.0f});

        glm_translate(view, (vec3){0.0f, 0.0f, -3.0f});
        glm_perspective(glm_rad(45.0f), 800.0f / 600.0f, 0.1f, 100.0f, proj);

        int modelLoc = glGetUniformLocation(shaderProgram, "model");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

        int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj);

        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Resource deallocation
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int height, int width)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow *window)
{
    
}
