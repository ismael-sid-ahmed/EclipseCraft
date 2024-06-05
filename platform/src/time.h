#include "header.h"

float deltaTime = 0.0f;
float lastFrame = 0.0f;

void deltaTimeCalc()
{
    float currentFrame = (float)glfwGetTime();
    deltaTime = currentFrame-lastFrame;
    lastFrame = currentFrame;
}