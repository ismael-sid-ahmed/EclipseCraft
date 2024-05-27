#include <ft2build.h>
#include FT_FREETYPE_H

struct nk_context *ctx;
struct nk_font_atlas *atlas;

void DebugUI(float camX, float camY, float camZ);
void DebugUIInit();