#include <stdio.h>

#include "Shaders.h"
#include "Buffers.h"
#include "texture.h"
#include "cglm.h"

#define WIDTH = 1280;
#define HEIGHT = 720;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void ProcessInput(GLFWwindow* window, vec3 cameraPos, vec3 cameraFront, vec3 cameraTarget, vec3 up);

vec3 cameraPos = {0.0f, 0.0f, 3.0f};
vec3 cameraFront = {0.0f, 0.0f, -1.0f};
vec3 cameraTarget = {0.0f, 0.0f, 0.0f};
vec3 up = {0.0f, 1.0f, 0.0f};

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = -90.0f;
float lastX = 400, lastY = 300;

bool firstMouse;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Window Creation
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Eclipse Craft", NULL, NULL);

    if (window == NULL)
    {
        printf("Window creation failed");
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);  

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    unsigned int shaderProgram = shaderProgramCompile();
    VertexAndBufferSetup();
    unsigned int texture = TextureProcess("wall.jpg");
    unsigned int texture1 = TextureProcess("epstein.png");
    
    firstMouse = true;

    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window, cameraPos, cameraFront, cameraTarget, up);

        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, &texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, &texture1);

        glUseProgram(shaderProgram);

        //Camera
        mat4 proj;
        mat4 view;

        glm_mat4_identity(proj);
        glm_mat4_identity(view);

        vec3 buffer_lookat;
        glm_vec3_add(cameraPos, cameraFront, buffer_lookat);

        glm_lookat(cameraPos, buffer_lookat, up, view);

        int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj);

        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);

        glBindVertexArray(VAO);

        for(int i = 0; i < 16; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                mat4 model;
                glm_mat4_identity(model);
                glm_translate(model, (vec3){i, 0, j});
                
                int modelLoc = glGetUniformLocation(shaderProgram, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        printf("%fX %fY %fZ\n", cameraPos[0], cameraPos[1], cameraPos[2]);
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

void ProcessInput(GLFWwindow* window)
{
    float camSpeed = 0.05f * deltaTime;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm_vec3_muladds(cameraFront, camSpeed, cameraPos);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm_vec3_muladds(cameraFront, -camSpeed, cameraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm_cross(cameraFront, up, cameraPos);
        glm_normalize(cameraPos);
        glm_vec3_muladds(cameraPos, -camSpeed, cameraPos);
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm_cross(cameraFront, up, cameraPos);
        glm_normalize(cameraPos);
        glm_vec3_muladds(cameraPos, camSpeed, cameraPos);
    }
        
    
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = ypos - lastY;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;
    pitch += yOffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    vec3 direction = {cos(glm_rad(yaw)), sin(glm_rad(pitch)), sin(glm_rad(yaw)) * cos(glm_rad(pitch))};
    glm_normalize_to(direction, cameraFront);
}
