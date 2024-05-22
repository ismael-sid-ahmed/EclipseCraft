#include "Buffers.h"

#include "glad.h"
#include "glfw3.h"

 float vertices[] = {
    //Back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, //0
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, //1
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, //2
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, //3
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, //4
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, //5

    //Front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //6
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, //7
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //8
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, //9
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, //10
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //11

    //Left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //12
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, //13
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //14
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //15
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //16
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //17

    //Right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //18
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, //19
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //20
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //21
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //22
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //23

    //Bottom face
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //24
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, //25
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, //26
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, //27
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, //28
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, //29

    //Upper face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, //30
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, //31
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //32
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, //33
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, //34
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  //35
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

void VertexAndBufferSetup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}