#include "header.h"

typedef struct 
{
    GLuint ID;
} shader_t;

shader_t shaderProgram;

const char* importShader();

unsigned int fragmentShaderCompile();
unsigned int vertexShaderCompile();

unsigned int shaderProgramCompile();