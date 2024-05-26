#include <stdio.h>

#include "Shaders.h"
#include "Buffers.h"
#include "texture.h"
#include "cglm.h"
#include "debug.h"

int globalWidth = 1280;
int globalHeight = 720;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void ProcessInput(GLFWwindow* window);

vec3 cameraPos = {0.0f, 0.0f, 3.0f};
vec3 cameraFront = {0.0f, 0.0f, -1.0f};
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
    GLFWwindow* window = glfwCreateWindow(globalWidth, globalHeight, "Eclipse Craft", NULL, NULL);

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
    int *texture = TextureProcess("wall.jpg");

    glUseProgram(shaderProgram);

    glUniform1i(glGetUniformLocation(&texture, "texture"), 0);
    
    firstMouse = true;
    
    DebugUIInit(window);

    while (!glfwWindowShouldClose(window))
    {   
        printf("ERROR: %i - ", glGetError());

        //TODO: GL_INVALID_OPERATION fix
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;  

        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);     
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, &texture);

        glUseProgram(shaderProgram);

        //Camera
        mat4 proj;
        mat4 view;

        glm_mat4_identity(proj);
        glm_mat4_identity(view);

        glm_perspective(glm_rad(45), 1280 / 720, 0.1f, 100.0f, proj);

        vec3 buffer_lookat;
        glm_vec3_add(cameraPos, cameraFront, buffer_lookat);
        glm_lookat(cameraPos, buffer_lookat, up, view);

        int projLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, proj);

        int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view);

        //Chunk rendering
        glBindVertexArray(VAO);

        for(int i = 0; i < 16; i++)
        {
            for(int j = 0; j < 16; j++)
            {
                for(int k = 0; k < 64; k++)
                {
                mat4 model;
                glm_mat4_identity(model);
                glm_translate(model, (vec3){i, -k, j});
                
                int modelLoc = glGetUniformLocation(shaderProgram, "model");
                glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);

                glDrawArrays(GL_TRIANGLES, 0, 36);
                }
            }
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
        printf("%f X %f Y %f Z\n", cameraPos[0], cameraPos[1], cameraPos[2]);

        DebugUI();
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
    globalWidth = width;
    globalHeight = height;
}

void ProcessInput(GLFWwindow* window)
{
    float camSpeed = 1.0f * deltaTime;

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
        vec3 result;
        glm_cross(cameraFront, up, result);
        glm_normalize(result);
        glm_vec3_muladds(result, -camSpeed, cameraPos);
    }
        
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        vec3 result;
        glm_cross(cameraFront, up, result);
        glm_normalize(result);
        glm_vec3_muladds(result, camSpeed, cameraPos);
    }
        
    
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = (float)xposIn;
    float ypos = (float)yposIn;

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
    pitch -= yOffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
    vec3 front = {cos(glm_rad(yaw)) * cos(glm_rad(pitch)), sin(glm_rad(pitch)), sin(glm_rad(yaw)) * cos(glm_rad(pitch))};
    glm_normalize_to(front, cameraFront);
}