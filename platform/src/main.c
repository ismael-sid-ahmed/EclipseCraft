#include <stdio.h>

#include "Shaders.h"
#include "Buffers.h"
#include "texture.h"
#include "cglm.h"
#include "camera.h"

#include "voxel.h"

#define GL_GLEXT_PROTOTYPES

#define STB_RECT_PACK_IMPLEMENTATION
#include "stb_rect_pack.h"

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"

/*
#include "vui.h"

#include "vui_opengl.h"
#include "vui_opengl.c"

#include "vui_stbtruetype.h"
#include "vui_stbtruetype.c"

#include "vui_stbtruetype_manager.h"
#include "vui_stbtruetype_manager.c"

*/

int globalWidth = 1280;
int globalHeight = 720;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void ProcessInput(GLFWwindow* window);

bool debugWin = false;

#include "debug.h"

/*typedef struct App
{
    GLFWwindow* window;
    VuiGlyphTextureId ascii_glyph_texture_id;
    VuiGlyphTextureId etc_glyph_texture_id;
    VuiFontId default_font_id;
    VuiImageId images[5];
    VuiStk(char) font_file_bytes;
    uint64_t last_frame_start_time;
    float dt;
    struct {
        GLuint tex_ascii_glyph_texture;
        GLuint tex_etc_glyph_texture;
        GLuint tex_image;
        GLuint program;
        float projection[16];
    } opengl;
};

typedef struct App App;

App app;
*/

int main()
{

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Window Creation
    GLFWwindow* window = glfwCreateWindow(globalWidth, globalHeight, "Eclipse Craft", NULL, NULL);
    //app.window = window;

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

    shaderProgram.ID = shaderProgramCompile();
    VertexAndBufferSetup();
    int *texture = TextureProcess("wall.jpg");

    glUseProgram(shaderProgram.ID);

    glUniform1i(glGetUniformLocation(&texture, "texture1"), 0);

    InitialChunkGenCaller();
    ChunkLoader();

    while (!glfwWindowShouldClose(window))
    {   
        //printf("ERROR: %i - ", glGetError());

        ProcessInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);     
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, &texture);

        glUseProgram(shaderProgram.ID);

        Camera(shaderProgram.ID);

        //Chunk rendering
        glBindVertexArray(VAO);

        ChunkRenderCaller(shaderProgram.ID);

        /*
        //Debug UI
            vui_opengl_init();

            vui_stbtt_glyph_texture_clear_styled_glyphs(app.etc_glyph_texture_id);

            vui_frame_start(vui_false, app.dt);

            vui_window_start(0, VuiVec2_init(1280, 720));
            vui_row_layout;

            static VuiVec2 size = {0};
            static VuiVec2 offset = {50.f, 50.f};
            vui_scope_width(vui_fill_len);
            vui_scope_height(vui_fill_len);
            vui_scroll_view_start(vui_sib_id, VuiScrollFlags_vhr, vui_ss.scroll_view);

            vui_opengl_render(app.window);

            vui_window_end;
            vui_frame_end;

        */

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Resource deallocation
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram.ID);

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
    CameraMove(window);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    cameraRotate(xposIn, yposIn);
}