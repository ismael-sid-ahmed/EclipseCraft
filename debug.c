#include "debug.h"

#include "glad.h"
#include "glfw3.h"

#include "app.h"

#include "vui.h"

#include "vui_opengl.h"
#include "vui_opengl.c"

void DebugUIInit()
{   
    
}

void DebugUI(float camX, float camY, float camZ)
{
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
}