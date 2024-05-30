typedef struct App
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
        float projection[16]
    } opengl;
};

App app;