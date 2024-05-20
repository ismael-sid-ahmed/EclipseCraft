#include "Shaders.h"
#include <stdio.h>
#include <string.h>

unsigned int fragmentShaderCompile()
{
    const char *fragmentShaderSource = importShader("frag.txt");
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Debug
    int success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("Fragment Shader compilation error: %s", infoLog);
    }

    return fragmentShader;
}

unsigned int vertexShaderCompile()
{
    const char *vertexShaderSource = importShader("vertex.txt");
    unsigned int vertexShader;
    //glcreateshader() is somehow changing the value of vertexShaderSource. Maybe it's due to undefined behaviour
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Debug
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("Vertex Shader compilation error: %s", infoLog);
    }

    return vertexShader;
}

unsigned int shaderProgramCompile()
{
    unsigned int* vertexShader = vertexShaderCompile();
    unsigned int* fragmentShader = fragmentShaderCompile();

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];

    //Debug
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Shader linking error %s", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

const char* importShader(char *shaderLocation)
{
    FILE* shaderFile;
    shaderFile = fopen(shaderLocation, "r");
    if (shaderFile == NULL)
    {
        printf("Shader loading has failed");
    }

    char *buffer = "";
    char shaderText[1024] = "";

    while(fgets(buffer, sizeof(shaderFile), shaderFile))
    {
        strcat(shaderText, buffer);
    }

    char* defShader = strdup(shaderText);

    fclose(shaderFile);
    
    return defShader;
}