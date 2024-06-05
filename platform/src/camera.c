#include "camera.h"

#include "cglm.h"
#include "time.h"

#include "header.h"

vec3 cameraPos = {0.0f, 0.0f, 0.0f};
vec3 cameraFront = {0.0f, 0.0f, -1.0f};
vec3 up = {0.0f, 1.0f, 0.0f};

float yaw = -90.0f;
float pitch = -90.0f;
float lastX = 400, lastY = 300;

bool firstMouse = true;

void Camera(GLuint shaderProgram)
{
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
}

void CameraMove(GLFWwindow* window)
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

void cameraRotate(double xposIn, double yposIn)
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