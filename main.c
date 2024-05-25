#include <stdio.h>

#include "Shaders.h"
#include "Buffers.h"
#include "texture.h"
#include "cglm.h"

#define NK_IMPLEMENTATION
#include "nuklear.h"

#include <ft2build.h>
#include FT_FREETYPE_H  

int globalWidth = 1280;
int globalHeight = 720;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void ProcessInput(GLFWwindow* window);

void DebugUI();

//Text rendering
typedef struct Key {
    double key;
};

typedef struct Value {
    double value;
};

typedef struct Map {
    struct Key key;
    struct Value value;
};

typedef struct Character {
    unsigned int textureID;
    ivec2 Size;
    ivec2 Bearing;
    unsigned int Advance;
};

struct Map charMap;

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

    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        printf("Could not laod Freetype library");
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "fonts/arial.ttf", 0, &face))
    {
        printf("Failed to load font");
        return -1;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, "X", FT_LOAD_RENDER))
    {
        printf("Failed to load glyph");
        return -1;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            printf("Error Freetype: Failed to load Glyph");
            continue;
        }

        unsigned int textTexture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        struct Character charachter = {
            texture,
            ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };

        ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);

    }

    while (!glfwWindowShouldClose(window))
    {   
        printf("ERROR: %i - ", glGetError());

        DebugUI();

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

void DebugUI()
{
    enum {EASY, HARD};
    static int op = EASY;
    static float value = 0.6f;
    static int i =  20;
    struct nk_context ctx;
    struct nk_user_font font;
    font.userdata.ptr = &
    nk_init(&ctx, calloc(1, 1024), &font)
    if (nk_begin(&ctx, "Show", nk_rect(50, 50, 220, 220),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_CLOSABLE)) {
        // fixed widget pixel width
        nk_layout_row_static(&ctx, 30, 80, 1);
        if (nk_button_label(&ctx, "button")) {
            // event handling
        }
        // fixed widget window ratio width
        nk_layout_row_dynamic(&ctx, 30, 2);
        if (nk_option_label(&ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(&ctx, "hard", op == HARD)) op = HARD;
        // custom widget pixel width
        nk_layout_row_begin(&ctx, NK_STATIC, 30, 2);
        {
            nk_layout_row_push(&ctx, 50);
            nk_label(&ctx, "Volume:", NK_TEXT_LEFT);
            nk_layout_row_push(&ctx, 110);
            nk_slider_float(&ctx, 0, &value, 1.0f, 0.1f);
        }
        nk_layout_row_end(&ctx);
    }
    nk_end(&ctx);
}