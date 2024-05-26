#include "debug.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024
#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL4_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl4.h"

struct nk_glfw glfw = {0};

void DebugUIInit(GLFWwindow* window)
{
    ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    nk_glfw3_font_stash_end(&glfw);}
}

void DebugUI()
{
    nk_glfw3_new_frame(&glfw);

    if (nk_begin(ctx, "Anything window", nk_rect(0, 0, 200, 250), 
    NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
    NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {
            nk_layout_row_dynamic(ctx, 120, 1);
            nk_label(ctx, "Hello world!", NK_TEXT_CENTERED);
            
            nk_layout_row_dynamic(ctx, 50, 1);
            nk_label(ctx, "Hello world!", NK_TEXT_LEFT);
            
            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "AnyButton"))
                fprintf(stdout, "button pressed\n");
        }
        nk_end(ctx);

    nk_glfw3_render(NK_ANTI_ALIASING_ON);
}