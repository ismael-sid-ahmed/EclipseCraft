#include "Buffers.h"

#include "glad.h"
#include "glfw3.h"

 float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
         0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.5f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.5f, 0.5f,
         0.5f,  0.5f,  0.5f,  0.5f, 0.5f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.5f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.5f, 0.0f,

         0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.5f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 0.5f,
         0.5f, -0.5f, -0.5f,  0.5f, 0.5f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.5f,

        -0.5f,  0.5f, -0.5f,  0.0f, 0.5f,
         0.5f,  0.5f, -0.5f,  0.5f, 0.5f,
         0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.5f
    };


void VertexAndBufferSetup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}